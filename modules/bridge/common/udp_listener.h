/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace apollo {
namespace bridge {

constexpr int MAXEPOLLSIZE = 100;

template <typename T>
class UDPListener {
 public:
  typedef bool (T::*func)(int fd);
  UDPListener() {}
  UDPListener(T *receiver, uint16_t port, func msg_handle) {
    receiver_ = receiver;
    listened_port_ = port;
    msg_handle_ = msg_handle;
  }
  ~UDPListener() {
    if (listener_sock_ != -1) {
      close(listener_sock_);
    }
  }

  void SetMsgHandle(func msg_handle) { msg_handle_ = msg_handle; }
  bool Initialize(T *receiver, func msg_handle, uint16_t port);
  bool Listen();

  static void *pthread_handle_message(void *param);

 public:
  struct Param {
    int fd_ = 0;
    UDPListener<T> *listener_ = nullptr;
  };

 private:
  bool setnonblocking(int sockfd);
  void MessageHandle(int fd);

 private:
  T *receiver_ = nullptr;
  uint16_t listened_port_ = 0;
  int listener_sock_ = -1;
  func msg_handle_ = nullptr;
  int kdpfd_ = 0;
};
//typedef bool (T::*func)(int fd); 定义函数指针返回类型为bool，传入参数为port
template <typename T>
bool UDPListener<T>::Initialize(T *receiver, func msg_handle, uint16_t port) {
  msg_handle_ = msg_handle;
  //如果msg_handle_为空指针，则返回错误
  if (!msg_handle_) {
    return false;
  }
  //receiver类型为模板传入类型，在这里是UDPBridgeReceiverComponent类型
  receiver_ = receiver;
  if (!receiver_) {
    return false;
  }
  //监听端口
  listened_port_ = port;
  //在Linux系统中，Resouce limit指在一个进程的执行过程中，它所能得到的资源的限制
  struct rlimit rt;
  //设置每个进程允许打开的最大文件数
  rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
  if (setrlimit(RLIMIT_NOFILE, &rt) == -1) {
    return false;
  }
  //设置socket
  listener_sock_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (listener_sock_ == -1) {
    return false;
  }
  int opt = SO_REUSEADDR;
  //设置 socket FD's option
  setsockopt(listener_sock_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  //设置非阻塞选项
  setnonblocking(listener_sock_);

  // serv_addr赋值
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = PF_INET;
  serv_addr.sin_port = htons((uint16_t)listened_port_);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  //绑定地址
  if (bind(listener_sock_, (struct sockaddr *)&serv_addr,
           sizeof(struct sockaddr)) == -1) {
    close(listener_sock_);
    return false;
  }
  //https://www.cnblogs.com/xuewangkai/p/11158576.html
  //该函数生成一个epoll专用的文件描述符。它其实是在内核申请一空间，用来存放你想关注的socket fd
  //上是否发生以及发生了什么事件。size就是你在这个epoll fd上能关注的最大socket fd数。随你定好了。
  //只要你有空间
  kdpfd_ = epoll_create(MAXEPOLLSIZE);
  struct epoll_event ev;
  //EPOLLIN表示对应的文件描述符可以读(包括对端SOCKET正常关闭);
  //EPOLLET将EPOLL设为边缘触发(Edge Triggered)模式
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = listener_sock_;
  //该函数用于控制某个epoll文件描述符上的事件，可以注册事件，修改事件，删除事件。
  if (epoll_ctl(kdpfd_, EPOLL_CTL_ADD, listener_sock_, &ev) < 0) {
    close(listener_sock_);
    return false;
  }
  return true;
}

template <typename T>
bool UDPListener<T>::Listen() {
  int nfds = -1;
  bool res = true;
  struct epoll_event events[MAXEPOLLSIZE];
  while (true) {
    //系统调用等待文件描述符epfd引用的epoll实例上的事件。事件所指向的存储区域将包含可供调用者使用的事件
    //第1个参数 epfd是 epoll的描述符。
    //第2个参数 events则是分配好的 epoll_event结构体数组，epoll将会把发生的事件复制到 events数组中
    //第3个参数 maxevents表示本次可以返回的最大事件数目，通常 maxevents参数与预分配的events数组的大小是相等的。
    //第4个参数 timeout表示在没有检测到事件发生时最多等待的时间（单位为毫秒）
    //该函数返回需要处理的事件数目
    nfds = epoll_wait(kdpfd_, events, 10000, -1);
    if (nfds == -1) {
      res = false;
      break;
    }

    for (int i = 0; i < nfds; ++i) {
      if (events[i].data.fd == listener_sock_) {
        pthread_t thread;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        Param *par = new Param;
        par->fd_ = events[i].data.fd;
        par->listener_ = this;
        //线程创建
        if (pthread_create(&thread, &attr,
                           &UDPListener<T>::pthread_handle_message,
                           reinterpret_cast<void *>(par))) {
          res = false;
          return res;
        }
      }
    }
  }
  close(listener_sock_);
  return res;
}

template <typename T>
bool UDPListener<T>::setnonblocking(int sockfd) {
  if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) == -1) {
    return false;
  }
  return true;
}

template <typename T>
void *UDPListener<T>::pthread_handle_message(void *param) {
  Param *par = static_cast<Param *>(param);
  //需要监听的fd
  int fd = par->fd_;
  UDPListener<T> *listener = par->listener_;
  if (par) {
    delete par;
  }
  par = nullptr;
  if (!listener) {
    pthread_exit(nullptr);
  }
  //进入消息处理函数
  listener->MessageHandle(fd);
  pthread_exit(nullptr);
}

template <typename T>
void UDPListener<T>::MessageHandle(int fd) {
  if (!receiver_ || !msg_handle_) {
    return;
  }
  (receiver_->*msg_handle_)(fd);
}

}  // namespace bridge
}  // namespace apollo

/******************************************************************************der
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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

#include <memory>
#include <string>
#include <vector>

#include "modules/bridge/common/bridge_header.h"
#include "modules/bridge/common/macro.h"

namespace apollo {
namespace bridge {

template <typename T>
class BridgeProtoSerializedBuf {
 public:
  BridgeProtoSerializedBuf() {}
  ~BridgeProtoSerializedBuf();

  char *GetFrame(size_t index);
  bool Serialize(const std::shared_ptr<T> &proto, const std::string &msg_name);

  const char *GetSerializedBuf(size_t index) const {
    //获取buf数据
    return frames_[index].buf_;
  }
  //获取一共序列化多少帧buf
  size_t GetSerializedBufCount() const { return frames_.size(); }
  size_t GetSerializedBufSize(size_t index) const {
    return frames_[index].buf_len_;
  }

 private:
  struct Buf {
    char *buf_;
    size_t buf_len_;
  };

 private:
  std::vector<Buf> frames_;
};

template <typename T>
BridgeProtoSerializedBuf<T>::~BridgeProtoSerializedBuf() {
  for (auto frame : frames_) {
    FREE_ARRY(frame.buf_);
  }
}

template <typename T>
bool BridgeProtoSerializedBuf<T>::Serialize(const std::shared_ptr<T> &proto,
                                            const std::string &msg_name) {
  //获取protobuf数据的字节数长度
  bsize msg_len = static_cast<bsize>(proto->ByteSizeLong());
  //开辟数组空间，大小为msg_len
  char *tmp = new char[msg_len]();
  //将protobufu数据转换到char *
  if (!proto->SerializeToArray(tmp, static_cast<int>(msg_len))) {
    FREE_ARRY(tmp);
    return false;
  }
  bsize offset = 0;
  bsize frame_index = 0;
  //计算protobuf数据一共有多少帧，这里定义frame大小为1024个字节，所以如果余数为0，则
  //说明为整数帧，如果不为零，则剩余信息单独为一帧
  uint32_t total_frames = static_cast<uint32_t>(msg_len / FRAME_SIZE +
                                                (msg_len % FRAME_SIZE ? 1 : 0));

  while (offset < msg_len) {
    //剩余字节数标志
    bsize left = msg_len - frame_index * FRAME_SIZE;
    //拷贝数据的大小，如果剩余字节大小大于1024字节，则拷贝数据只能为1024字节，如果小于
    //1024字节，则拷贝数据大小为left字节数，也就是剩余的字节数据
    bsize cpy_size = (left > FRAME_SIZE) ? FRAME_SIZE : left;
    //发送数据的头部信息
    BridgeHeader header;
    //头部数据版本号
    header.SetHeaderVer(0);
    //protobuf数据类型名，用于标识该protobuf数据的类型
    header.SetMsgName(msg_name);   //举例 msg_name为test_example,header占24个字节
    //protobuf数据ID，用于唯一标识一个protobuf数据
    header.SetMsgID(proto->header().sequence_num());
    //数据时间辍
    header.SetTimeStamp(proto->header().timestamp_sec());
    //protobuf数据序列化后的总字节数，注意不包含首部
    header.SetMsgSize(msg_len);
    //该protobuf数据的总帧数，按照1024字节划分
    header.SetTotalFrames(total_frames);
    //每一帧数据的大小
    header.SetFrameSize(cpy_size);
    //每一帧数据的索引值
    header.SetIndex(frame_index);
    //该帧的数据在序列化protobuf数据中的位置,用于将各个帧中的数据组装回protobuf数据
    header.SetFramePos(frame_index * FRAME_SIZE);
    //返回头部字节数
    hsize header_size = header.GetHeaderSize();
    //每一帧buf的数据，包括protobuf拆分数据和头部数据，大小为cpy_size + header_size
    Buf buf;
    buf.buf_ = new char[cpy_size + header_size];
    buf.buf_len_ = cpy_size + header_size;
    //头部数据序列化，也就是将头部数据填充到buf中
    header.Serialize(buf.buf_, buf.buf_len_);
    //将拆包数据拷贝到buf里
    memcpy(buf.buf_ + header_size, tmp + frame_index * FRAME_SIZE, cpy_size);
    //到此时就形成了一帧数据
    frames_.push_back(buf);
    frame_index++;
    offset += cpy_size;
  }
  FREE_ARRY(tmp);
  return true;
}

}  // namespace bridge
}  // namespace apollo

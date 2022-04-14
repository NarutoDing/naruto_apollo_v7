/******************************************************************************
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

#include <string>

namespace apollo {
namespace bridge {

typedef uint32_t bsize;

enum HType {
  Header_Ver,
  Msg_Name,
  Msg_ID,
  Msg_Size,
  Msg_Frames,
  Frame_Size,
  Frame_Pos,
  Frame_Index,
  Time_Stamp,

  Header_Tail,
};

class HeaderItemBase {
 public:
  HeaderItemBase() = default;
  virtual ~HeaderItemBase() {}

 public:
  virtual char *SerializeItem(char *buf, size_t buf_size) = 0;
  virtual const char *DiserializeItem(const char *buf,
                                      size_t *diserialized_size) = 0;
  virtual HType GetType() const = 0;
};

template <enum HType t, typename T>
struct HeaderItem;

template <enum HType t, typename T>
char *SerializeItemImp(const HeaderItem<t, T> &item, char *buf,
                       size_t buf_size) {
  if (!buf || buf_size == 0 ||
      buf_size < size_t(sizeof(t) + item.ValueSize() + 3)) {
    return nullptr;
  }
  //首指针的意思可以理解为char * prtE代表的 char exemple[]数组的第一个指针
  //也就是prtE[0]为exemple[0]
  
  //1: res为首指针，现在res指向buf[25]处的位置
  char *res = buf;
  //获取传入值alue的字节数，sizeof(value_)
  //1: apollo::bridge::Header_Ver枚举值占4个字节
  size_t item_size = item.ValueSize();
  //1: 获取传入的头的type，比如apollo::bridge::Header_Ver，版本好索引
  HType type = t;
  //1: 将版本号枚举值拷贝到res中，占据4个字节,res[0-3]为版本号枚举值  buf[25-28]为版本号枚举值
  memcpy(res, &type, sizeof(HType));
  //1: res[4]为':',buf[29]为':'
  res[sizeof(HType)] = ':';
  //1: res现在为首指针， 指向buf[30]处指针  
  res = res + sizeof(HType) + 1;
  //1： 将item_size拷贝进res及buf，item_size为8个字节大小，现从buf[30]处拷贝该值
  memcpy(res, &item_size, sizeof(size_t));
  //1： res[4]为':' 也就是buf[34]为':'
  res[sizeof(bsize)] = ':';
  //1: 现在res为首指针，指向buf[35]
  res = res + sizeof(bsize) + 1;
  //1: 拷贝value数据,从buf[35]处开始拷贝
  memcpy(res, item.GetValuePtr(), item.ValueSize());
  //1: res[4]处字符为'\n'，也就是buf[39]处为'\n'
  res[item.ValueSize()] = '\n';
  //1: res为首指针，指向buf[40]处
  res += item.ValueSize() + 1;
  //依次类推
  return res;
}

template <enum HType t, typename T>
const char *DiserializeItemImp(HeaderItem<t, T> *item, const char *buf,
                               size_t *diserialized_size) {
  if (!buf || !diserialized_size) {
    return nullptr;
  }
  const char *res = buf;

  char p_type[sizeof(HType)] = {0};
  memcpy(p_type, buf, sizeof(HType));
  HType type = *(reinterpret_cast<HType *>(p_type));
  if (type != t) {
    return nullptr;
  }
  res += sizeof(HType) + 1;
  *diserialized_size += sizeof(HType) + 1;

  char p_size[sizeof(bsize)] = {0};
  memcpy(p_size, res, sizeof(bsize));
  bsize size = *(reinterpret_cast<bsize *>(p_size));
  res += sizeof(bsize) + 1;
  *diserialized_size += sizeof(bsize) + 1;

  item->SetValue(res);
  res += size + 1;
  *diserialized_size += size + 1;
  return res;
}

template <enum HType t, typename T>
struct HeaderItem : public HeaderItemBase {
  T value_;

  operator T() { return value_; }
  HeaderItem &operator=(const T &val) {
    value_ = val;
    return *this;
  }
  HType GetType() const override { return t; }
  size_t ValueSize() const { return sizeof(value_); }
  const T *GetValuePtr() const { return &value_; }
  void SetValue(const char *buf) {
    if (!buf) {
      return;
    }
    value_ = *(reinterpret_cast<const T *>(buf));
  }

  char *SerializeItem(char *buf, size_t buf_size) override {
    return SerializeItemImp(*this, buf, buf_size);
  }

  const char *DiserializeItem(const char *buf,
                              size_t *diserialized_size) override {
    return DiserializeItemImp(this, buf, diserialized_size);
  }
};

template <enum HType t>
struct HeaderItem<t, std::string> : public HeaderItemBase {
  std::string value_;
  operator std::string() { return value_; }
  HeaderItem &operator=(const std::string &val) {
    value_ = val;
    return *this;
  }
  size_t ValueSize() const { return value_.length() + 1; }
  HType GetType() const override { return t; }
  const char *GetValuePtr() const { return value_.c_str(); }
  void SetValue(const char *buf) {
    if (!buf) {
      return;
    }
    value_ = std::string(buf);
  }

  char *SerializeItem(char *buf, size_t buf_size) override {
    return SerializeItemImp(*this, buf, buf_size);
  }

  const char *DiserializeItem(const char *buf,
                              size_t *diserialized_size) override {
    return DiserializeItemImp(this, buf, diserialized_size);
  }
};

}  // namespace bridge
}  // namespace apollo

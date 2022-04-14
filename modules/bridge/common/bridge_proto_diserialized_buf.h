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

#include "cyber/cyber.h"
#include "modules/bridge/common/bridge_header.h"
#include "modules/bridge/common/macro.h"

namespace apollo {
namespace bridge {

constexpr uint32_t INT_BITS = static_cast<uint32_t>(sizeof(uint32_t) * 8);

class ProtoDiserializedBufBase {
 public:
  ProtoDiserializedBufBase() {}
  virtual ~ProtoDiserializedBufBase() {}

  virtual bool Initialize(const BridgeHeader &header,
                          std::shared_ptr<cyber::Node> node) = 0;

  virtual bool DiserializedAndPub() = 0;
  virtual bool IsReadyDiserialize() const = 0;
  virtual bool IsTheProto(const BridgeHeader &header) = 0;
  virtual void UpdateStatus(uint32_t frame_index) = 0;
  virtual uint32_t GetMsgID() const = 0;
  virtual std::string GetMsgName() const = 0;
  virtual char *GetBuf(size_t offset) = 0;
};

template <typename T>
class BridgeProtoDiserializedBuf : public ProtoDiserializedBufBase {
 public:
  BridgeProtoDiserializedBuf() {}
  explicit BridgeProtoDiserializedBuf(const std::string &topic_name)
      : topic_name_(topic_name) {}
  virtual ~BridgeProtoDiserializedBuf();

  virtual bool DiserializedAndPub();
  virtual bool Initialize(const BridgeHeader &header,
                          std::shared_ptr<cyber::Node> node);

  virtual bool IsReadyDiserialize() const { return is_ready_diser; }
  virtual void UpdateStatus(uint32_t frame_index);
  virtual bool IsTheProto(const BridgeHeader &header);

  bool Initialize(const BridgeHeader &header);
  bool Diserialized(std::shared_ptr<T> proto);
  virtual char *GetBuf(size_t offset) { return proto_buf_ + offset; }
  virtual uint32_t GetMsgID() const { return sequence_num_; }
  virtual std::string GetMsgName() const { return proto_name_; }

 private:
  size_t total_frames_ = 0;
  size_t total_size_ = 0;
  std::string proto_name_ = "";
  std::vector<uint32_t> status_list_;
  char *proto_buf_ = nullptr;
  bool is_ready_diser = false;
  uint32_t sequence_num_ = 0;
  std::shared_ptr<cyber::Writer<T>> writer_;
  std::string topic_name_ = "";
};

template <typename T>
BridgeProtoDiserializedBuf<T>::~BridgeProtoDiserializedBuf() {
  FREE_ARRY(proto_buf_);
}

template <typename T>
bool BridgeProtoDiserializedBuf<T>::Diserialized(std::shared_ptr<T> proto) {
  if (!proto_buf_ || !proto) {
    return false;
  }
  proto->ParseFromArray(proto_buf_, static_cast<int>(total_size_));
  return true;
}

template <typename T>
void BridgeProtoDiserializedBuf<T>::UpdateStatus(uint32_t frame_index) {
  size_t status_size = status_list_.size();
  if (status_size == 0) {
    is_ready_diser = false;
    return;
  }

  uint32_t status_index = frame_index / INT_BITS;
  status_list_[status_index] |= (1 << (frame_index % INT_BITS));
  for (size_t i = 0; i < status_size; i++) {
    if (i == status_size - 1) {
      if (static_cast<int>(status_list_[i]) ==
          (1 << total_frames_ % INT_BITS) - 1) {
        AINFO << "diserialized is ready";
        is_ready_diser = true;
      } else {
        is_ready_diser = false;
        break;
      }
    } else {
      if (status_list_[i] != 0xffffffff) {
        is_ready_diser = false;
        break;
      }
      is_ready_diser = true;
    }
  }
}

template <typename T>
bool BridgeProtoDiserializedBuf<T>::IsTheProto(const BridgeHeader &header) {
  if (strcmp(proto_name_.c_str(), header.GetMsgName().c_str()) == 0 &&
      sequence_num_ == header.GetMsgID()) {
    return true;
  }
  return false;
}

template <typename T>
bool BridgeProtoDiserializedBuf<T>::Initialize(const BridgeHeader &header) {
  total_size_ = header.GetMsgSize();
  total_frames_ = header.GetTotalFrames();
  if (total_frames_ == 0) {
    return false;
  }
  int status_size = static_cast<int>(total_frames_ / INT_BITS +
                                     ((total_frames_ % INT_BITS) ? 1 : 0));
  if (status_list_.empty()) {
    for (int i = 0; i < status_size; i++) {
      status_list_.push_back(0);
    }
  }

  if (!proto_buf_) {
    proto_buf_ = new char[total_size_];
  }
  return true;
}

template <typename T>
bool BridgeProtoDiserializedBuf<T>::Initialize(
    const BridgeHeader &header, std::shared_ptr<cyber::Node> node) {
  writer_ = node->CreateWriter<T>(topic_name_.c_str());
  return Initialize(header);
}

template <typename T>
bool BridgeProtoDiserializedBuf<T>::DiserializedAndPub() {
  auto pb_msg = std::make_shared<T>();
  if (!Diserialized(pb_msg)) {
    return false;
  }
  writer_->Write(pb_msg);
  return true;
}

}  // namespace bridge
}  // namespace apollo

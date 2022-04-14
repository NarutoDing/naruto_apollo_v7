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

#include "modules/bridge/common/bridge_header.h"

#include <cstring>

namespace apollo {
namespace bridge {

bool BridgeHeader::Serialize(char *buf, size_t size) {
  if (!buf || size == 0) {
    return false;
  }
  //每个序列化数据所在的指针位置
  char *cursor = buf;  //此处指针位于buf首部
  char *p_header_size = nullptr;
  //首先序列化HeaderFlag，也就是 constexpr char BRIDGE_HEADER_FLAG[] = "ApolloBridgeHeader";
  cursor = SerializeHeaderFlag(cursor, size);
  //cursor位于buf[20]处的指针位置，p_header_size指向buf[20]的指针位置
  //此时p_header_size[0] == buf[20]
  p_header_size = cursor;
  //cursor为首指针，移动到buf[25]字节处
  cursor += sizeof(hsize) + 1;
  //序列化Header的其它内容
  for (int i = 0; i < Header_Tail; i++) {
    //传入cursor指针， 和buf数据size
    cursor = header_item[i]->SerializeItem(cursor, size);
  }

  if (!SerializeHeaderSize(p_header_size, size)) {
    return false;
  }
  return true;
}

bool BridgeHeader::Diserialize(const char *buf, size_t buf_size) {
  const char *cursor = buf;

  int i = static_cast<int>(buf_size);
  while (i > 0) {
    HType type = *(reinterpret_cast<const HType *>(cursor));
    if (type >= Header_Tail || type < 0) {
      cursor += sizeof(HType) + 1;
      bsize size = *(reinterpret_cast<const bsize *>(cursor));
      cursor += sizeof(bsize) + size + 2;
      i -= static_cast<int>(sizeof(HType) + sizeof(bsize) + size + 3);
      continue;
    }
    size_t value_size = 0;
    for (int j = 0; j < Header_Tail; j++) {
      if (type == header_item[j]->GetType()) {
        cursor = header_item[j]->DiserializeItem(cursor, &value_size);
        break;
      }
    }
    i -= static_cast<int>(value_size);
  }
  return true;
}

bool BridgeHeader::IsAvailable(const char *buf) {
  if (!buf) {
    return false;
  }
  if (memcmp(BRIDGE_HEADER_FLAG, buf, sizeof(BRIDGE_HEADER_FLAG) - 1) != 0) {
    return false;
  }
  return true;
}

char *BridgeHeader::SerializeHeaderFlag(char *buf, size_t size) {
  if (!buf || size == 0) {
    return nullptr;
  }
  return SerializeBasicType<char, sizeof(BRIDGE_HEADER_FLAG)>(
      BRIDGE_HEADER_FLAG, buf, size);
}

char *BridgeHeader::SerializeHeaderSize(char *buf, size_t size) {
  hsize header_size = GetHeaderSize();
  return SerializeBasicType<hsize, sizeof(hsize)>(&header_size, buf, size);
}

}  // namespace bridge
}  // namespace apollo

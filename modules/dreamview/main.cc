/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
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

#include "cyber/common/global_data.h"
#include "cyber/init.h"
#include "modules/dreamview/backend/dreamview.h"

int main(int argc, char *argv[]) {
  //google解析命令行参数
  google::ParseCommandLineFlags(&argc, &argv, true);
  // Added by caros to improve dv performance
  apollo::cyber::GlobalData::Instance()->SetProcessGroup("dreamview_sched");
  //cyber初始化
  apollo::cyber::Init(argv[0]);
  //创建Dreamview对象
  apollo::dreamview::Dreamview dreamview;
  //初始化和启动dreamview
  const bool init_success = dreamview.Init().ok() && dreamview.Start().ok();
  if (!init_success) {
    AERROR << "Failed to initialize dreamview server";
    return -1;
  }
  apollo::cyber::WaitForShutdown();
  return 0;
}

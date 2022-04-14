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
#include "cyber/cyber.h"
#include "modules/map/tools/map_datachecker/server/worker.h"

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  AINFO << "cyber init";
  if (apollo::cyber::Init(argv[0])) {
    AINFO << "init succeed";
  } else {
    AERROR << "init failed";
  }

  google::SetStderrLogging(FLAGS_minloglevel);

  AINFO << "starting worker";
  apollo::hdmap::Mapdatachecker worker;
  if (!worker.Start()) {
    AFATAL << "Start Mapdatachecker Failed!";
    return -1;
  }

  apollo::cyber::WaitForShutdown();
  return 0;
}

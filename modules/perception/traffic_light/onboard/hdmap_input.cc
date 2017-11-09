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

#include "modules/perception/traffic_light/onboard/hdmap_input.h"

#include <stdlib.h>
#include <algorithm>
#include <vector>

#include "Eigen/Core"
#include "modules/common/configs/config_gflags.h"
#include "modules/common/log.h"
#include "modules/map/hdmap/hdmap_util.h"
#include "modules/perception/common/define.h"
#include "modules/perception/common/perception_gflags.h"

namespace apollo {
namespace perception {

using apollo::hdmap::HDMapUtil;

using std::string;
using std::vector;

// HDMapInput
HDMapInput::HDMapInput() {}

bool HDMapInput::Init() {
  return HDMapUtil::ReloadMaps();
}

}  // namespace perception
}  // namespace apollo

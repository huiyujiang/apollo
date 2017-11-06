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
 
#ifndef MODULES_PERCEPTION_OBSTACLE_FUSION_INTERFACE_BASE_FUSION_H_
#define MODULES_PERCEPTION_OBSTACLE_FUSION_INTERFACE_BASE_FUSION_H_
// SAMPLE CODE:
//
// class MyObjectFusion : public BaseFusion {
// public:
//     MyObjectFusion() : BaseFusion() {}
//     virtual ~MyObjectFusion() {}
//
//     virtual bool init() override {
//         // Do something.
//         return true;
//     }
//
//     virtual bool fuse(
//              const std::vector<SensorObjects>& multi_sensor_objects,
//              std::vector<ObjectPtr>* fused_objects) override {
//
//          // Do something.
//          return true;
//      }
//
//      virtual std::string name() const override {
//          return "MyObjectFusion";
//      } //
// };
//
// // Register plugin.
// REGISTER_FUSION(MyObjectFusion);
////////////////////////////////////////////////////////
// USING CODE:
//
// BaseFusion* fusion =
//  BaseFusionRegisterer::get_instance_by_name("MyObjectFusion");
// using fusion to do somethings.
// ////////////////////////////////////////////////////
#include <vector>

#include "modules/common/macro.h"
#include "modules/perception/lib/base/registerer.h"
#include "modules/perception/lib/pcl_util/pcl_types.h"
#include "modules/perception/obstacle/base/types.h"
#include "modules/perception/obstacle/base/object.h"
 
namespace apollo {
namespace perception {
class BaseFusion {
public:
    BaseFusion() {}
    virtual ~BaseFusion() {}
    virtual bool init() = 0;
    // @brief: fuse objects from multi sensors(64-lidar, 16-lidar, radar...)
    // @param [in]: multi sensor objects.
    // @param [out]: fused objects.
    virtual bool fuse(
            const std::vector<SensorObjects>& multi_sensor_objects,
            std::vector<ObjectPtr>* fused_objects) = 0;
    virtual std::string name() const = 0;
private:
    DISALLOW_COPY_AND_ASSIGN(BaseFusion);
};
REGISTER_REGISTERER(BaseFusion);
#define REGISTER_FUSION(name) REGISTER_CLASS(BaseFusion, name)
}  // namespace perception
}  // namespace apollo
#endif  // MODULES_PERCEPTION_OBSTACLE_FUSION_INTERFACE_BASE_FUSION_H_
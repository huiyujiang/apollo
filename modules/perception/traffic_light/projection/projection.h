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
#ifndef MODULES_PERCEPTION_TRAFFIC_LIGHT_PROJECTION_BASE_LIGHTS_PROJECTION_H
#define MODULES_PERCEPTION_TRAFFIC_LIGHT_PROJECTION_BASE_LIGHTS_PROJECTION_H

#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "modules/perception/traffic_light/interface/base_projection.h"

namespace apollo {
namespace perception {
namespace traffic_light {

//@brief Projection for each Camera.
class SingleBoundaryBasedProjection : public BaseProjection {
 public:
  virtual bool project(const CameraCoeffient &camera_coeffient,
                       const Eigen::Matrix4d &pose,
                       const apollo::hdmap::Signal &tl_info,
                       Light *light) const override;

 private:
  bool project_point(const CameraCoeffient &coeffient,
                     const Eigen::Matrix4d &pose,
                     const apollo::common::Point3D &point, int *center_x,
                     int *center_y) const;

  bool project_point_distort(const CameraCoeffient &coeffient,
                             const Eigen::Matrix4d &pose,
                             const apollo::common::PointENU &point,
                             int *center_x, int *center_y) const;

  Eigen::Matrix<double, 2, 1> pixel_denormalize(
      const Eigen::Matrix<double, 2, 1> &pt2d,
      const Eigen::Matrix<double, 3, 4> &camera_intrinsic,
      const Eigen::Matrix<double, 5, 1> &distort_params) const;
};

REGISTER_PROJECTION(SingleBoundaryBasedProjection);
}  // namespace traffic_light
}  // namespace perception
}  // namespace apollo

#endif  // MODULES_PERCEPTION_TRAFFIC_LIGHT_PROJECTION_BASE_LIGHTS_PROJECTION_H

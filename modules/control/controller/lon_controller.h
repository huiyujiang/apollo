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

/**
 * @file
 * @brief Defines the LonController class.
 */

#ifndef MODULES_CONTROL_CONTROLLER_LON_CONTROLLER_H_
#define MODULES_CONTROL_CONTROLLER_LON_CONTROLLER_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "modules/common/vehicle_state/vehicle_state_provider.h"
#include "modules/control/common/interpolation_2d.h"
#include "modules/control/common/pid_controller.h"
#include "modules/control/common/trajectory_analyzer.h"
#include "modules/control/controller/controller.h"
#include "modules/control/filters/digital_filter.h"
#include "modules/control/filters/digital_filter_coefficients.h"

/**
 * @namespace apollo::control
 * @brief apollo::control
 */
namespace apollo {
namespace control {

/**
 * @class LonController
 *
 * @brief Longitudinal controller, to compute brake / throttle values.
 */
class LonController : public Controller {
 public:
  /**
   * @brief constructor
   */
  LonController();

  /**
   * @brief destructor
   */
  virtual ~LonController();

  /**
   * @brief initialize Longitudinal Controller
   * @param control_conf control configurations
   * @return Status initialization status
   */
  common::Status Init(const ControlConf *control_conf) override;

  /**
   * @brief compute brake / throttle values based on current vehicle status
   *        and target trajectory
   * @param localization vehicle location
   * @param chassis vehicle status e.g., speed, acceleration
   * @param trajectory trajectory generated by planning
   * @param cmd control command
   * @return Status computation status
   */
  common::Status ComputeControlCommand(
      const localization::LocalizationEstimate *localization,
      const canbus::Chassis *chassis,
      const planning::ADCTrajectory *trajectory,
      control::ControlCommand *cmd) override;

  /**
   * @brief reset longitudinal controller
   * @return Status reset status
   */
  common::Status Reset() override;

  /**
   * @brief stop longitudinal controller
   */
  void Stop() override;

  /**
   * @brief longitudinal controller name
   * @return string controller name in string
   */
  std::string Name() const override;

 protected:
  void ComputeLongitudinalErrors(const TrajectoryAnalyzer *trajectory,
                                 const double preview_time,
                                 SimpleLongitudinalDebug *debug);

 private:
  void SetDigitalFilterPitchAngle(const LonControllerConf &lon_controller_conf);

  void LoadControlCalibrationTable(
      const LonControllerConf &lon_controller_conf);

  void SetDigitalFilter(double ts, double cutoff_freq,
                        DigitalFilter *digital_filter);

  void CloseLogFile();

  const localization::LocalizationEstimate *localization_ = nullptr;
  const canbus::Chassis *chassis_ = nullptr;

  std::unique_ptr<Interpolation2D> control_interpolation_;
  const planning::ADCTrajectory *trajectory_message_ = nullptr;
  std::unique_ptr<TrajectoryAnalyzer> trajectory_analyzer_;

  std::string name_;
  bool controller_initialized_ = false;

  PIDController speed_pid_controller_;
  PIDController station_pid_controller_;

  FILE *speed_log_file_ = nullptr;

  DigitalFilter digital_filter_pitch_angle_;

  const ControlConf *control_conf_ = nullptr;
};
}  // namespace control
}  // namespace apollo
#endif  // MODULES_CONTROL_CONTROLLER_LONGITUDINAL_CONTROLLER_H_

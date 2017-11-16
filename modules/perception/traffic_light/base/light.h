// Copyright 2016 Baidu Inc. All Rights Reserved.
// @author: Hengyu Li (lihengyu@baidu.com)
// @file: light.h
// @brief: traffic light basic data struction definition.

#ifndef MODULES_PERCEPTION_TRAFFIC_LIGHT_BASE_LIGHT_H
#define MODULES_PERCEPTION_TRAFFIC_LIGHT_BASE_LIGHT_H

#include <eigen3/Eigen/Core>
#include <opencv2/opencv.hpp>
#include "modules/perception/proto/traffic_light_detection.pb.h"
#include "modules/map/proto/map_signal.pb.h"

#include "modules/perception/traffic_light/base/image.h"

namespace apollo {
namespace perception {
namespace traffic_light {

typedef apollo::perception::TrafficLight::Color TLColor;
const TLColor UNKNOWN_COLOR = apollo::perception::TrafficLight::UNKNOWN;
const TLColor GREEN = apollo::perception::TrafficLight::GREEN;
const TLColor RED = apollo::perception::TrafficLight::RED;
const TLColor YELLOW = apollo::perception::TrafficLight::YELLOW;
const TLColor BLACK = apollo::perception::TrafficLight::BLACK;
//When the light has been covered by some objected, the color returned.
const TLColor DEFAULT_UNKNOWN_COLOR = apollo::perception::TrafficLight::UNKNOWN;

enum DetectionClassId {
  UNKNOWN_CLASS = -1,
  VERTICAL_CLASS = 0,
  QUADRATE_CLASS = 1,
  HORIZONTAL_CLASS = 2
};

//@brief Light Region in the Image
struct LightRegion {
  //roi is marked by map & projection, it may be too large or not accuracy.
  cv::Rect projection_roi;

  std::vector<cv::Rect> debug_roi;
  std::vector<float> debug_roi_detect_scores;

  //rectified_roi is the region marked by Rectifier, it should be accuracy and small.
  //A Light can have more than one roi, Rectifier may found more than one region seems like TL.
  //Each roi can has many candidates, Recognizer can votes for them.
  cv::Rect rectified_roi;
  bool is_detected = false;
  bool is_selected = false;
  // detection 输出结果，实际取值 -1、0 或 1
  // 为 0 则 UnityRecognize 中使用白天模型
  // 为 1 则使用夜晚模型
  DetectionClassId detect_class_id = UNKNOWN_CLASS;

  // output score by detection
  float detect_score = 0.0f;

  std::string to_string() const {
    std::ostringstream oss;
    oss << "LightRegion: [projection_roi:<(" << projection_roi.tl().x << ","
        << projection_roi.tl().y << "),(" << projection_roi.br().x << ","
        << projection_roi.br().y << "] ";
    return oss.str();
  }
};

//@brief Light Status
struct LightStatus {
  // Traffic light color status.
  TLColor color = UNKNOWN_COLOR;
  // How confidence about the detected results, between 0 and 1.
  double confidence = 0.0;

  std::string to_string() const {
    std::string light_color = (color == UNKNOWN_COLOR ? "unknown color" :
                               (color == RED ? "red" :
                                (color == GREEN ? "green" :
                                 (color == YELLOW ? "yellow" : "black"))));
    //std::string light_color;
    std::ostringstream oss;
    oss << "Status: [color:" << light_color << " confidence:" << confidence << "]";
    return oss.str();
  }
};

//@brief A Traffic Light.
struct Light {
  Light() = default;

  explicit Light(const apollo::hdmap::Signal &signal) :
      info(signal) {
  }
  apollo::hdmap::Signal info;    // Light info in the map.
  LightRegion region;  // Light region on the image.
  LightStatus status;  // Light Status.

  std::string to_string() const {
    std::ostringstream oss;
    oss << "Light: {" << status.to_string() << region.to_string()
        << "Signal Info: [" << info.ShortDebugString() << "]}";
    return oss.str();
  }
};

std::ostream &operator<<(std::ostream &os, const Light &light);

typedef std::shared_ptr<Light> LightPtr;
typedef std::vector<LightPtr> LightPtrs;

//@brief compute stopline to car's distance
double stopline_distance(
    const Eigen::Matrix4d &car_pose,
    const ::google::protobuf::RepeatedPtrField<::apollo::hdmap::Curve> &stoplines);

//@brief compute traffic light to car's distance
double trafficlight_distance(
    const Eigen::Matrix4d &car_pose,
    const ::google::protobuf::RepeatedPtrField<::apollo::hdmap::Subsignal> &subsignal);

}  // namespace traffic_light
}  // namespace perception
}  // namespace apollo

#endif  // MODULES_PERCEPTION_TRAFFIC_LIGHT_BASE_LIGHT_H
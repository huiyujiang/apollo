// Copyright 2016 Baidu Inc. All Rights Reserved.
// @autho: zhengwenchao(zhengwenchao@baidu.com)
// @file: image.cpp
// @brief: Image Class

#include "modules/perception/traffic_light/base/image.h"

#include <iomanip>

#include <gflags/gflags.h>
#include "modules/common/log.h"
//#include "modules/drivers/usb_cam/include/usb_cam/utility.h"
#include <cv_bridge/cv_bridge.h>

DEFINE_int32(double_show_precision, 14, "When output a double data, the precision.");

namespace apollo {
namespace perception {
namespace traffic_light {

bool Image::Init(const double &ts, const CameraId &device_id, const cv::Mat &mat) {
  contain_mat_ = true;
  contain_image_ = true;
  timestamp_ = ts,
  device_id_ = device_id,
  mat_ = mat.clone();
  ADEBUG << *this << " init.";
  return true;
}
bool Image::Init(const double &ts, const CameraId &device_id,
                 const std::shared_ptr<sensor_msgs::Image> image_data) {
  contain_mat_ = false;
  contain_image_ = true;
  timestamp_ = ts,
  device_id_ = device_id,
  image_data_ = image_data;
  ADEBUG << *this << " init.";
  return true;
}

double Image::ts() const {
  return timestamp_;
}

CameraId Image::device_id() const {
  return device_id_;
}

std::string Image::device_id_str() const {
  if (kCameraIdToStr.find(device_id_) == kCameraIdToStr.end()) {
    return "unkown device(camera)";
  }
  return kCameraIdToStr.at(device_id_);
}
bool Image::GenerateMat() {
  if (!contain_mat_) {

    try {
//      if (image_data_->encoding.compare("rgb8") == 0) {
//        cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(image_data_, "bgr8");
//        mat_ = cv_ptr->image;
//      } else
      if (image_data_->encoding.compare("yuyv") == 0) {
        //TODO:: yuyv 2 rgb rgb 2 bgr
//        unsigned char* yuv = (unsigned char*)&(image_data_->data[0]);
//        mat_ = cv::Mat(image_data_->height,image_data_->width,CV_8UC3);
//        usb_cam::yuyv2rgb_avx(yuv,mat_.data,image_data_->height*image_data_->width);
//        cv::cvtColor(mat_,mat_,CV_RGB2BGR);
      }

      contain_mat_ = true;
      AINFO << "Generate done " << mat_.size();
    }
    catch (const cv_bridge::Exception &e) {
      AERROR << "TLPreprocessorSubnode trans msg to cv::Mat failed." << e.what();
      return false;
    }
  }
  return true;
}
cv::Mat Image::mat() const {
  return mat_;
}
cv::Size Image::size() const {
  if (contain_mat_) {
    return mat_.size();
  } else {
    return cv::Size(image_data_->width, image_data_->height);
  }
}

std::ostream &operator<<(std::ostream &os, const Image &image) {

  if (image.contain_mat_) {
    os << "Image device_id:" << static_cast<int>(image.device_id_)
       << " device_id_str: " << image.device_id_str()
       << " ts:" << std::setprecision(FLAGS_double_show_precision) << image.timestamp_
       << " size:" << image.mat_.size();
  } else {
    os << "Image not inited.";
  }
  return os;
}

}// namespace traffic_light
}// namespace perception
}// namespace apollo

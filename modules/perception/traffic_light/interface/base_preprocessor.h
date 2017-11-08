// Copyright (c) 2017 Baidu.com, Inc. All Rights Reserved
// @author guiyilin(guiyilin@baidu.com)
// @date 2017/08/07
// @file: base_preprocessor.h
// @brief: 
// 

#ifndef ADU_PERCEPTION_TRAFFIC_LIGHT_INTERFACE_BASE_PREPROCESSOR_H
#define ADU_PERCEPTION_TRAFFIC_LIGHT_INTERFACE_BASE_PREPROCESSOR_H
#include <string>
#include <vector>

#include "lib/base/noncopyable.h"
#include "lib/base/registerer.h"
#include "module/perception/traffic_light/base/image.h"
#include "module/perception/traffic_light/base/light.h"

namespace adu {
namespace perception {
namespace traffic_light {

//@brief Reviser is the class is to revise the perception result.
//       It may use history info(Tracker) or some else info.
class BasePreprocessor {
 public:
  BasePreprocessor() = default;

  virtual ~BasePreprocessor() = default;

  //@brief init the reviser.
  virtual bool init() = 0;

  //@brief Revise's name
  virtual std::string name() const = 0;
};

REGISTER_REGISTERER(BasePreprocessor);
#define REGISTER_PREPROCESSOR(name) REGISTER_CLASS(BasePreprocessor, name)

} // namespace traffic_light
} // namespace perception
} // namespace adu

#endif  // ADU_PERCEPTION_TRAFFIC_LIGHT_INTERFACE_BASE_PREPROCESSOR_H


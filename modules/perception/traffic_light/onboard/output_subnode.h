// Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
// @author Ruidong Tang (tangruidong@baidu.com)
// @file: output_subnode.h
#ifndef ADU_PERCEPTION_TRAFFIC_LIGHT_ONBOARD_OUTPUT_SUBNODE_H
#define ADU_PERCEPTION_TRAFFIC_LIGHT_ONBOARD_OUTPUT_SUBNODE_H

#include <map>
#include <string>
#include <array>

#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>

#include "onboard/subnode.h"
#include "onboard/stream_output.h"
#include "module/perception/traffic_light/base/image_lights.h"

namespace adu {
namespace perception {
namespace traffic_light {

class TLProcData;

class TLOutputSubnode : public onboard::Subnode {
 public:
  TLOutputSubnode() = default;
  virtual ~TLOutputSubnode() {
    _proc_data = nullptr;
  }

  virtual onboard::Status proc_events() override;

 protected:
  virtual bool init_internal() override;
 private:
  bool init_shared_data();
  bool init_output_stream();

  bool transform_message(const onboard::Event &event,
                         const std::shared_ptr<ImageLights> &lights,
                         boost::shared_ptr<std_msgs::String> *msg) const;
  bool proc_upstream_data(const onboard::Event &event);

 private:
  std::unique_ptr<onboard::StreamOutput> _output_stream;
  TLProcData *_proc_data = nullptr;

  // save BGR colors
  //static std::map<std::string, std::array<int, 3> > _s_color_table;

  DISALLOW_COPY_AND_ASSIGN(TLOutputSubnode);
};

}  // namespace traffic_light
}  // namespace perception
}  // namespace adu

#endif  // ADU_PERCEPTION_TRAFFIC_LIGHT_ONBOARD_OUTPUT_SUBNODE_H

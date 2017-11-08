//
// Created by gaohan02 on 16-12-2.
//

#ifndef PERCEPTION_COLOR_DECISION_H
#define PERCEPTION_COLOR_DECISION_H

#include <modules/perception/traffic_light/interface/green_interface.h>
#include "modules/perception/traffic_light/interface/base_reviser.h"

namespace apollo {
namespace perception {
namespace traffic_light {

class ColorReviser : public BaseReviser {
 public:
  ColorReviser() {
  }

  //@brief init the reviser.
  virtual bool Init();
  //@brief reviser revise  the perception result
  //       ASSERT(rectifed_result.size == perception_result.size)
  //@param [in] option
  //@param [in/out] rectifed_result
  //@return true/false
  virtual bool Revise(const ReviseOption &option, std::vector<LightPtr> *lights) override;

  //@brief Revise's name
  virtual std::string name() const;

 private:
  float blink_time_;
  int enable_;
  std::map<std::string, TLColor> color_map_;
  std::map<std::string, double> time_map_;
  static std::map<TLColor, std::string> s_color_strs_;
};

}
}
}

#endif //PERCEPTION_COLOR_DECISION_H

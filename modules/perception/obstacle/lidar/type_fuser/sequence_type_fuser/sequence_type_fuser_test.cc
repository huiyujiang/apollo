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

#include "gtest/gtest.h"
#include "modules/perception/obstacle/lidar/type_fuser/sequence_type_fuser/sequence_type_fuser.h"
#include "modules/perception/lib/config_manager/config_manager.h"
#include "modules/perception/common/perception_gflags.h"

namespace apollo {
namespace perception {

class SequenceTypeFuserTest : public testing::Test {
 protected:
  SequenceTypeFuserTest() {}
  virtual ~SequenceTypeFuserTest() {}
  void SetUp() {
    RegisterFactorySequenceTypeFuser();
    FLAGS_work_root = "modules/perception";
    FLAGS_config_manager_path = "conf/config_manager.config";
    ConfigManager* config_manager = ConfigManager::instance();
    if (!config_manager->Init()) {
        AERROR << "Fail to init config manager.";
        return;
    }
    fuser_.reset(new SequenceTypeFuser);
  }
  void TearDown() {}
  void build_objects();
  std::size_t id_map(size_t i);
  void generate_smooth_prob(std::vector<float>* prob, std::size_t id, float seed);
 protected:
  std::shared_ptr<SequenceTypeFuser> fuser_;
  std::vector<std::vector<ObjectPtr> > objects_;
  std::vector<double> timestamps_;
  static const std::size_t s_sequence_length_;
  static const std::size_t s_object_num_;
};

const std::size_t SequenceTypeFuserTest::s_sequence_length_ = 10;
const std::size_t SequenceTypeFuserTest::s_object_num_ = 4;

std::size_t SequenceTypeFuserTest::id_map(std::size_t i) {
    if (i == 0) {
        return 0;
    } else {
        return i + 2;
    }
}

void SequenceTypeFuserTest::generate_smooth_prob(std::vector<float>* prob, 
        std::size_t id, float seed) {
    float p = (1.f - seed) / (VALID_OBJECT_TYPE - 1);
    for (std::size_t i = 0; i < VALID_OBJECT_TYPE; ++i) {
        prob->at(id_map(i)) = p;
    }
    prob->at(id_map(id)) = seed;
}

void SequenceTypeFuserTest::build_objects() {
    objects_.resize(s_sequence_length_);
    timestamps_.resize(s_sequence_length_);
    for (size_t i = 0; i < s_sequence_length_; ++i) {
        timestamps_[i] = static_cast<double>(i) * 0.1;
        objects_[i].resize(s_object_num_);
        for (size_t j = 0; j < s_object_num_; ++j) {
            objects_[i][j].reset(new Object);
            objects_[i][j]->track_id = static_cast<int>(j);
            objects_[i][j]->score = 0.95;
            std::vector<float>& type_probs = objects_[i][j]->type_probs;
            type_probs.resize(MAX_OBJECT_TYPE, 0.0);
            generate_smooth_prob(&type_probs, j, 0.7);
            std::cout << j << "th object prob: ";
            for (size_t m = 0; m < type_probs.size(); ++m) {
                std::cout << type_probs[m] << " ";
            }
            std::cout << std::endl;
        }
    }
}

TEST_F(SequenceTypeFuserTest, TestFuseType) {
    build_objects();
    EXPECT_TRUE(fuser_->init());
    EXPECT_STREQ(fuser_->name().c_str(), "SequenceTypeFuser");
    TypeFuserOptions options;
    for (size_t i = 0; i < s_sequence_length_; ++i) {
        options.timestamp = timestamps_[i];
        EXPECT_TRUE(fuser_->fuse_type(options, &objects_[i]));
    }
    for (size_t j = 0; j < s_object_num_; ++j) {
        EXPECT_EQ(static_cast<std::size_t>(objects_.back()[j]->type), id_map(j));
    }
}

}  // namespace perception
}  // namespace apollo
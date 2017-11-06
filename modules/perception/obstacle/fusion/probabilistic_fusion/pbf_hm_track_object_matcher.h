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

#ifndef ADU_PERCEPTION_OBSTACLE_FUSION_PROBABILISTIC_FUSION_PBF_HM_TRACK_OBJECT_MATCHER_H
#define ADU_PERCEPTION_OBSTACLE_FUSION_PROBABILISTIC_FUSION_PBF_HM_TRACK_OBJECT_MATCHER_H

#include <utility>
#include <vector>
#include "modules/common/macro.h"
#include "modules/perception/obstacle/common/hungarian_bigraph_matcher.h"
#include "modules/perception/obstacle/fusion/probabilistic_fusion/pbf_sensor_object.h"
#include "modules/perception/obstacle/fusion/probabilistic_fusion/pbf_track.h"
#include "modules/perception/obstacle/fusion/probabilistic_fusion/pbf_base_track_object_matcher.h"
#include "modules/perception/obstacle/common/graph_util.h"

namespace apollo {
namespace perception {

class PbfHmTrackObjectMatcher : public PbfBaseTrackObjectMatcher {
public:
    PbfHmTrackObjectMatcher();
    virtual ~PbfHmTrackObjectMatcher();
    
    bool match(std::vector<PbfTrackPtr>& fusion_tracks,
        std::vector<PbfSensorObjectPtr>& sensor_objects,
        const TrackObjectMatcherOptions& options,
        std::vector<TrackObjectPair>& assignments,
        std::vector<int>& unassigned_fusion_tracks,
        std::vector<int>& unassigned_sensor_tracks, 
        std::vector<double>& track2measurements_dist, 
        std::vector<double>& measurement2track_dist)  override;

    bool init() override;

    std::string name() const override;

protected:
    void compute_association_mat(const std::vector<PbfTrackPtr>& fusion_tracks,
            const std::vector<PbfSensorObjectPtr>& sensor_objects,
            const std::vector<int>& unassigned_fusion_tracks,
            const std::vector<int>& unassigned_sensor_objects,
            const Eigen::Vector3d& ref_point,
            std::vector<std::vector<double> >& association_mat);
    bool hm_assign(const std::vector<std::vector<double> >& association_mat,
            std::vector<TrackObjectPair>& assignments,
            std::vector<int>& unassigned_fusion_tracks,
            std::vector<int>& unassigned_sensor_objects);
    void minimize_assignment(const std::vector<std::vector<double> > &association_mat,
        std::vector<int> &ref_idx,
        std::vector<int> &new_idx);
    void compute_connected_components(
        const std::vector<std::vector<double> >& association_mat,
        float connected_threshold,
        std::vector<std::vector<int> >& track_components,
        std::vector<std::vector<int> >& obj_components);
private:
    DISALLOW_COPY_AND_ASSIGN(PbfHmTrackObjectMatcher);

};

} // namespace perception
} // namespace apollo

#endif

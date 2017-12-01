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
#ifndef MODULES_PERCEPTION_TRAFFIC_LIGHT_UTILS_H
#define MODULES_PERCEPTION_TRAFFIC_LIGHT_UTILS_H

#include <opencv2/opencv.hpp>

namespace apollo {
namespace perception {
namespace traffic_light {

uint64_t TimestampDouble2Int64(double ts);

void ClearBox(cv::Rect &rect);

bool BoxIsValid(const cv::Rect &box, const cv::Size &size);
cv::Rect RefinedBox(cv::Rect box, const cv::Size &size);

cv::Point2f GetCenter(cv::Rect box);

float GetDistance(cv::Point2f, cv::Point2f);

float Get2dGaussianScore(cv::Point2f p1, cv::Point2f p2, float sigma1,
                         float sigma2);

float Get1dGaussianScore(float x1, float x2, float sigma);
}
}
}

#endif  // GREEN_UTILS_H

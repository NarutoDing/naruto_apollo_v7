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

#include "modules/prediction/common/prediction_util.h"

#include <algorithm>

#include "modules/common/math/linear_interpolation.h"
#include "modules/prediction/common/prediction_gflags.h"

namespace apollo {
namespace prediction {
namespace math_util {

double Normalize(const double value, const double mean, const double std) {
  const double eps = 1e-10;
  return (value - mean) / (std + eps);
}

double Relu(const double value) { return (value > 0.0) ? value : 0.0; }

std::vector<double> Softmax(const std::vector<double>& value, bool use_exp) {
  std::vector<double> result;
  double sum = 0.0;
  for (std::size_t i = 0; i < value.size(); ++i) {
    double exp_value = std::max(0.001, value[i]);
    if (use_exp) {
      exp_value = std::exp(value[i]);
    }
    sum += exp_value;
    result.push_back(exp_value);
  }
  for (std::size_t i = 0; i < value.size(); ++i) {
    result[i] = result[i] / sum;
  }
  return result;
}

int SolveQuadraticEquation(const std::vector<double>& coefficients,
                           std::pair<double, double>* roots) {
  if (coefficients.size() != 3) {
    return -1;
  }
  const double a = coefficients[0];
  const double b = coefficients[1];
  const double c = coefficients[2];
  if (std::fabs(a) <= std::numeric_limits<double>::epsilon()) {
    return -1;
  }

  double delta = b * b - 4.0 * a * c;
  if (delta < 0.0) {
    return -1;
  }

  double sqrt_delta = std::sqrt(delta);
  roots->first = (-b + sqrt_delta) * 0.5 / a;
  roots->second = (-b - sqrt_delta) * 0.5 / a;
  return 0;
}

double EvaluateQuinticPolynomial(const std::array<double, 6>& coeffs,
                                 const double t, const uint32_t order,
                                 const double end_t, const double end_v) {
  if (t >= end_t) {
    switch (order) {
      case 0: {
        double end_value =
            ((((coeffs[5] * end_t + coeffs[4]) * end_t + coeffs[3]) * end_t +
              coeffs[2]) *
                 end_t +
             coeffs[1]) *
                end_t +
            coeffs[0];
        return end_value + end_v * (t - end_t);
      }
      case 1: {
        return end_v;
      }
      default: { return 0.0; }
    }
  }
  switch (order) {
    case 0: {
      return ((((coeffs[5] * t + coeffs[4]) * t + coeffs[3]) * t + coeffs[2]) *
                  t +
              coeffs[1]) *
                 t +
             coeffs[0];
    }
    case 1: {
      return (((5.0 * coeffs[5] * t + 4.0 * coeffs[4]) * t + 3.0 * coeffs[3]) *
                  t +
              2.0 * coeffs[2]) *
                 t +
             coeffs[1];
    }
    case 2: {
      return (((20.0 * coeffs[5] * t + 12.0 * coeffs[4]) * t) +
              6.0 * coeffs[3]) *
                 t +
             2.0 * coeffs[2];
    }
    case 3: {
      return (60.0 * coeffs[5] * t + 24.0 * coeffs[4]) * t + 6.0 * coeffs[3];
    }
    case 4: {
      return 120.0 * coeffs[5] * t + 24.0 * coeffs[4];
    }
    case 5: {
      return 120.0 * coeffs[5];
    }
    default:
      return 0.0;
  }
}

double EvaluateQuarticPolynomial(const std::array<double, 5>& coeffs,
                                 const double t, const uint32_t order,
                                 const double end_t, const double end_v) {
  if (t >= end_t) {
    switch (order) {
      case 0: {
        double end_value =
            (((coeffs[4] * end_t + coeffs[3]) * end_t + coeffs[2]) * end_t +
             coeffs[1]) *
                end_t +
            coeffs[0];
        return end_value + (t - end_t) * end_v;
      }
      case 1: {
        return end_v;
      }
      default: { return 0.0; }
    }
  }
  switch (order) {
    case 0: {
      return (((coeffs[4] * t + coeffs[3]) * t + coeffs[2]) * t + coeffs[1]) *
                 t +
             coeffs[0];
    }
    case 1: {
      return ((4.0 * coeffs[4] * t + 3.0 * coeffs[3]) * t + 2.0 * coeffs[2]) *
                 t +
             coeffs[1];
    }
    case 2: {
      return (12.0 * coeffs[4] * t + 6.0 * coeffs[3]) * t + 2.0 * coeffs[2];
    }
    case 3: {
      return 24.0 * coeffs[4] * t + 6.0 * coeffs[3];
    }
    case 4: {
      return 24.0 * coeffs[4];
    }
    default:
      return 0.0;
  }
}

double EvaluateCubicPolynomial(const std::array<double, 4>& coefs,
                               const double t, const uint32_t order,
                               const double end_t, const double end_v) {
  if (t > end_t) {
    switch (order) {
      case 0: {
        double end_value =
            ((coefs[3] * end_t + coefs[2]) * end_t + coefs[1]) * end_t +
            coefs[0];
        return end_value + (t - end_t) * end_v;
      }
      case 1: {
        return end_v;
      }
      default: { return 0.0; }
    }
  }

  switch (order) {
    case 0: {
      return ((coefs[3] * t + coefs[2]) * t + coefs[1]) * t + coefs[0];
    }
    case 1: {
      return (3.0 * coefs[3] * t + 2.0 * coefs[2]) * t + coefs[1];
    }
    case 2: {
      return 6.0 * coefs[3] * t + 2.0 * coefs[2];
    }
    case 3: {
      return 6.0 * coefs[3];
    }
    default:
      return 0.0;
  }
}

double GetSByConstantAcceleration(const double v0, const double acceleration,
                                  const double t) {
  if (acceleration > -FLAGS_double_precision) {
    return v0 * t + 0.5 * acceleration * t * t;
  }
  double t_stop = v0 / (-acceleration);
  double t_actual = std::min(t, t_stop);
  return v0 * t_actual + 0.5 * acceleration * t_actual * t_actual;
}

}  // namespace math_util

namespace predictor_util {

using apollo::common::PathPoint;
using apollo::common::TrajectoryPoint;

void TranslatePoint(const double translate_x, const double translate_y,
                    TrajectoryPoint* point) {
  if (point == nullptr || !point->has_path_point()) {
    AERROR << "Point is nullptr or has NO path_point.";
    return;
  }
  const double original_x = point->path_point().x();
  const double original_y = point->path_point().y();
  point->mutable_path_point()->set_x(original_x + translate_x);
  point->mutable_path_point()->set_y(original_y + translate_y);
}

void GenerateFreeMoveTrajectoryPoints(
    Eigen::Matrix<double, 6, 1>* state,
    const Eigen::Matrix<double, 6, 6>& transition, double theta,
    const double start_time, const std::size_t num, const double period,
    std::vector<TrajectoryPoint>* points) {
  double x = (*state)(0, 0);
  double y = (*state)(1, 0);
  double v_x = (*state)(2, 0);
  double v_y = (*state)(3, 0);
  double acc_x = (*state)(4, 0);
  double acc_y = (*state)(5, 0);

  for (std::size_t i = 0; i < num; ++i) {
    double speed = std::hypot(v_x, v_y);
    double acc = 0.0;
    if (speed <= std::numeric_limits<double>::epsilon()) {
      speed = 0.0;
      v_x = 0.0;
      v_y = 0.0;
      acc_x = 0.0;
      acc_y = 0.0;
      acc = 0.0;
    } else {
      speed = std::fmin(speed, FLAGS_vehicle_max_speed);
    }

    // update theta and acc
    if (speed > std::numeric_limits<double>::epsilon()) {
      if (points->size() > 0) {
        TrajectoryPoint& prev_trajectory_point = points->back();
        PathPoint* prev_path_point = prev_trajectory_point.mutable_path_point();
        theta = std::atan2(y - prev_path_point->y(), x - prev_path_point->x());
        prev_path_point->set_theta(theta);
        acc = (speed - prev_trajectory_point.v()) / period;
        prev_trajectory_point.set_a(acc);
      }
    } else {
      if (points->size() > 0) {
        theta = points->back().path_point().theta();
      }
    }

    // update state
    (*state)(2, 0) = v_x;
    (*state)(3, 0) = v_y;
    (*state)(4, 0) = acc_x;
    (*state)(5, 0) = acc_y;

    // obtain position
    x = (*state)(0, 0);
    y = (*state)(1, 0);

    // Generate trajectory point
    TrajectoryPoint trajectory_point;
    PathPoint path_point;
    path_point.set_x(x);
    path_point.set_y(y);
    path_point.set_z(0.0);
    path_point.set_theta(theta);
    trajectory_point.mutable_path_point()->CopyFrom(path_point);
    trajectory_point.set_v(speed);
    trajectory_point.set_a(acc);
    trajectory_point.set_relative_time(start_time +
                                       static_cast<double>(i) * period);
    points->emplace_back(std::move(trajectory_point));

    // Update position, velocity and acceleration
    (*state) = transition * (*state);
    x = (*state)(0, 0);
    y = (*state)(1, 0);
    v_x = (*state)(2, 0);
    v_y = (*state)(3, 0);
    acc_x = (*state)(4, 0);
    acc_y = (*state)(5, 0);
  }
}

double AdjustSpeedByCurvature(const double speed, const double curvature) {
  if (std::abs(curvature) < FLAGS_turning_curvature_lower_bound) {
    return speed;
  }
  if (std::abs(curvature) > FLAGS_turning_curvature_upper_bound) {
    return FLAGS_speed_at_upper_curvature;
  }
  return apollo::common::math::lerp(
      FLAGS_speed_at_lower_curvature, FLAGS_turning_curvature_lower_bound,
      FLAGS_speed_at_upper_curvature, FLAGS_turning_curvature_upper_bound,
      curvature);
}

}  // namespace predictor_util
}  // namespace prediction
}  // namespace apollo

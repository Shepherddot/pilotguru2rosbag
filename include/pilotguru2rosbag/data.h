//
// Created by liu on 22-9-1.
//

#ifndef SRC_PILOTGURU2ROSBAG_INCLUDE_PILOTGURU2ROSBAG_DATA_H_
#define SRC_PILOTGURU2ROSBAG_INCLUDE_PILOTGURU2ROSBAG_DATA_H_

#include <vector>
#include <string>

#include <opencv2/core.hpp>

#include <Eigen/Core>

using Vector6d = Eigen::Matrix<double, 6, 1>;

struct Data {
  std::string video_name_;
  std::vector<double> image_times_;

  std::vector<Vector6d> imus_;
  std::vector<double> imu_times_;

  std::vector<Eigen::Vector2d> gps_;
  std::vector<double> gps_times_;

  double absolute_start_time_;
  double record_start_time_;

  void parseDir(std::string& dir_name);
};

#endif //SRC_PILOTGURU2ROSBAG_INCLUDE_PILOTGURU2ROSBAG_DATA_H_

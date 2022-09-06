//
// Created by liu on 22-9-1.
//

#include "pilotguru2rosbag/data.h"

#include <fstream>

void Data::parseDir(std::string &dir_name) {
  std::string image_timestamp_file = dir_name + "/pre/image.txt";
  std::string imu_file = dir_name + "/pre/imu.txt";
  std::string video_file = dir_name + "/pre/video.mp4";

  video_name_ = video_file;

  std::ifstream image_time_file;
  image_time_file.open(image_timestamp_file);

  std::string image_data_line;
  while (std::getline(image_time_file, image_data_line)) {
    std::stringstream ss;
    ss << image_data_line;
    std::string frame_id;
    uint64_t timestamp;

    ss >> frame_id;
    ss >> timestamp;

    image_times_.push_back(timestamp * 0.000001);
  }

  std::ifstream imu_data_file;
  imu_data_file.open(imu_file);

  std::string imu_data_item;
  while (std::getline(imu_data_file, imu_data_item)) {
    std::stringstream ss;
    ss << imu_data_item;

    uint64_t timestamp;
    double gyro_x;
    double gyro_y;
    double gyro_z;

    double acc_x;
    double acc_y;
    double acc_z;

    ss >> timestamp >> gyro_x >> gyro_y >> gyro_z >> acc_x >> acc_y >> acc_z;

    Vector6d data_collect;
    data_collect << gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z;

    imu_times_.push_back(timestamp * 0.000001);
    imus_.push_back(data_collect);
  }



}

//
// Created by liu on 22-9-1.
//



#include <iostream>
#include <memory>
#include <fstream>
#include <chrono>

#include <rosbag/bag.h>

#include <opencv2/core.hpp>

#include "pilotguru2rosbag/data.h"
#include "pilotguru2rosbag/image_process.h"
#include "pilotguru2rosbag/imu_process.h"

int main() {
  std::string data_path = "/home/liu/test_dataset/2022_03_12-10_52_59";
  Data data;
  data.parseDir(data_path);

  uint64_t microseconds_since_epoch = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

  data.absolute_start_time_ = microseconds_since_epoch * 0.000001;
  data.record_start_time_ = data.image_times_[0];

  rosbag::Bag bag_file(data_path + "/ros_bag.bag", rosbag::BagMode::Write);

//  ImageProcess img_processor(data, bag_file);
  ImuProcess imu_processor(data, bag_file);

  std::cout << "read data." << std::endl;

  return 0;
}

//
// Created by liu on 22-9-1.
//

#include "pilotguru2rosbag/imu_process.h"

#include <sensor_msgs/Imu.h>

ImuProcess::ImuProcess(const Data &data, rosbag::Bag &bag_file) {
  processData(data, bag_file);
}

void ImuProcess::processData(const Data &data, rosbag::Bag &bag_file) {
  for(int i = 0; i < data.imu_times_.size(); i++){
    sensor_msgs::Imu imu;

    double msg_time = data.absolute_start_time_ + (data.imu_times_[i] - data.record_start_time_);

    ros::Time cur_time = ros::Time(msg_time);
    imu.header.stamp = cur_time;
    imu.header.seq = i;
    imu.header.frame_id = "imu";

    imu.angular_velocity.x = data.imus_[i][0];
    imu.angular_velocity.y = data.imus_[i][1];
    imu.angular_velocity.z = data.imus_[i][2];

    imu.linear_acceleration.x = data.imus_[i][3];
    imu.linear_acceleration.y = data.imus_[i][4];
    imu.linear_acceleration.z = data.imus_[i][5];
    
    bag_file.write("/mobile/imu", cur_time, imu);
  }
}

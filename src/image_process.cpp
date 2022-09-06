//
// Created by liu on 22-9-1.
//

#include "pilotguru2rosbag/image_process.h"

#include <iostream>

#include <sensor_msgs/Image.h>
#include <ros/time.h>
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/Header.h>

#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

ImageProcess::ImageProcess(const Data &data, rosbag::Bag &bag_file) {
  processData(data, bag_file);
}

void ImageProcess::processData(const Data &data, rosbag::Bag &bag_file) {
  cv::VideoCapture cap(data.video_name_);

  // Check if camera opened successfully
  if (!cap.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    return;
  }

  for (int idx = 0; idx < data.image_times_.size(); idx++) {
    cv::Mat frame;
    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    cv::imshow("curr frame", frame);
    cv::waitKey(30);

    double msg_time = data.absolute_start_time_ + (data.image_times_[idx] - data.record_start_time_);

    double time_diff = data.image_times_[idx] - data.record_start_time_;

    std::cout << std::fixed << time_diff << std::endl;

    std_msgs::Header img_header;
    ros::Time cur_time(msg_time);
    img_header.stamp = cur_time;
    img_header.seq = idx;

    cv_bridge::CvImage img_bridge = cv_bridge::CvImage(img_header, sensor_msgs::image_encodings::BGR8, frame);
    sensor_msgs::Image ros_img;
    img_bridge.toImageMsg(ros_img);
    bag_file.write("/mobile/image", cur_time, ros_img);
  }

  // When everything done, release the video capture object
  cap.release();
}

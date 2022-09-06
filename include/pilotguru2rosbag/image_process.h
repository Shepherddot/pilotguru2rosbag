//
// Created by liu on 22-9-1.
//

#ifndef SRC_PILOTGURU2ROSBAG_INCLUDE_PILOTGURU2ROSBAG_IMAGE_PROCESS_H_
#define SRC_PILOTGURU2ROSBAG_INCLUDE_PILOTGURU2ROSBAG_IMAGE_PROCESS_H_

#include "data.h"

#include <rosbag/bag.h>

class ImageProcess {
 public:
  ImageProcess(const Data &data, rosbag::Bag &bag_file);

 private:
  void processData(const Data &data, rosbag::Bag &bag_file);
};

#endif //SRC_PILOTGURU2ROSBAG_INCLUDE_PILOTGURU2ROSBAG_IMAGE_PROCESS_H_

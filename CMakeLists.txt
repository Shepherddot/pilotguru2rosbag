cmake_minimum_required(VERSION 3.0.2)
project(pilotguru2rosbag)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

SET(CMAKE_BUILD_TYPE Debug)
MESSAGE("-- Build type: " ${CMAKE_BUILD_TYPE})
#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-Wno-deprecated")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
geometry_msgs
roscpp
sensor_msgs
rospy
rosbag
cv_bridge
std_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)
set(EIGEN3_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/eigen)
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/eigen)

set(Boost_NO_BOOST_CMAKE ON)
#set(Boost_DIR /usr)
set(Boost_DIR /usr/local)
set(Boost_INCLUDE_DIR ${Boost_DIR}/include)
set(Boost_LIBRARY_DIR_RELEASE ${Boost_DIR}/lib)
find_package(Boost REQUIRED COMPONENTS serialization filesystem)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pilotguru2rosbag
#  CATKIN_DEPENDS geometry_msgs roscpp sensor_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
include
${catkin_INCLUDE_DIRS}
${OpenCV_INCLUDE_DIRS}
${EIGEN3_INCLUDE_DIR}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
src/data.cpp
src/image_process.cpp
src/imu_process.cpp
src/gps_process.cpp
)

target_link_libraries(${PROJECT_NAME}
${catkin_LIBRARIES}
${OpenCV_LIBS}
${Boost_LIBRARIES}
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}_node
src/main_loader.cpp
)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
${catkin_LIBRARIES}
${OpenCV_LIBS}
${PROJECT_NAME}
${Boost_LIBRARIES}
)

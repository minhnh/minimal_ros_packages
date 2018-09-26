cmake_minimum_required(VERSION 2.8.3)
project(smach_minimal)


## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  message_generation
)


# package specific setup, will be more relevant for C++ code, but required nonetheless
catkin_package(
   CATKIN_DEPENDS message_runtime
)

# install executables
install(PROGRAMS
  scripts/traffic_lights.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/ros/launch
)

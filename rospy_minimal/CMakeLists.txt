cmake_minimum_required(VERSION 3.5)
project(rospy_minimal)


## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
)

# setup Python package
catkin_python_setup()

# package specific setup, will be more relevant for C++ code, but required nonetheless
catkin_package()

# install executables
install(PROGRAMS
  scripts/talker_node
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/ros/launch
)


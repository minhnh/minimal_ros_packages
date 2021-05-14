cmake_minimum_required(VERSION 3.5)
project(action_minimal)


## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  actionlib_msgs
  msg_minimal
)

# Message files
add_action_files(
  DIRECTORY action
  FILES Minimal.action
)
generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs msg_minimal
)

# package specific setup, will be more relevant for C++ code, but required nonetheless
catkin_package(
  CATKIN_DEPENDS actionlib_msgs
)

# install executables
install(PROGRAMS
  scripts/action_test_python_server
  scripts/action_test_python_client
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/ros/launch
)


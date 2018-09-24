cmake_minimum_required(VERSION 2.8.3)
project(msg_minimal)


## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  message_generation
)

# Message files
add_message_files(
  FILES
    Minimal.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

# package specific setup, will be more relevant for C++ code, but required nonetheless
catkin_package(
  CATKIN_DEPENDS message_runtime
)

# install executables
install(PROGRAMS
  scripts/msg_test_node
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/ros/launch
)


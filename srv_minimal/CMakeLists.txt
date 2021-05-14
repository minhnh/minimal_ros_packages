cmake_minimum_required(VERSION 3.5)
project(srv_minimal)


## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  message_generation
  msg_minimal
)

# Message files
add_service_files(
  FILES
    MinimalService.srv
)
generate_messages(
  DEPENDENCIES
    std_msgs
    msg_minimal
)

# package specific setup, will be more relevant for C++ code, but required nonetheless
catkin_package(
  CATKIN_DEPENDS message_runtime
)

# install executables
install(PROGRAMS
  scripts/srv_test_python_server
  scripts/srv_test_python_client
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# install launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/ros/launch
)


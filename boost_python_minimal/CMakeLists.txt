cmake_minimum_required(VERSION 3.5)
project(boost_python_minimal)

## Compile as C++14, supported in ROS Kinetic and newer
add_compile_options(-std=c++14)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

set(PY_MAJOR 3)
set(PY_MINOR 8)
set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED COMPONENTS python${PY_MAJOR}${PY_MINOR})
find_package(PythonLibs ${PY_MAJOR}.${PY_MINOR} REQUIRED)

# setup Python package
catkin_python_setup()

# package specific setup, will be more relevant for C++ code, but required nonetheless
catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PYTHON_INCLUDE_DIRS}
)

# add 'boost_python_minimal' library
add_library(${PROJECT_NAME}
  src/cpp/bytes_example.cpp
)
add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

# add wrapper library for loading in Python
add_library(_cpp_wrapper SHARED
  src/cpp/boost_python_module.cpp
)
# change output directory, so python can find the module, and set prefix to ""
# to omit the default "lib".
set_target_properties(_cpp_wrapper PROPERTIES
  PREFIX ""
  LIBRARY_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_PYTHON_DESTINATION}
)
target_link_libraries(_cpp_wrapper
  ${PROJECT_NAME}
  ${Boost_LIBRARIES}
  ${PYTHON_LIBRARIES}
  ${catkin_LIBRARIES}
)

# Test pure C++ code
add_executable(bytes_example_test
  scripts/bytes_example_test.cpp
)
target_link_libraries(bytes_example_test
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############
# includes
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
# install executables
install(PROGRAMS
  scripts/bytes_example_test.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

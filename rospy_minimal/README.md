# Minimal ROS package using `rospy`

## Folder structure
```
.
├── CMakeLists.txt
├── launch
│   └── talker_node.launch
├── package.xml
├── README.md
├── scripts
│   └── talker_node
├── setup.py
└── src
    └── rospy_minimal
        ├── __init__.py
        └── talker.py
```

## [`CMakeLists.txt`](CMakeLists.txt)
Important `CMake` commands:
* `project()`: specifies project name
* `find_package()`: specifies package dependencies
* `catkin_python_setup()`: setup the Python package, will require a `setup.py` to be present.
* `install()`: (optional) will copy executables, launch files to the installation location. This will be more relevant
when more complex workspace setup are needed.

More details can be found on [`CMakeLists.txt` ROS documentation](http://wiki.ros.org/catkin/CMakeLists.txt).

## [`package.xml`](package.xml)
Mostly used to specify dependencies, allowing `rosdep` tool to handle them correctly.

More details can be found on [`package.xml` ROS documentation](http://wiki.ros.org/catkin/package.xml).

## [`setup.py`](setup.py)

File needed for setting up a Python package. Function `generate_distutils_setup` is imported to setup the package to
work with `catkin` in ROS. In this case the package name is `rospy_minimal`, and the setup script will look under the
`src` folder, specifically for `src/rospy_minimal/__init__.py`, to create the Python package.

More info on this file in a regular Python package independent of ROS can be found
[here](https://docs.python.org/3/distutils/setupscript.html).

## Launch file
File specifying configurations for running executables. In this case [`talker_node.launch`](launch/talker_node.launch)
will start the [`talker_node`](scripts/talker_node) script. Important XML tags:
* `arg`: specifies launch file argument, allow passing arguments to launch file. An example using `roslaunch` command
with [`talker_node.launch`](launch/talker_node.launch) would be:
```roslaunch rospy_minimal talker_node.launch talk_topic:=talking_topic```.
* `param`: allow passing parameters into executables. These parameters can't be accessed in Python using the function
`rospy.get_param` like in the [`talker_node`](scripts/talker_node) script.

More details can be found on the ROS documentation for [`roslaunch` command line tool](http://wiki.ros.org/roslaunch)
and for [launch file syntax](http://wiki.ros.org/roslaunch/XML).

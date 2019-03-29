# Minimal ROS package using `rospy`

This tutorial will walk you through creating and testing simple publisher and subscriber for communicating ROS messages.
For Python examples of ROS publishers and subscribers, please refer to the
[ROS tutorial](http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber(python)).

## Folder structure
```
.
├── CMakeLists.txt
├── launch
│   └── talker_node.launch
├── package.xml
├── README.md
├── scripts
│   └── talker_node
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

## Foundation course tasks
* To test the node, launch `talker_node.launch`.
```sh
$ roslaunch rospy_minimal talker_node.launch
```
* Add a publisher of type `string` using the topic name stored in `self._talk_topic` variable.
* In the `talk` function publish the string stored in `self._message`. Running `rostopic echo` on the talk topic
should produce the stored string message:
```sh
$ rostopic echo /talk
data: "hello world!"
---
```
* Create a subscriber which listens to messages of type `string` using the topic name stored in `self._listen_topic`,
and the `self._subscriber_cb` callback function.
* Update `self._message` with data from the string messages in `self._subscriber_cb`. If all works well, when you
publish on the `/listen` topic:
```
$ rostopic pub /listen std_msgs/String "data: 'oioi'"
```
the `/talk` topic will print the corresponding messages:
```
$ rostopic echo /talk
data: "oioi"
---
```

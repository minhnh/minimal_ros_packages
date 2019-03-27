# Minimal ROS package with message generation for action
Minimal working example for defining a new ROS action. More details on `actionlib` generation can be found on
[ROS documentation for `actionlib`](https://wiki.ros.org/actionlib) and the
[`actionlib` tutorial](http://wiki.ros.org/actionlib_tutorials/Tutorials).

## Folder structure
```
.
├── action
│   └── Minimal.action
├── CMakeLists.txt
├── launch
│   └── action_test_server.launch
├── package.xml
├── README.md
└── scripts
    ├── action_test_python_client
    └── action_test_python_server
```

## [`CMakeLists.txt`](CMakeLists.txt)
Compared to a bare ROS package, the following changes are needed:

* add `actionlib_msgs` to `find_package()` under `COMPONENTS`
* add `actionlib_msgs` to `catkin_package()` under `CATKIN_DEPENDS`
* add action file(s) (in this case [`Minimal.action`](action/Minimal.action):
```
add_action_files(
   DIRECTORY action
   FILES Minimal.action
 )
```
* generate messages with the appropriate dependencies:
```
generate_messages(
   DEPENDENCIES actionlib_msgs std_msgs
)
```
* `add_action_files()` and `generate_messages()` need to be called before `catkin_packge()`, else will cause error.

## [`package.xml`](package.xml)
Dependencies on message generation and `actionlib_msgs` need to be added:
```XML
<build_depend>actionlib_msgs</build_depend>
<exec_depend>message_generation</exec_depend>
<exec_depend>actionlib_msgs</exec_depend>
```
## Running and testing the action server

* To start the action server, launch [`action_test_server.launch`](launch/action_test_server.launch):
```sh
$ roslaunch action_minimal action_test_server.launch
```
* To test the action server using the [client test script](scripts/action_test_python_client), a sample execution
would be:
```sh
$ rosrun action_minimal action_test_python_client 1 2 sum
```
Full usage messge:
```sh
$ rosrun action_minimal action_test_python_client --help
usage: action_test_python_client [-h] [--action-name ACTION_NAME]
                                 x y operation

Tool to test the minimal action server

positional arguments:
  x                     first number
  y                     second number
  operation             operation

optional arguments:
  -h, --help            show this help message and exit
  --action-name ACTION_NAME, -a ACTION_NAME
                        name of the minimal action server
```

## Foundation course tasks

* Modify [`Minimal.action`](action/Minimal.action) to have a `msg_minimal/Minimal` field named `goal` as the action goal
request, and a `float32` field named `result` as the action result.
* Build and check in Python. If all is well, the following commands should work:
```sh
$ python2
Python 2.7.12 (default, Dec  4 2017, 14:50:18)
[GCC 5.4.0 20160609] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> from action_minimal.msg import MinimalAction, MinimalGoal, MinimalResult
>>> action_goal = MinimalGoal()
>>> action_goal.goal
a: 0.0
b: 0.0
operation: ''
>>> action_result = MinimalResult()
>>> action_result
result: 0.0
```
* Add an action server of type `action_minimal/MinimalAction` to the `MinimalActionServer` class in the script
[`action_test_python_server`](scripts/action_test_python_server).
* Handle arithmatic operation in the `_execute_cb` function, then call `set_succeeded()` using the appropriate
action result.

# Minimal ROS package with message generation
Minimal working example for defining a new ROS message. More details on message generation, i.e. built-in types, can be
found on [ROS documentation for messages](https://wiki.ros.org/msg).

## Folder structure
```
.
├── CMakeLists.txt
├── launch
│   └── msg_test_node.launch
├── msg
│   └── Minimal.msg
├── package.xml
├── README.md
└── scripts
    └── msg_test_node
```

## [`CMakeLists.txt`](CMakeLists.txt)
Compared to a bare ROS package, the following changes are needed:
* add `message_generation` to `find_package()` under `COMPONENTS`
* add `message_runtime` to `catkin_package()` under `CATKIN_DEPENDS`
* add message file(s) (in this case [`Minimal.msg`](msg/Minimal.msg), which need to be in the `msg` folder in package
directory else will cause error):
```
add_message_files(
  FILES
    Minimal.msg
)
```
* generate messages:
```
generate_messages(
  DEPENDENCIES
  std_msgs
)
```
* `add_message_files()` and `generate_messages()` need to be called before `catkin_packge()`, else will error.

## [`package.xml`](package.xml)
Dependencies on message generation need to be added:
```XML
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```

## ToDo's
1. modify [`Minimal.msg`](msg/Minimal.msg) to have numeric `a`, `b` fields and string `operation`
2. build and check in python
```
$ python2
Python 2.7.12 (default, Dec  4 2017, 14:50:18)
[GCC 5.4.0 20160609] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> from msg_minimal.msg import Minimal
>>> msg = Minimal()
>>> msg.a
0.0
>>> msg.b
0.0
>>> msg.operation
''
```
3. add a subscriber to [`msg_test_node`](scripts/msg_test_node) which listens to `minimal_topic` of type
`msg_minimal/Minimal`
4. launch [`msg_test_node.launch`](launch/msg_test_node.launch)
```
$ roslaunch msg_minimal msg_test_node.launch
```
5. publish to the topic specified in step 3 the correct `msg_minimal/Minimal` message.

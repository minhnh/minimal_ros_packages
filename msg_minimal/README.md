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

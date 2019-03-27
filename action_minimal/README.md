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

## Foundation course tasks

TODO(minhnh)

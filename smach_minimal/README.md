# Minimal ROS package with message generation
Minimal working example for defining a new ROS service. More details on service generation can be found on
[ROS documentation for services](https://wiki.ros.org/srv) and the
[service client Python tutorial](http://wiki.ros.org/ROS/Tutorials/WritingServiceClient(python)).

## Folder structure
```
.
├── CMakeLists.txt
├── launch
│   └── srv_test_server.launch
├── package.xml
├── README.md
├── scripts
│   └── srv_test_python_server
└── srv
    └── Minimal.srv
```

## [`CMakeLists.txt`](CMakeLists.txt)
Compared to a bare ROS package, the following changes are needed:
* add `message_generation` to `find_package()` under `COMPONENTS`
* add `message_runtime` to `catkin_package()` under `CATKIN_DEPENDS`
* add service file(s) (in this case [`MinimalService.srv`](srv/Minimal.srv), which need to be in the `srv` folder in package
directory else will cause error):
```
add_service_files(
  FILES
    Minimal.srv
)
```
* generate messages:
```
generate_messages(
  DEPENDENCIES
    std_msgs
)
```
* `add_service_files()` and `generate_messages()` need to be called before `catkin_packge()`, else will error.

## [`package.xml`](package.xml)
Dependencies on message generation need to be added:
```XML
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```

# Minimal ROS package with message generation for services
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
│   ├── srv_test_python_client
│   └── srv_test_python_server
└── srv
    └── MinimalService.srv
```

## [`CMakeLists.txt`](CMakeLists.txt)
Compared to a bare ROS package, the following changes are needed:
* add `message_generation` to `find_package()` under `COMPONENTS`
* add `message_runtime` to `catkin_package()` under `CATKIN_DEPENDS`
* add service file(s) (in this case [`MinimalService.srv`](srv/Minimal.srv), which need to be in the `srv` folder in
package directory else will cause error):
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

## TODO's
1. modify [`MinimalService.srv`](srv/MinimalService.srv) to have a `msg_minimal/Minimal` field named `request` as
request, and a `float32` field named `result` as response.
2. build and check in python
```
$ python2
Python 2.7.12 (default, Dec  4 2017, 14:50:18)
[GCC 5.4.0 20160609] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> from srv_minimal.srv import MinimalService, MinimalServiceResponse, MinimalServiceRequest
>>> req = MinimalServiceRequest()
>>> req.request
a: 0.0
b: 0.0
operation: ''
>>> req.request.__class__
<class 'msg_minimal.msg._Minimal.Minimal'>
>>> res = MinimalServiceResponse()
>>> res.result
0.0
```
3. add service of type `srv_minimal/MinimalService` to the [`srv_test_python_server`](scripts/srv_test_python_server).
4. launch [`srv_test_server.launch`](launch/srv_test_server.launch)
```
$ roslaunch srv_minimal srv_test_server.launch
```
5. execute the [`srv_test_python_client`](scripts/srv_test_python_client) script:
```
$ ./srv_test_python_client 1 2 sum
```
to view the help message:
```
$ ./srv_test_python_client --help
usage: srv_test_python_client [-h] [--service-name SERVICE_NAME] a b operation

Tool to test the minimal service

positional arguments:
  a                     first number
  b                     second number
  operation             operation

optional arguments:
  -h, --help            show this help message and exit
  --service-name SERVICE_NAME, -s SERVICE_NAME
                        name of the minimal service
```

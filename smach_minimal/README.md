# Minimal ROS package with a `smach` state machine
Minimal working example for defining a new ROS `smach` state machine. More details on service generation can be found
on [ROS documentation for `smach`](http://wiki.ros.org/smach) and the
[`smach`tutorials](http://wiki.ros.org/smach/Tutorials).

## Folder structure
```
.
├── CMakeLists.txt
├── images
│   ├── traffic_light_sm.png
│   └── traffic_light_sm.xml
├── launch
│   └── smach_minimal.launch
├── package.xml
├── README.md
└── scripts
    └── traffic_lights
```

## TODOs
![alt text](images/traffic_light_sm.png "Logo Title Text 1")

* add `YELLOW` and `GREEN` states to simulate a traffic light
* add delays in the `execute` functions
* add a `flag` field in `userdata` to control what's returned from `execute`
* add conditions using the `flag` field so the state transitions are like that in the above figure
* run launch file:
```
roslaunch smach_minimal smach_minimal.launch
```

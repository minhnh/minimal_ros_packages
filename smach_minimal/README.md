# Minimal ROS package with a `smach` state machine
Minimal working example for defining a new ROS `smach` state machine. More details on service generation can be found
on [ROS documentation for `smach`](http://wiki.ros.org/smach) and the
[`smach`tutorials](http://wiki.ros.org/smach/Tutorials).

## Folder structure
```
.
├── CMakeLists.txt
├── launch
│   └── smach_minimal_launch.launch
├── package.xml
├── README.md
└── scripts
    └── traffic_lights.py
```

## TODOs
TODO(minhnh): add state machine transition map
* add `YELLOW` and `GREEN` states to simulate a traffic light
* add delays in the `execute` functions
* add a `flag` field in `userdata` to control what's returned from `execute`
* add conditions using the `flag` field so the state transitions are like that
in the above figure

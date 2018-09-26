#!/usr/bin/env python
import roslib
import rospy
import smach
import smach_ros


# define state Red
class Red(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Stop'])
        self.counter = 0

    def execute(self, userdata):
        rospy.loginfo('***Executing state Red***')
        rospy.sleep(5)
        return 'Stop'


# define state Yellow


#define state green


def main():
    rospy.init_node('traffic_lights')

    # flag=0
    # Create a SMACH state machine
    sm = smach.StateMachine(outcomes=['DONE'])

    # Open the container
    with sm:
        # Add states to the container
        smach.StateMachine.add('RED', Red(),
                               transitions={'Stop':'RED'})

    # Execute SMACH plan
    outcome = sm.execute()


if __name__ == '__main__':
    main()

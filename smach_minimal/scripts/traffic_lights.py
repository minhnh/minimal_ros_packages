#!/usr/bin/env python

import roslib
import rospy
import smach
import smach_ros

# define state Red
class Red(smach.State):
    flag = 0
    def __init__(self):
        smach.State.__init__(self, outcomes=['Stop'])
        self.counter = 0

    def execute(self, userdata):
        rospy.loginfo('***Executing state Red***')
        if self.counter < 3:
            self.counter += 1
            rospy.sleep(5)
            Red.flag=0
            return 'Stop'
        else:
            return 'Wait'


# define state Yellow
class Yellow(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Wait', 'Stop'])

    def execute(self, userdata):
        rospy.loginfo('===Executing state Yellow===')
        rospy.sleep(2)
        if Red.flag==1:
            return 'Stop'
        if Red.flag==0:
            return 'Wait'



#define state green
class Green(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Go'])

    def execute(self, userdata):
        rospy.loginfo('...Executing green state...')
        rospy.sleep(2)
        Red.flag=1
        return 'Go'

def main():
    rospy.init_node('traffic_lights')

    # flag=0
    # Create a SMACH state machine
    sm = smach.StateMachine(outcomes=['Go'])

    # Open the container
    with sm:
        # Add states to the container
        smach.StateMachine.add('Red', Red(),
                               transitions={'Stop':'Yellow'})
        smach.StateMachine.add('Yellow', Yellow(),
                               transitions={'Wait':'Green', 'Stop':'Red'})
        smach.StateMachine.add('Green', Green(),
                               transitions={'Go':'Yellow'})


    # Execute SMACH plan
    outcome = sm.execute()



if __name__ == '__main__':
    main()

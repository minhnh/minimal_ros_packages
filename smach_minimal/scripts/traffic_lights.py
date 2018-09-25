#!/usr/bin/env python

import roslib;
import rospy
import smach
import smach_ros

# define state Foo
class Red(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Stop','Wait','Go'])
        self.counter = 0

    def execute(self, userdata):
        rospy.loginfo('Executing state Red')
        if self.counter < 3:
            self.counter += 1
            return 'outcome1'
        else:
            return 'outcome2'


# define state Bar
class Yellow(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['Stop','Wait','Go'])

    def execute(self, userdata):
        rospy.loginfo('Executing state BAR')
        return 'outcome1'
        




def main():
    rospy.init_node('smach_example_state_machine')

    # Create a SMACH state machine
    sm = smach.StateMachine(outcomes=['outcome4'])

    # Open the container
    with sm:
        # Add states to the container
        smach.StateMachine.add('FOO', Foo(), 
                               transitions={'outcome1':'BAR', 'outcome2':'outcome4'})
        smach.StateMachine.add('BAR', Bar(), 
                               transitions={'outcome1':'FOO'})

    # Execute SMACH plan
    outcome = sm.execute()



if __name__ == '__main__':
    main()


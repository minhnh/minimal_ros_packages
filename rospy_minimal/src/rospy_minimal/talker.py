import rospy
from std_msgs.msg import String


class Talker(object):
    """
    Minimal Publisher, Subscriber practice
    Check documentation at http://wiki.ros.org/rospy/Overview/Publishers%20and%20Subscribers
    for creating publishers and subscribers in Python
    """
    def __init__(self, talk_topic, listen_topic):
        self._talk_topic = talk_topic
        self._listen_topic = listen_topic
        self._message = 'hello world!'
        # TODO(minhnh) create a rospy.Publisher which publishes std_msgs/String messages
        self._publisher = None
        # TODO(minhnh) create a rospy.Subscriber which subscribes to std_msgs/String messages using
        # self._subscriber_cb as callback
        self._subscriber = None

    def talk(self):
        if self._publisher is None:
            print('you have not created a rospy.Publisher object, will not publish the message "%s" to topic "%s"'
                  % (self._message, self._talk_topic))
            return

        # TODO(minhnh) create publisher, remove the line raising error, create and publish a String message containing
        # self._message as data
        raise NotImplementedError()

    def _subscriber_cb(self, msg):
        # TODO(minhnh) set self._message to the message data
        raise NotImplementedError()

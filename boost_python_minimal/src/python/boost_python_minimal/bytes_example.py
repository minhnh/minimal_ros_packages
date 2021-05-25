# from std_msgs.msg import String as StringMsg
try:
    from cStringIO import StringIO as IOClass   # Python 2.x
except ImportError:
    from io import BytesIO as IOClass           # Python 3.x
from boost_python_minimal._cpp_wrapper import _print_string_message


def print_string_message(msg):
    buf = IOClass()
    msg.serialize(buf)
    _print_string_message(buf.getvalue())

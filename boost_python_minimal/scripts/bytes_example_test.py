#!/usr/bin/env python
import argparse
from std_msgs.msg import String as StringMsg
from boost_python_minimal._cpp_wrapper import _print_bytes
from boost_python_minimal.bytes_example import print_string_message, bytes_to_string_message


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Example usage of the minimal Boost Python library.')
    parser.add_argument('test_string', help='a string to test Boost Python functions')
    args = parser.parse_args()

    print(f"received test string: '{args.test_string}'")

    print("now printing a bytearray containing test string using exposed C++ code...")
    test_bytes = bytes(args.test_string, 'utf-8')
    _print_bytes(test_bytes)

    print("now creating a ROS string message and print it using exposed C++ code...")
    msg = StringMsg()
    msg.data = args.test_string
    print_string_message(msg)

    print("now converting a bytearray containing test string to a ROS string message using exposed C++ code...")
    msg2 = bytes_to_string_message(test_bytes)
    print(f"message: type={type(msg2)}, data='{msg2.data}'")

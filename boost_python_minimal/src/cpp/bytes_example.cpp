#include <iostream>
#include <string>
#include <vector>
#include <std_msgs/String.h>
#include <boost_python_minimal/bytes_example.h>

namespace boost_python_minimal{

void print_bytes(const std::string &testString) {
    std::cout << "this was printed by C++ code: " << testString << std::endl;
}

void byte_from_string_message(const std_msgs::String &pStringMsg, std::vector<uint8_t> &pOutBytes) {

}

}

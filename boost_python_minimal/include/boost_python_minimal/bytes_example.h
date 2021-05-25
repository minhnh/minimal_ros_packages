#ifndef BOOST_PYTHON_MINIMAL_BYTES_EXAMPLE_H
#define BOOST_PYTHON_MINIMAL_BYTES_EXAMPLE_H

#include <string>
#include <vector>
#include <std_msgs/String.h>

namespace boost_python_minimal {

void print_bytes(const std::string &);

void byte_from_string_message(const std_msgs::String &pStringMsg, std::vector<uint8_t> &pOutBytes);

}

#endif  // BOOST_PYTHON_MINIMAL_BYTES_EXAMPLE_H

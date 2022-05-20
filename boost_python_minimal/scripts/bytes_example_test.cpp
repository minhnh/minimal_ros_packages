#include <string>
#include <boost_python_minimal/bytes_example.h>

namespace bpm = boost_python_minimal;

int main(int argc, char** argv) {
    std::string testString("hello world!");
    if (argc < 2) {
        bpm::print_bytes(testString);
        return 0;
    }

    // print all arguments
    while (--argc) {
        testString.assign(*(++argv));
        bpm::print_bytes(testString);
    }
    return 0;
}
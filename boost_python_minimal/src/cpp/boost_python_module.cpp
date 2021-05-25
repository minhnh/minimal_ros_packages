#include <boost/python.hpp>
#include <boost/shared_array.hpp>
#include <ros/serialization.h>
#include <std_msgs/String.h>
#include <boost_python_minimal/bytes_example.h>

namespace bp = boost::python;
namespace bpm = boost_python_minimal;

namespace boost_python_minimal {
    void print_bytes_wrapper(PyObject* pPyBuffer) {
        if (!PyObject_CheckBuffer(pPyBuffer)) {
            //raise TypeError using standard boost::python mechanisms
            PyErr_SetString(PyExc_TypeError, "data do not have buffer type");
            return;
        }

        Py_buffer view;
        PyObject_GetBuffer(pPyBuffer, &view, PyBUF_SIMPLE);

        std::string data;
        data.assign((char *) view.buf, (int)view.len);
        print_bytes(data);

        PyBuffer_Release(&view);
    }

    void print_string_message_wrapper(PyObject* pPyBuffer) {
        if (!PyObject_CheckBuffer(pPyBuffer)) {
            //raise TypeError using standard boost::python mechanisms
            PyErr_SetString(PyExc_TypeError, "data do not have buffer type");
            return;
        }

        Py_buffer view;
        PyObject_GetBuffer(pPyBuffer, &view, PyBUF_SIMPLE);

        auto pyBufPtr = (uint8_t *) view.buf;
        auto pyBufLen = (int) view.len;
        boost::shared_array<uint8_t> buffer(new uint8_t[pyBufLen]);
        for (size_t i = 0; i < pyBufLen; ++i)
        {
            buffer[i] = pyBufPtr[i];
        }
        PyBuffer_Release(&view);

        ros::serialization::IStream stream(buffer.get(), pyBufLen);
        std_msgs::String msg;
        ros::serialization::Serializer<std_msgs::String>::read(stream, msg);

        print_bytes(msg.data);

        return;
    }
}

BOOST_PYTHON_MODULE(_cpp_wrapper)
{
    bp::def("_print_bytes", bpm::print_bytes_wrapper);
    bp::def("_print_string_message", bpm::print_string_message_wrapper);
}

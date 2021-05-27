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
            PyErr_SetString(PyExc_TypeError, "data do not have buffer type");
            bp::throw_error_already_set();
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
            bp::throw_error_already_set();
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
        try {
            ros::serialization::Serializer<std_msgs::String>::read(stream, msg);
        } catch (const std::exception &exp) {
            std::string errMsg("failed to deserialize message: ");
            errMsg.append(exp.what());
            PyErr_SetString(PyExc_RuntimeError, errMsg.c_str());
            return;
        }

        print_bytes(msg.data);

        return;
    }

    bp::object bytes_to_string_message_wrapper(PyObject* pPyBuffer) {
        if (!PyObject_CheckBuffer(pPyBuffer)) {
            PyErr_SetString(PyExc_TypeError, "data do not have buffer type");
            bp::throw_error_already_set();
        }

        std_msgs::String rosMsg;
        Py_buffer view;
        PyObject_GetBuffer(pPyBuffer, &view, PyBUF_SIMPLE);
        rosMsg.data.assign((char *) view.buf, (int)view.len);
        PyBuffer_Release(&view);

        size_t serialSize = ros::serialization::serializationLength(rosMsg);
        char * buffer = new char[serialSize];
        ros::serialization::OStream stream((uint8_t *) buffer, static_cast<uint32_t>(serialSize));
        ros::serialization::serialize(stream, rosMsg);

        PyObject* memView = PyMemoryView_FromMemory(buffer, serialSize, PyBUF_WRITE);
        return bp::object(bp::handle<>(memView));
    }
}

BOOST_PYTHON_MODULE(_cpp_wrapper)
{
    bp::def("_print_bytes", bpm::print_bytes_wrapper);
    bp::def("_print_string_message", bpm::print_string_message_wrapper);
    bp::def("_bytes_to_string_message", bpm::bytes_to_string_message_wrapper);
}

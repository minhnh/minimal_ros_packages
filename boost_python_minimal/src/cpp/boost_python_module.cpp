#include <boost/python.hpp>
#include <boost_python_minimal/bytes_example.h>

namespace bp = boost::python;
namespace bpm = boost_python_minimal;

namespace boost_python_minimal {
    void print_bytes_wrapper(bp::object buffer) {
        PyObject* py_buffer = buffer.ptr();
        if (!PyObject_CheckBuffer(py_buffer)) {
            //raise TypeError using standard boost::python mechanisms
            PyErr_SetString(PyExc_TypeError, "data do not have buffer type");
            return;
        }

        Py_buffer view;
        PyObject_GetBuffer(py_buffer, &view, PyBUF_SIMPLE);

        //you can also write checks here for length, verify the
        //buffer is memory-contiguous, etc.
        std::string data;
        data.assign((char *) view.buf, (int)view.len);

        print_bytes(data);
        PyBuffer_Release(&view);
    }
}

BOOST_PYTHON_MODULE(_cpp_wrapper)
{
    bp::def("_print_bytes", bpm::print_bytes_wrapper);
}

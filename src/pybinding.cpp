#include <pybind11/pybind11.h>
#include "bssolver.hpp"

namespace py = pybind11;

PYBIND11_MODULE(bssolver, m, py::mod_gil_not_used()){
   m.doc() = "Test";

   m.def("ComputeCallPrice", &ComputeCallPrice);
}

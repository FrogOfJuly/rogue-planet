//
// Created by Kirill Golubev on 28.04.2021.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "engine.h"
#include "find_alpha.h"

namespace py = pybind11;

PYBIND11_MODULE(earthcooling, m) {
    py::class_<engine>(m, "Engine")
            .def(py::init<double, double>())
            .def("init_physics", &engine::init_physics)
            .def("forward_pass", &engine::forward_pass)
            .def("backward_pass", &engine::backward_pass)
            .def("getT", &engine::getT)
            .def("enable_radiation", &engine::enable_radiation)
            .def("fill_with", &engine::fill_with);
    m.def("find_alpha", &find_alpha);
}
//
// Created by Kirill Golubev on 28.04.2021.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "engine.h"

namespace py = pybind11;

PYBIND11_MODULE(earthcooling, m) {
    py::class_<engine>(m, "Engine")
            .def(py::init<double, double>())
            .def("init_physics", &engine::init_physics,
                 py::arg("mantle_temperature"),
                 py::arg("thermal_conductivity"),
                 py::arg("specific_heat_capacity"),
                 py::arg("density"),
                 py::arg("upper_mantle"),
                 py::arg("troposphere_height"))
            .def("forward_pass", &engine::forward_pass)
            .def("backward_pass", &engine::backward_pass)
            .def("getT", &engine::getT)
            .def("enable_radiation", &engine::enable_radiation)
            .def("fill_with", &engine::fill_with)
            .def("N", &engine::N)
            .def("simulate_n_steps", &engine::simulate_n_steps)
            .def_readonly("R_c", &engine::R_c)
            .def_readonly("R_t", &engine::R_t);

}
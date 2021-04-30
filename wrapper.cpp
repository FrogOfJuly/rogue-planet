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
            .def("init_physics", &engine::init_physics,
                 py::arg("mantle_temperature"),
                 py::arg("surface_temperature"),
                 py::arg("thermal_conductivity"),
                 py::arg("specific_heat_capacity"),
                 py::arg("density"),
                 py::arg("upper_mantle"),
                 py::arg("troposphere_height"),
                 py::arg("interval_to_model"))
            .def("forward_pass", &engine::forward_pass)
            .def("backward_pass", &engine::backward_pass)
            .def("getT", &engine::getT)
            .def("getX", &engine::getX)
            .def("enable_radiation", &engine::enable_radiation)
            .def("fill_with", &engine::fill_with)
            .def("set_border_cond", &engine::set_border_cond)
            .def("simulate_n_steps", &engine::simulate_n_steps)
            .def("N", [](const engine *e) { return e->eval_params.N; })
            .def("R_c", [](const engine *e) { return e->phys_params.R_c; })
            .def("R_t", [](const engine *e) { return e->phys_params.R_t; })
            .def("dt", [](const engine *e) { return e->eval_params.dt; })
            .def("dx", [](const engine *e) { return e->eval_params.dx; })
            .def("Tl", [](const engine *e) { return e->phys_params.Tl; })
            .def("get_radiation_flux", &engine::get_radiation_flux)
            .def("passed_time", &engine::get_passed_time)
            .def("ticks_per_day", &engine::ticks_per_day);

    m.def("find_alpha", &find_alpha);

}
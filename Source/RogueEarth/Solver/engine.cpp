//
// Created by Kirill Golubev on 28.04.2021.
//

#include "engine.h"
#include <vector>

#include <cassert>
#include <iostream>

void print_array(const engine::grid &array) {
    return;
    for (auto &t : array) {
        std::cout << t << ", ";
    }
    std::cout << std::endl;
}

engine::engine(double dx, double dt) {
    eval_params.dx = dx;
    eval_params.dt = dt;
}

void engine::init_physics(double mantle_temerature,
                          double surface_temperature,
                          double thermal_conductivity,
                          double specific_heat_capacity,
                          double density,
                          double upper_mantle,
                          double troposphere_height,
                          double interval_to_model) {
    phys_params.T0 = mantle_temerature;
    phys_params.R_c = upper_mantle;
    phys_params.R_t = troposphere_height;
    phys_params.Ts = surface_temperature;

    phys_params.core.kappa = thermal_conductivity;
    phys_params.core.c = specific_heat_capacity;
    phys_params.core.rho = density;


    eval_params.L = phys_params.R_t - phys_params.R_c;
    eval_params.l = interval_to_model;

    phys_params.Tl = phys_params.T0 + (phys_params.Ts - phys_params.T0) /
                                      eval_params.L * (eval_params.L - eval_params.l);

    eval_params.N = (int) (eval_params.l / eval_params.dx);

    eval_params.J0 = phys_params.T0 * phys_params.T0 * phys_params.T0 * phys_params.sigma /
                     phys_params.core.kappa;
    eval_params.r = eval_params.dt / (eval_params.dx * eval_params.dx);


    alpha = std::vector<double>(eval_params.N + 1);
    beta = std::vector<double>(eval_params.N + 1);
    T = std::vector<double>(eval_params.N + 1);
}

void engine::fill_with(double t) {
    T[0] = 1;
    for (int i = 1; i < eval_params.N + 1; ++i) {
        T[i] = t / phys_params.T0;
    }
}

void engine::enable_radiation(double alpha_) {
    phys_params.sigma = consts.sigma_sb;
    eval_params.J0 = alpha_ * phys_params.T0 * phys_params.T0 * phys_params.T0 * phys_params.sigma /
                     phys_params.core.kappa;
}

void engine::forward_pass() {
    {
        double F_0 = phys_params.Tl / phys_params.T0;
        double B_0 = 1.0;
        double C_0 = 0.0;
        alpha[0] = -C_0 / B_0;
        beta[0] = F_0 / B_0;
    }
    print_array(T);
//    std::cout << "***********************************" << std::endl;
    for (int k = 1; k < eval_params.N; ++k) {
//        auto p = get_params(k);
//        double amend = p.spherical_amend;
        double amend = 1.0 / (consts.R_e - eval_params.l + eval_params.dx * k);
        double r = eval_params.r;

        double A = r + amend * r;
        double B = -1 - 2 * r - amend * 2 * r;
        double C = A;
        double F = -T[k - 1];

        alpha[k] = -C / (A * alpha[k - 1] + B);
        beta[k] = (F - A * beta[k - 1]) / (A * alpha[k - 1] + B);
    }
    print_array(alpha);
    print_array(beta);
}

void engine::backward_pass() {
    double B_N =
            eval_params.J0 * (T.back() * T.back() * T.back()) *
            eval_params.dx + 1;
//    std::cout << "J0: " << eval_params.J0 << std::endl;
    double A_N = -1;
    double F_N = 0;
    int N = eval_params.N;
    T[N] = (F_N - A_N * beta[N - 1]) / (A_N * alpha[N - 1] + B_N);
    for (int k = eval_params.N - 1; k >= 0; --k) {
        T[k] = alpha[k] * T[k + 1] + beta[k];
    }
    eval_params.cur_time += eval_params.dt;
//    std::cout << "-------------------------------" << std::endl;
    print_array(T);
//    std::cout << "===============================" << std::endl;
}

engine::grid engine::getT() const {
    std::vector<double> res(T.size());
    for (int i = 0; i < eval_params.N + 1; ++i) {
        res[i] = T[i] * phys_params.T0;
    }
    return res;
}

engine::grid engine::getX() const {
    grid res(T.size());
    for (int i = 0; i < eval_params.N + 1; ++i) {
        res[i] = (-eval_params.l + eval_params.dx * i) / 1000.0;
    }
    return res;
}

double engine::get_passed_time() const {
    double real_t = eval_params.cur_time * (phys_params.core.c * phys_params.core.rho) / phys_params.core.kappa;
    return real_t;
}

engine::grid engine::simulate_n_steps(int n) {
    for (int i = 0; i < n; ++i) {
        forward_pass();
        backward_pass();
    }
    return getT();
}


int engine::ticks_per_day() const {
    return int(3600.0 * 24.0 / (eval_params.dt * (phys_params.core.c * phys_params.core.rho) / phys_params.core.kappa));
}

void engine::set_border_cond(const engine::grid &data) {
    assert(T.size() - 1 == data.size());
    T[0] = 1.0;
    for (size_t i = 0; i < T.size(); ++i) {
        T[i + 1] = data[i] / phys_params.T0;
    }
}


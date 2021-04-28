//
// Created by Kirill Golubev on 28.04.2021.
//

#include <vector>
#include "engine.h"
#include <iostream>

void print_array(const engine::grid &array) {
    for (auto &t : array) {
        std::cout << t << ", ";
    }
    std::cout << std::endl;
}

void engine::forward_pass() {
    double F_0 = T0;
    double B_0 = 1;
    double C_0 = 0;
    alpha[0] = -C_0 / B_0;
    beta[0] = F_0 / B_0;
    const double A = r();
    const double B = -1 - 2 * r();
    const double C = r();
    for (int k = 1; k < N(); ++k) {
        double F = -T[k - 1];
        alpha[k] = -C / (A * alpha[k - 1] + B);
        beta[k] = (F - A * beta[k - 1]) / (A * alpha[k - 1] + B);
    }
}

void engine::backward_pass() {
    double B_N = sigma * (T.back() * T.back() * T.back()) * dx + 1;
    double A_N = -1;
    double F_N = 0;
    T[N()] = (F_N - A_N * beta[N() - 1]) / (A_N * alpha[N() - 1] + B_N);
    for (int k = N() - 1; k >= 0; --k) {
        T[k] = alpha[k] * T[k + 1] + beta[k];
    }
}

std::vector<double> engine::getT() const {
    std::vector<double> res;
    for (auto t : T) {
        res.push_back(t);
    }
    return res;
}

void engine::fill_with(double t) {
    for (int i = 1; i < N() + 1; ++i) {
        T[i] = t;
    }
}

void engine::enable_radiation() {
    sigma = sigma_sf;
}

engine::engine(double dx, double dt) : dx(dx), dt(dt) {}

void engine::init_physics(double left_temerature, double L, double thermal_conductivity, double heat_capacity, double density) {
    T0 = left_temerature;
    R = L;
    alpha = std::vector<double>(N() + 1);
    beta = std::vector<double>(N() + 1);
    T = std::vector<double>(N() + 1);
    kappa = thermal_conductivity;
    c = heat_capacity;
    rho = density;

}

size_t engine::N() const {
    return size_t(R / dx);
}

double engine::r() const {
    return dt / (dx * dx) * (rho * c / kappa);
}

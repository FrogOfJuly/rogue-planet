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
    for (int k = 1; k < N(); ++k) {
        double A = r() + spherical_amend(k) * r();
        double B = -1 - 2 * r() - spherical_amend(k) * 2 * r();
        double C = A;
        double F = -T[k - 1];
        alpha[k] = -C / (A * alpha[k - 1] + B);
        beta[k] = (F - A * beta[k - 1]) / (A * alpha[k - 1] + B);
    }
}

void engine::backward_pass() {
    double B_N = S * sigma * (T.back() * T.back() * T.back()) * dx + 1;
    double A_N = -1;
    double F_N = 0;
    T[N()] = (F_N - A_N * beta[N() - 1]) / (A_N * alpha[N() - 1] + B_N);
    for (int k = N() - 1; k >= 0; --k) {
        T[k] = alpha[k] * T[k + 1] + beta[k];
    }
}

engine::grid engine::getT() const {
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

engine::engine(double dx, double dt) : dt(dt), dx(dx) {
}

void engine::init_physics(double mantle_temerature,
                          double thermal_conductivity,
                          double specific_heat_capacity,
                          double density,
                          double upper_mantle,
                          double troposphere_height) {
    T0 = mantle_temerature;
    R_c = upper_mantle;
    R_t = troposphere_height;
    dx /= (R_t - R_c);
    std::cout << "point number: " << N() << std::endl;
    std::cout << "dx: " << dx << std::endl;
    alpha = std::vector<double>(N() + 1);
    beta = std::vector<double>(N() + 1);
    T = std::vector<double>(N() + 1);
    kappa = thermal_conductivity;
    c_p = specific_heat_capacity;
    rho = density;
    S = 4 * 3.14 * R_e * R_e;

}

size_t engine::N() const {
    return size_t(1.0 / dx);
}

double engine::r() const {
    const double k = (rho * c_p / kappa);
    const double alp = (R_t - R_c);
    return dt / (dx * dx) * k / (alp * alp);
}

double engine::x(int i) const {
    return dx * i;
}

double engine::spherical_amend(int k) const {
    const double alp = (R_t - R_c);
    const double bet = (R_e + R_c);
//    return 0;
    return dx / (2 * (x(k) + bet / alp));
}


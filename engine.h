//
// Created by Kirill Golubev on 28.04.2021.
//

#ifndef EARTHCOOLING_ENGINE_H
#define EARTHCOOLING_ENGINE_H

#include <array>

struct engine {
    double kappa = 1.0;
    double c = 1.0;
    double rho = 1.0;
    const double sigma_sf = 5.67 * pow(10, -8);
    double sigma = 0;
    double T0 = 300.0;
    double R = 1.0;

    double dx = 0.01;
    double dt = 0.1;

    using grid = std::vector<double>;

    grid alpha{};
    grid beta{};
    grid T{};

    engine(double dx, double dt);

    void init_physics(double T0, double L, double thermal_conductivity, double heat_capacity, double density);

    [[nodiscard]] double r() const;

    [[nodiscard]] size_t N() const;

    void fill_with(double t);

    void forward_pass();

    void backward_pass();

    void enable_radiation();

    [[nodiscard]] std::vector<double> getT() const;
};


#endif //EARTHCOOLING_ENGINE_H

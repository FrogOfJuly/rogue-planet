//
// Created by Kirill Golubev on 28.04.2021.
//

#ifndef EARTHCOOLING_ENGINE_H
#define EARTHCOOLING_ENGINE_H

#include <array>

struct engine {
    double kappa = 1.0;
    double c_p = 1.0;
    double rho = 1.0;
    const double sigma_sf = 5.67 * pow(10, -8);
    const double R_e = 6400 * pow(10, 3);
    double sigma = 0;
    double T0 = 1.0;
    double R_t = 1.0;
    double R_c = 0.0;
    double S = 1.0;

    double dx = 0.01;
    double dt = 0.1;

    using grid = std::vector<double>;

    grid alpha{};
    grid beta{};
    grid T{};

    engine(double dx, double dt);

    void init_physics(double mantle_temerature,
                      double thermal_conductivity,
                      double specific_heat_capacity,
                      double density,
                      double upper_mantle,
                      double troposphere_height);

    [[nodiscard]] double r() const;

    [[nodiscard]] size_t N() const;

    [[nodiscard]] double x(int i) const;

    void fill_with(double t);

    void forward_pass();

    void backward_pass();

    void enable_radiation();

    [[nodiscard]] double spherical_amend(int k) const;

    [[nodiscard]] grid getT() const;

    grid simulate_n_steps(int n){
        for(int i = 0; i < n; ++i){
            forward_pass();
            backward_pass();
        }
        return getT();
    }
};


#endif //EARTHCOOLING_ENGINE_H

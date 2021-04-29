//
// Created by Kirill Golubev on 28.04.2021.
//

#ifndef EARTHCOOLING_ENGINE_H
#define EARTHCOOLING_ENGINE_H

#include <array>
#include <cmath>
#include <vector>

struct engine {
    struct {
        const double sigma_sb = 5.67 * pow(10, -8);
        const double R_e = 6400 * pow(10, 3);
    } consts;
    struct {
        double sigma = 0;
        double T0 = 1.0;
        double Ts = 0.0;
        double R_t = 1.0;
        double R_c = 0.0;
        double Tl = 0.0;

        struct {
            double kappa = 1.0;
            double c = 1.0;
            double rho = 1.0;
        } core;

        struct {
            double kappa = 1.0;
            double c = 1.0;
            double rho = 1.0;
        } atm;
    } phys_params;
    struct {
//        double alpha;
//        double beta;
        double L;
        double l;

        double dx = 0.01;
        int N = 0;

        double dt = 0.1;

        double cur_time = 0;

        double J0 = 1.0;
        double r = 1.0;
    } eval_params;

    struct params {
        double x;
        double spherical_amend;
    };

    struct real_params {
        double x;
        double T;
    };

    using grid = std::vector<double>;

    grid alpha{};
    grid beta{};
    grid T{};

    engine(double dx, double dt);

    void init_physics(double mantle_temerature,
                      double surface_temperature,
                      double thermal_conductivity,
                      double specific_heat_capacity,
                      double density,
                      double upper_mantle,
                      double troposphere_height,
                      double interval_to_model);

    [[nodiscard]] double get_passed_time() const;

    void fill_with(double t);

    void set_border_cond(const grid &data);

    void forward_pass();

    void backward_pass();

    void enable_radiation(double alpha = 1);

    [[nodiscard]] grid getT() const;

    [[nodiscard]] grid getX() const;

    grid simulate_n_steps(int n);

    [[nodiscard]] int ticks_per_day() const;


};


#endif //EARTHCOOLING_ENGINE_H

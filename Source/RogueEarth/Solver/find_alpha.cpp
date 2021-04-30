#include "find_alpha.h"

#include <iostream>

bool check_alpha(engine eng, double alpha, double eps, size_t num_steps) {
    eng.enable_radiation(alpha);
    static const double wanted_temp = 300;
    auto old_t = eng.getT().back();
    eng.forward_pass();
    eng.backward_pass();
    auto curr_t = eng.getT().back();
    for (size_t i = 0; i < num_steps; ++i) {
        eng.forward_pass();
        eng.backward_pass();
        old_t = curr_t;
        curr_t = eng.getT().back();
    }
    return abs(curr_t - wanted_temp) < eps;
}

double find_alpha(engine eng, double step, double eps, size_t num_steps) {
    for (double alpha = 0; alpha <= 1; alpha += step) {
        if (check_alpha(eng, alpha, eps, num_steps)) {
            return alpha;
        }
    }
    return 0;
}
#include "find_alpha.h"

#include <iostream>

bool check_alpha(engine eng, double alpha, double eps) {
    eng.enable_radiation(alpha);
    static const double wanted_temp = 300;
    auto old_t = eng.getT().back();
    eng.forward_pass();
    eng.backward_pass();
    auto curr_t = eng.getT().back();
    while (abs(old_t - curr_t) > eps) {
        eng.forward_pass();
        eng.backward_pass();
        old_t = curr_t;
        curr_t = eng.getT().back();
    }
    std::cout << curr_t << std::endl;
    return abs(curr_t - wanted_temp) < eps;
}

double find_alpha(engine eng, double step, double eps) {
    for (double alpha = step; alpha <= 1; alpha += step) {
        if (check_alpha(eng, alpha, eps)) {
            return alpha;
        }
    }
    return 0;
}
#pragma once

namespace Newton{
    // Numerical derivative, h influcences precision
    double num_derivative(const double& x, double func(const double&), const double& h);

    // Newton method of finding root (double h is for num_deriviative)
    std::pair<__float128,int> newton_method(const std::pair<double,double>& interval, double func(const double&), const double& eps, const int& max_iter, const double& h);
}
#include "newton.cpp"
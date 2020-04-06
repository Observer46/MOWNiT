#pragma once

#include <stdexcept>
#include <quadmath.h>       // Because we need better precision than double for 1e-33
#include <vector>

namespace Bisection{
    // Returns sign of number
    int sign(const double& number);

    // Returns (root, iteration_count)
    std::pair<__float128,int> bisection(const std::pair<double,double>& interval, const double& eps, double func(const double&));

    // Counts all roots on the interval (returns with smaller precision)
    std::vector<double> all_roots(const std::pair<double,double>& interval, const double& eps, double func(const double&));
};

#include "bisection.cpp"

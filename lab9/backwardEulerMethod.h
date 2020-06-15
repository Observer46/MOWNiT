#pragma once

#include <fstream>
#include <iostream>

#include "odesolver.h"

class BackwardEulerMethod : public ODESolver{
public:
    BackwardEulerMethod(const std::vector<std::function<double(std::vector<double>, double)>>& odes, 
        const std::vector<double>& initial_conditions)
        : ODESolver(odes, initial_conditions) {};

    std::vector<std::vector<double>> solve(const double& h, const std::pair<double,double>& interval, 
        const unsigned& fixed_point_iter, const std::string& output_name);
};
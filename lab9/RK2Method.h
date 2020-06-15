#pragma once

#include <fstream>
#include <iostream>

#include "odesolver.h"

class RK2Method : public ODESolver{
public:
    RK2Method(const std::vector<std::function<double(std::vector<double>, double)>>& odes, 
        const std::vector<double>& initial_conditions)
        : ODESolver(odes, initial_conditions) {};

    std::vector<std::vector<double>> solve(const double& h, const std::pair<double,double>& interval, 
        const std::string& output_name);
};
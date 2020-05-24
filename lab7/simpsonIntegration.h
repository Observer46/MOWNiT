#pragma once

#include <cmath>
#include <fstream>
#include <iostream>

#include "quadrature.h"

class SimpsonIntegration : public Quadrature{
public:
    SimpsonIntegration(const double& eps, const unsigned& max_n) : Quadrature(eps, max_n) {};
    ~SimpsonIntegration() override = default;
    double integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx,
        const std::string& output_name) override;
};
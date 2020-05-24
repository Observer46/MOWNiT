#pragma once

#include <cmath>
#include <fstream>
#include <iostream>

#include "quadrature.h"

class RectangleIntegration : public Quadrature{
public:
    RectangleIntegration(const double& eps, const unsigned& max_n) : Quadrature(eps, max_n) {};
    ~RectangleIntegration() override = default;
    double integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx,
        const std::string& output_name) override;
};
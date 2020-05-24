#pragma once

#include <cmath>
#include <fstream>
#include <iostream>

#include "quadrature.h"

class TrapezoidIntegration : public Quadrature{
public:
    TrapezoidIntegration(const double& eps, const unsigned& max_n) : Quadrature(eps, max_n) {};
    ~TrapezoidIntegration() override = default;
    double integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx,
        const std::string& output_name) override;
};
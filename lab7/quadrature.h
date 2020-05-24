#pragma once

#include "integrationInterface.h"

class Quadrature : public IntegrationInterface
{
protected:
    double eps;
    unsigned max_n;
public:
    Quadrature(const double& eps, const unsigned& max_n) : eps{eps}, max_n{max_n} {};
    ~Quadrature() override = default;
}; 
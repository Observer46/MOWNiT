#pragma once

class Interpolation{ // Prawdopodobnie zbedna
public:
    virtual ~Interpolation() {};
    virtual double value(const double& x) const = 0;
};
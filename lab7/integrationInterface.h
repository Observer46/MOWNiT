#pragma once

#include <string>
#include <functional>
#include <stdexcept>

class IntegrationInterface
{
public:
    virtual ~IntegrationInterface() = default; 
    virtual double integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx, 
        const std::string& output_name) = 0;        // Pure virtual
};

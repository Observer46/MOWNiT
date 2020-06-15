#pragma once

#include <string>
#include <functional>
#include <vector>
#include <stdexcept>

class ODESolver
{
protected:
    std::vector<std::function<double(std::vector<double>, double)>> odes;
    std::vector<double> initial_conditions;
public:
    ODESolver(const std::vector<std::function<double(std::vector<double>, double)>>& odes, 
        const std::vector<double>& initial_conditions)
        :   odes{odes}, initial_conditions{initial_conditions}  
            {   
                if (odes.size() != initial_conditions.size())   
                    throw std::invalid_argument("Different numer of equation than initial conditions");  
            }
    ~ODESolver() = default;
};
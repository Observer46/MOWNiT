#pragma once

namespace Secant{           // Was suppoused to contain more functions, but turned out that "improved" version is much worse  
    // Function calculation root of the function using secant method
    std::pair<__float128,int> secant_method(const std::pair<double,double>& interval, double func(const double&), const double& eps, const int& max_iter);
}
#include "secant.cpp"
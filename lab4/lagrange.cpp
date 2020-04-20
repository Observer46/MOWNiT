#include "secant.h"

namespace Secant{
    // Function calculation root of the function using secant method
    std::pair<__float128,int> secant_method(const std::pair<double,double>& interval, double func(const double&), const double& eps, const int& max_iter){
        if (interval.second < interval.first)   
            throw std::invalid_argument("Interval is not defined corretly!");
        __float128 x_prev = interval.second;
        __float128 x_prev2 = interval.first;
        __float128 correction = (__float128) 1e-15;
        __float128 root;
        int iter;

        if ( func(x_prev2) == std::numeric_limits<double>::infinity() )     
            x_prev2 += correction;
        if ( func(x_prev) == std::numeric_limits<double>::infinity() )     
            x_prev -= correction;

        for(iter=0; iter < max_iter; iter++){
            root = (func(x_prev) * x_prev2 - func(x_prev2) * x_prev) / (func(x_prev) - func(x_prev2));
            if ( abs((double) (root - x_prev)) < eps  && iter > 1)  // We don't want to actidentally end because
                break;                                              // our first estimation of root was near x_prev
            if (root == std::numeric_limits<double>::infinity() ){
                root = x_prev;              // In case our iterations lead us to dividing by almost zero
                std::cout << "Reached maximum capabilities of the format!\n";
                break;
            }
            x_prev2 = x_prev;
            x_prev = root;
        }
        std::pair<__float128,int> result(root, iter);
        return result;
    }
}
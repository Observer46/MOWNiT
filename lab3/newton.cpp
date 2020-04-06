#include "newton.h"
namespace Newton{
    double num_derivative(const double& x, double func(const double&), const double& h){
        return (func(x + h) - func(x - h)) / (2.0 * h);
    }

    std::pair<__float128,int> newton_method(const std::pair<double,double>& interval, double func(const double&), const double& eps, const int& max_iter, const double& h){
        if (func(interval.first) * func(interval.second) > 0 )     
            throw std::invalid_argument("Function must have different signs on the ends of the interval!");

        __float128 root, prev_root;           // Initial values, from where we start
        double mid = (interval.first + interval.second) / 2.0;
        root = prev_root = (__float128) mid;//interval.second;
        int iter;
        for(iter=0; iter < max_iter; iter++){
            prev_root = root;
            root = prev_root - func(prev_root) / num_derivative(prev_root, func, h);
            if ( abs((double) (root - prev_root)) < eps )   // We reached expected precision
                break;
        }
        std::pair<__float128,int> result(root, iter);
        return result;
    }
}
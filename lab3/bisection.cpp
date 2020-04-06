#include "bisection.h"
namespace Bisection{
    // Returns sign of number
    int sign(const double& number){
        return number < 0 ? -1 : (number > 0 ? 1 : 0);
    }

    // Returns (root, iteration_count) 
    std::pair<__float128,int> bisection(const std::pair<double,double>& interval, const double& eps, double func(const double&)){
        if (interval.second < interval.first)   
            throw std::invalid_argument("Interval is not defined corretly!");

        __float128 a = (__float128) interval.first;         // We need better precision than double
        __float128  b = (__float128) interval.second;

        if (func(a) * func(b) > 0 )     
            throw std::invalid_argument("Function must have different signs on the ends of the interval!");

        int iteration_count = 0;
        while (b - a > eps){          // [a,b] is current operating interval
            __float128 mid = (__float128) (a + b) / 2.0;
            int a_sign = sign( func(a) );
            int mid_sign = sign( func(mid) );

            if (a_sign * mid_sign < 0)
                b = mid;
            else
                a = mid;
            iteration_count++;
        }
        __float128 root = (__float128) (a + b) / 2.0;     // As our root we take the middle of our final interval
        std::pair<__float128,int> result(root, iteration_count);
        return result;
    }

    // The idea is to perform bisection on all the small intervals of length of eps - by doing so we detect 
    // all of the roots on the interval provided, that they distance between roots is bigger than eps
    // linear complexity with respect to the length of interval (whereas bisection is logarithmic with respect to the length of interval)
    // Overall, pretty bad function, but finds all roots on the interval
    std::vector<double> all_roots(const std::pair<double,double>& interval, const double& eps, double func(const double&)){
        double shift = eps;
        double a = interval.first;
        double b = interval.first + shift;
        std::vector<double> roots;
        while (b < interval.second){
            int a_sign = sign( func(a) );
            int b_sign = sign( func(b) );
            if (a_sign * b_sign < 0){
                double root = (a + b) / 2.0;
                roots.push_back(root);
            }
            a = b;
            b += shift;
        }
        return roots;
    }
}
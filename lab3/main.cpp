#include <iostream>
#include <cmath>
#include <quadmath.h>
#include <vector>
#include <limits>

#include "bisection.h"
#include "newton.h"
#include "secant.h"

constexpr double PI = 3.141592653589;

double f1(const double& x){
    return cos(x) * cosh(x) - 1;
}

double f2(const double& x){
    return 1/x - tan(x);
}

double f3(const double& x){
    return pow(2, -x) + exp(x) + 2*cos(x) - 6;
}

double fl128_to_double(const __float128& res){
    double converted = (double) res;
    return converted;
}

int main(){
    double precision_tab[] = {1e-7, 1e-15, 1e-33};
    unsigned precision_count = 3;
    std::pair<double,double> interval1(3*PI/2, 2 * PI);
    std::pair<double,double> interval2(0, PI/ 2);
    std::pair<double,double> interval3(1, 3);
    
    // std::pair<double, double> inter4(-1.0, 12.0); // Extra
    // std::vector<double> roots = Bisection::all_roots(inter4, precision_tab[0], f1);
    // for(unsigned i=0; i < roots.size(); i++)
    //     std::cout << roots[i] << std::endl;

    std::cout << "\t Bisection:\n";
    for(unsigned i=0; i < precision_count; i++){
        std::pair<__float128, int> res_pair1 = Bisection::bisection(interval1, precision_tab[i], f1);
        std::cout << "f1:: Root: " << fl128_to_double(res_pair1.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair1.second << std::endl;
        std::pair<__float128, int> res_pair2 = Bisection::bisection(interval2, precision_tab[i], f2);
        std::cout << "f2:: Root: " << fl128_to_double(res_pair2.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair2.second << std::endl;
        std::pair<__float128, int> res_pair3 = Bisection::bisection(interval3, precision_tab[i], f3);
        std::cout << "f3:: Root: " << fl128_to_double(res_pair3.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair3.second << "\n\n";
    }

    std::cout << "\n\t Newton method:\n";
    int max_iter[] = {20, 50, 100};
    double h = 1e-5;

    for(unsigned i=0; i < precision_count; i++){
        std::pair<__float128, int> res_pair1 = Newton::newton_method(interval1, f1, precision_tab[i], max_iter[i], h);
        std::cout << "f1:: Root: " << fl128_to_double(res_pair1.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair1.second << std::endl;
        std::pair<__float128, int> res_pair2 = Newton::newton_method(interval2, f2, precision_tab[i], max_iter[i], h);
        std::cout << "f2:: Root: " << fl128_to_double(res_pair2.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair2.second << std::endl;
        std::pair<__float128, int> res_pair3 = Newton::newton_method(interval3, f3, precision_tab[i], max_iter[i], h);
        std::cout << "f3:: Root: " << fl128_to_double(res_pair3.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair3.second << "\n\n";
    }


    std::cout << "\n\t Secant method:\n";
    for(unsigned i=0; i < precision_count; i++){
        std::pair<__float128, int> res_pair1 = Secant::secant_method(interval1, f1, precision_tab[i], max_iter[i]);
        std::cout << "f1:: Root: " << fl128_to_double(res_pair1.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair1.second << std::endl;
        std::pair<__float128, int> res_pair2 = Secant::secant_method(interval2, f2, precision_tab[i], max_iter[i]);
        std::cout << "f2:: Root: " << fl128_to_double(res_pair2.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair2.second << std::endl;
        std::pair<__float128, int> res_pair3 = Secant::secant_method(interval3, f3, precision_tab[i], max_iter[i]);
        std::cout << "f3:: Root: " << fl128_to_double(res_pair3.first) << ", needed iteratons to get precision of " << precision_tab[i] << ": " << res_pair3.second << "\n\n";
    }

    return 0;
}
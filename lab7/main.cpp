#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <exception>
#include <algorithm>

#include "rectangleIntegration.h"
#include "trapezoidIntegration.h"
#include "simpsonIntegration.h"
#include "monteCarlo.h"

void printRes(const double& rect_res, const double& trap_res, const double& simp_res, const double& monte_res){
    std::cout << "Metoda prostokatow: " << rect_res << "\n";
    std::cout << "Metoda trapezow: " << trap_res << "\n";
    std::cout << "Metoda Simpsona: " << simp_res << "\n";
    std::cout << "Metoda Monte Carlo: " << monte_res << "\n\n";
}

int main(){
    std::pair<double,double> interval1(3.0, 6.0);       //f1 on interval (3,6), expected 59.9063
    auto f1 = [] (double x) {return x * x * (1 + sin(5*x));};

    std::pair<double,double> interval2(2.0, 13.0);       //f2 on interval (2,13), expected 9.80557
    auto f2 = [] (double x) {return sin(x) * sin(x) * log(x); };

    std::pair<double,double> interval3(-1.0, 1.0);       //f3 on interval (-1,1), expected 0.668648
    auto f3 = [] (double x) {return asin(x) * atan(x); };

    double eps = -1.0;
    unsigned n = 20;
    double rect_res, trap_res, simp_res, monte_res;
    std::cout << "\t Wyniki dla n = " << n << "\n\n\n";

    RectangleIntegration recInt(eps, n);
    TrapezoidIntegration trapInt(eps, n);
    SimpsonIntegration simpInt(eps, n);
    MonteCarlo monteCarlo(eps, n);
    
    rect_res = recInt.integrate(interval1, f1, "output/f1_Rec.txt");
    trap_res = trapInt.integrate(interval1, f1, "output/f1_Trap.txt");
    simp_res = simpInt.integrate(interval1, f1, "output/f1_Simp.txt");
    monte_res = monteCarlo.integrate(interval1, f1, "output/f1_Monte.txt");
    printRes(rect_res, trap_res, simp_res, monte_res);

    rect_res = recInt.integrate(interval2, f2, "output/f2_Rec.txt");
    trap_res = trapInt.integrate(interval2, f2, "output/f2_Trap.txt");
    simp_res = simpInt.integrate(interval2, f2, "output/f2_Simp.txt");
    monte_res = monteCarlo.integrate(interval2, f2, "output/f2_Monte.txt");
    printRes(rect_res, trap_res, simp_res, monte_res);

    rect_res = recInt.integrate(interval3, f3, "output/f3_Rec.txt");
    trap_res = trapInt.integrate(interval3, f3, "output/f3_Trap.txt");
    simp_res = simpInt.integrate(interval3, f3, "output/f3_Simp.txt");
    monte_res = monteCarlo.integrate(interval3, f3, "output/f3_Monte.txt");
    printRes(rect_res, trap_res, simp_res, monte_res);

    n = 10000;
    double est_PI = monteCarlo.calculate_PI(n, "output/PI_plot.txt", "output/PI_convergence.txt");
    std::cout << "Przyblizona wartosc PI: " << est_PI << " dla n = " << n << "\n";
    return 0;
}
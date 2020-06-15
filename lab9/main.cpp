#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <functional>
#include <exception>
#include <algorithm>

#include "eulerMethod.h"
#include "backwardEulerMethod.h"
#include "RK2Method.h"
#include "RK4Method.h"

void plot_exact_func(const std::function<double(double)>& exact_func, 
        const std::pair<double,double>& interval, const double& h, const std::string& filename){

    std::ofstream output(filename);
    unsigned step_count = (interval.second - interval.first) / h;
    double t = interval.first;
    for(unsigned i=0; i < step_count; i++){
        output << t << " " << exact_func(t) << "\n";
        t += h;
    }
}

int main(){
    // Lorenz's system of equations
    //////////////////////////////////////////////////////////
    constexpr double sigma = 10.0;
    constexpr double beta = 8.0/3.0;
    constexpr double rho = 28.0;
    constexpr double h = 1e-3;
    std::pair<double,double> lorenz_interval(0.0, 40.0);

    auto lorenz_dx = [] (std::vector<double> xyz, double t) { return sigma * ( xyz[1] - xyz[0] ); };
    auto lorenz_dy = [] (std::vector<double> xyz, double t) { return xyz[0] * ( rho - xyz[2] ) - xyz[1]; };
    auto lorenz_dz = [] (std::vector<double> xyz, double t) { return xyz[0] * xyz[1] - beta * xyz[2]; };
    std::vector<std::function<double(std::vector<double>, double)>> lorenz_odes = {lorenz_dx, lorenz_dy, lorenz_dz};
    std::vector<double> lorenz_init = {1.0, 1.0, 1.0};

    EulerMethod euler_res(lorenz_odes, lorenz_init);
    euler_res.solve(h, lorenz_interval, "lorenz_euler.txt");
    BackwardEulerMethod back_euler_res(lorenz_odes, lorenz_init);
    back_euler_res.solve(h, lorenz_interval, 3, "lorenz_backward_euler.txt");
    RK2Method rk2_res(lorenz_odes, lorenz_init);
    rk2_res.solve(h, lorenz_interval, "lorenz_rk2.txt");
    RK4Method rk4_res(lorenz_odes, lorenz_init);
    rk4_res.solve(h, lorenz_interval, "lorenz_rk4.txt");
    //////////////////////////////////////////////////////////

    //ex 4
    constexpr double m = 3.0, k = 4.0;
    auto ex4_dy = [] (std::vector<double> y , double x) { return k * m * sin(m*x) * ( k * cos(m*x) +  y[0]);};
    auto exact_solution = [] (double x) { return exp(-k * cos(m*x)) - k*cos(m*x) + 1; };
    double x0 = 0.0;        
    double xk = 10.0;
    std::pair<double,double> func_interval(x0, xk);
    double a = exact_solution(x0);
    double h1 = 1e-2, h2 = 1e-3, h3 = 1e-4;

    std::vector<double> ex4_init_cond = {a};
    std::vector<std::function<double(std::vector<double>, double)>> ex4_ode = {ex4_dy};
    
    plot_exact_func(exact_solution, func_interval, h1, "func_exact_1.txt");
    EulerMethod euler_func1(ex4_ode, ex4_init_cond);
    euler_func1.solve(h1, func_interval, "func_euler_1.txt");
    RK4Method rk4_func1(ex4_ode, ex4_init_cond);
    rk4_func1.solve(h1, func_interval, "func_rk4_1.txt");

    plot_exact_func(exact_solution, func_interval, h2, "func_exact_2.txt");
    EulerMethod euler_func2(ex4_ode, ex4_init_cond);
    euler_func2.solve(h2, func_interval, "func_euler_2.txt");
    RK4Method rk4_func2(ex4_ode, ex4_init_cond);
    rk4_func2.solve(h2, func_interval, "func_rk4_2.txt");

    plot_exact_func(exact_solution, func_interval, h3, "func_exact_3.txt");
    EulerMethod euler_func3(ex4_ode, ex4_init_cond);
    euler_func3.solve(h3, func_interval, "func_euler_3.txt");
    RK4Method rk4_func3(ex4_ode, ex4_init_cond);
    rk4_func3.solve(h3, func_interval, "func_rk4_3.txt");

    return 0;
}
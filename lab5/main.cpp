#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <exception>
#include <algorithm>

#include "aghMatrix.h"
#include "sole.h"

#include "polynomialApprox.h"
#include "trigonometricalApprox.h"

//constexpr double PI = 3.141592653589;

// Pierwsza funkcja przykladowa z parametrami: k = 2, m = 2
inline double f1(const double& x){
    return sin(2.0*x/PI) * exp(-2.0 * x / PI);
}

// Trzecia funkcja przykladowa z parametrem  m = 3
inline double f2(const double& x){
    return sin(3.0 * x) * exp(-3.0 * x / PI);
}

inline double w(const double& x){
    return 1.0;
}

// vector (x,y) - rownomiernie rozlozone punkty (zgodnie z zasada rozkladu punktow dla aproksymacji trygonometrycznej)
std::vector<std::pair<double,double>> sample_points(const unsigned& n, std::pair<double, double>& interval, double f(const double&)){
    if (n == 1)     throw std::invalid_argument("Approximation using one point will not work :(");
    std::vector<std::pair<double,double>> x_and_vals;
    double x = interval.first;
    double step = (interval.second - interval.first) / n ;
    for (unsigned i=0; i < n; i++){
        std::pair<double,double> x_fx(x,f(x));
        x_and_vals.push_back(x_fx);
        x += step;
    }
    return x_and_vals;
}

void create_plot_data(const int& point_amount, const std::pair<double,double>& interval, double f(const double&), const std::string& filename){
    double step = (interval.second - interval.first) / point_amount;
    double x = interval.first;
    std::ofstream dataForPlot;
    dataForPlot.open(filename);
    for (int i=0; i < point_amount; i++){
        double val = f(x);
        dataForPlot << x << " " << val << "\n";
        x += step;  
    }
}

void create_sampled_points_plot_data(std::vector<std::pair<double,double>> sampled_points, const std::string& filename){
    std::ofstream dataForPlot;
    dataForPlot.open(filename);
    for(const auto& x_fx : sampled_points)
        dataForPlot << x_fx.first << " " << x_fx.second << "\n";
}


int main(){
    std::pair<double, double> interval(-3.0,10.0);
    constexpr int draw_points_amount = 1e5;     // Do tworzenia wykresow

    create_plot_data(draw_points_amount, interval, f1, "f1_data.txt");
    create_plot_data(draw_points_amount, interval, f2, "f2_data.txt");
    
    std::vector<int> N_list = {5,10,20,40};
    for(const int& N : N_list){
        std::vector<std::pair<double,double>> f1_sample = sample_points(N, interval, f1);
        std::vector<std::pair<double,double>> f2_sample = sample_points(N, interval, f2);
        create_sampled_points_plot_data(f1_sample, "f1_sample_" + std::to_string(N) + ".txt");      // Dane z probki
        create_sampled_points_plot_data(f2_sample, "f2_sample_" + std::to_string(N) + ".txt");

        PolynomialApproximation f1_poly_approx_opt(f1_sample, w, std::min(N,6));    // m = min(N, 6), dobrze uwarunkowane numerycznie
        PolynomialApproximation f2_poly_approx_opt(f2_sample, w, std::min(N,6));    
        PolynomialApproximation f1_poly_approx(f1_sample, w, N);    // m = N, taki stopien wielomianu, ile jest punktow w probce (gorzej uwarunkowane numerycznie)
        PolynomialApproximation f2_poly_approx(f2_sample, w, N);  
        TrigonometricalApproximation f1_trig_approx(f1_sample, interval);
        TrigonometricalApproximation f2_trig_approx(f2_sample, interval);
        std::cout << "\tSample size: " << N << "\n";
        std::cout << "f1 polynomial (m = min(N,6)) approx sqr err: " << f1_poly_approx_opt.get_err() << "\n";
        std::cout << "f2 polynomial (m = min(N,6)) approx sqr err: " << f2_poly_approx_opt.get_err() << "\n";
        std::cout << "f1 polynomial (m = N) approx sqr err: " << f1_poly_approx.get_err() << "\n";
        std::cout << "f2 polynomial (m = N) approx sqr err: " << f2_poly_approx.get_err() << "\n";
        std::cout << "f1 trigonometrical approx sqr err: " << f1_trig_approx.get_err() << "\n";
        std::cout << "f2 trigonometrical approx sqr err: " << f2_trig_approx.get_err() << "\n\n";
        f1_poly_approx.create_plot_data(draw_points_amount, interval, "f1_poly_approx_data_" + std::to_string(N) + ".txt");
        f2_poly_approx.create_plot_data(draw_points_amount, interval, "f2_poly_approx_data_" + std::to_string(N) + ".txt");
        f1_poly_approx_opt.create_plot_data(draw_points_amount, interval, "f1_poly_opt_approx_data_" + std::to_string(N) + ".txt");
        f2_poly_approx_opt.create_plot_data(draw_points_amount, interval, "f2_poly_opt_approx_data_" + std::to_string(N) + ".txt");
        f1_trig_approx.create_plot_data(draw_points_amount, interval, "f1_trig_approx_data_" + std::to_string(N) + ".txt");
        f2_trig_approx.create_plot_data(draw_points_amount, interval, "f2_trig_approx_data_" + std::to_string(N) + ".txt");
    }

    return 0;
}
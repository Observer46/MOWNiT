#include <iostream>
#include <cmath>
//#include <quadmath.h>
#include <vector>
//#include <limits>
#include <fstream>
#include <string>

#include "interpolation.h"
#include "newton.h"
//#include "lagrange.h"
//#include "hermite.h"

constexpr double PI = 3.141592653589;

// Druga funkcja przykladowa z parametrami domyslnymi: k = 3, m = 4
double f(const double& x, const double& k = 3.0, const double& m = 4.0){
    return exp(k*cos(m*x));
}

void create_plot_data(const int& point_amount, const std::pair<double,double>& interval, std::string& filename){
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

std::pair<std::vector<double>, std::vector<double>> get_equally_distributed_nodes(const std::pair<double,double>& interval, const int& N){
    std::vector<double> nodes;
    std::vector<double> values;
    double step = (interval.second - interval.first) / (N - 1);
    double x = interval.first;
    for(int i=0; i < N; i++){
        nodes.push_back(x);
        values.push_back(f(x));
        x += step;
    }
    std::pair<std::vector<double>, std::vector<double>> nodes_and_values(nodes, values);
    return nodes_and_values;
}

std::pair<std::vector<double>, std::vector<double>> get_chebyshev_nodes(const std::pair<double,double>& interval, const int& N){
    std::vector<double> nodes;
    std::vector<double> values;
    double a = interval.first;
    double b = interval.second;
    for(int i=1; i <= N; i++){
        double arg = PI *( (2.0*i - 1.0)/(2.0*N));
        double xi = 0.5*(a + b) + 0.5*(b - a)*cos(arg);
        // std::cout << arg << " " << xi << "\n";
        nodes.push_back(xi);
        values.push_back(f(xi));
    }
    std::pair<std::vector<double>, std::vector<double>> nodes_and_values(nodes, values);
    return nodes_and_values;
}

template<class T>
double find_fit(T interpolation, std::pair<double,double> interval, int point_amount){
    double step = (interval.second - interval.first) / (point_amount - 1);
    double x = interval.first;
    double fit = 0.0;
    for(int i=0; i < point_amount; i++){
        fit += std::abs(f(x) - interpolation.value(x));
        x += step;
    }
    return fit;
}

template<class T>
std::pair<int,int> find_best_fit(std::pair<double,double> interval, const int& max_N, const int& draw_points_amount){
    int best_N_che = -1;
    int best_N_reg = -1;
    double best_fit_che = -1.0;
    double best_fit_reg = -1.0;
    std::string type = typeid(T).name();
    std::string chebyshev_file =  type + "_chebyshev_err.txt";
    std::string regular_nodes_file = type + "_reg_nodes_err.txt";

    std::ofstream cheby_fd;
    std::ofstream reg_fd;
    cheby_fd.open(chebyshev_file);
    reg_fd.open(regular_nodes_file);

    for(int N=2; N <= max_N; N++){
        std::pair<std::vector<double>, std::vector<double>> nodes_and_values = get_chebyshev_nodes(interval, N);
        std::vector<double> nodes = nodes_and_values.first;
        std::vector<double> node_vals = nodes_and_values.second;
        T interpolation_che(nodes, node_vals, N);
        double curr_fit = find_fit<T>(interpolation_che, interval, draw_points_amount);
        if (best_fit_che < 0){
            best_fit_che = curr_fit;
            best_N_che = N;
        }
        else if (best_fit_che > curr_fit){
            best_fit_che = curr_fit;
            best_N_che = N;
        }

        nodes_and_values = get_equally_distributed_nodes(interval, N);
        nodes = nodes_and_values.first;
        node_vals = nodes_and_values.second;
        T interpolation_reg(nodes, node_vals, N);
        curr_fit = find_fit<T>(interpolation_reg, interval, draw_points_amount);
        if (best_fit_reg < 0){
            best_fit_reg = curr_fit;
            best_N_reg = N;
        }
        else if (best_fit_reg > curr_fit){
            best_fit_reg = curr_fit;
            best_N_reg = N;
        }
       // std::cout << N << " " << curr_fit << "\n"; // Wypisywanie kolejnych fitow
    }
    std::cout << "Best N for interpolation by regular nodes: " << best_N_reg << std::endl;
    std::cout << "Best N for interpolation by chebyshev nodes: " << best_N_che << std::endl;
    std::pair<int,int> result(best_N_reg, best_N_che);
    return result;
}

template<class T>
void create_best_fit_data(const std::pair<double,double> & interval, const int& draw_points_amount){
    std::pair<int,int> best_fit = find_best_fit<T>(interval, 50, draw_points_amount);
    int best_N_reg = best_fit.first;
    int best_N_che = best_fit.second;
    std::string type = typeid(T).name();

    // Rownoodlegle wezly
    std::pair<std::vector<double>, std::vector<double>> nodes_and_values = get_equally_distributed_nodes(interval, best_N_reg);
    std::vector<double> nodes = nodes_and_values.first;
    std::vector<double> node_vals = nodes_and_values.second;
    T interpolation_reg(nodes, node_vals, best_N_reg);
    
    interpolation_reg.create_plot_data(draw_points_amount, interval, type + "_best_fit_reg.txt");

    // Wezly Czebyszewa
    nodes_and_values = get_chebyshev_nodes(interval, best_N_che);
    nodes = nodes_and_values.first;
    node_vals = nodes_and_values.second;
    T interpolation_che(nodes, node_vals, best_N_che);
    
    interpolation_che.create_plot_data(draw_points_amount, interval, type + "_best_fit_che.txt");
}

int main(){
    constexpr int draw_points_amount = 1e5;
    std::pair<double, double> interval(-2,2);
    std::string function_data_filename = "function_data.txt";
    create_plot_data(draw_points_amount, interval, function_data_filename);

    std::vector<int> N_list = { 2, 3, 8, 9, 10, 12, 15, 20};
    for (const int& N : N_list){
        std::pair<std::vector<double>, std::vector<double>> nodes_and_values = get_chebyshev_nodes(interval, N);
        std::vector<double> nodes = nodes_and_values.first;
        std::vector<double> node_vals = nodes_and_values.second;
        NewtonInterpolation newton_inter(nodes, node_vals, N);
        std::string outputname = "newton_res_" + std::to_string(N) + ".txt";
        newton_inter.create_plot_data(draw_points_amount, interval, outputname);
    }

    create_best_fit_data<NewtonInterpolation>(interval, draw_points_amount);

    return 0;
}
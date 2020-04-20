#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

#include "newton.h"
#include "lagrange.h"
#include "hermite.h"

constexpr double PI = 3.141592653589;

// Druga funkcja przykladowa z parametrami domyslnymi: k = 3, m = 4
double f(const double& x, const double& k = 3.0, const double& m = 4.0){
    return exp(k*cos(m*x));
}

double df(const double& x, const double& k = 3.0, const double& m = 4.0){
    return k*m * sin(m*x) * ( -exp(k*cos(m*x)) );
}

// double ddf(const double& x, const double& k = 3.0, const double& m = 4.0){
//     return k*m*m * exp(k*cos(m*x)) * ( k*sin(m*x)*sin(m*x) - cos(m*x) );
// }

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

std::pair<std::vector<double>, std::vector<double>> get_equally_distributed_nodes(const std::pair<double,double>& interval, const int& N, const bool& isHerimite){
    std::vector<double> nodes;
    std::vector<double> values;
    double step = (interval.second - interval.first) / (N - 1);
    double x = interval.first;
    for(int i=0; i < N; i++){
        nodes.push_back(x);
        values.push_back(f(x));
        if (isHerimite){
            nodes.push_back(x);
            values.push_back(df(x));
            // nodes.push_back(x);
            // values.push_back(ddf(x));
        }
        x += step;
    }
    std::pair<std::vector<double>, std::vector<double>> nodes_and_values(nodes, values);
    return nodes_and_values;
}

std::pair<std::vector<double>, std::vector<double>> get_chebyshev_nodes(const std::pair<double,double>& interval, const int& N, const bool& isHerimite){
    std::vector<double> nodes;
    std::vector<double> values;
    double a = interval.first;
    double b = interval.second;
    for(int i=1; i <= N; i++){
        double arg = PI *( (2.0*i - 1.0)/(2.0*N));
        double xi = 0.5*(a + b) + 0.5*(b - a)*cos(arg);
        nodes.push_back(xi);
        values.push_back(f(xi));
        if (isHerimite){
            nodes.push_back(xi);
            values.push_back(df(xi));
            // nodes.push_back(xi);
            // values.push_back(ddf(xi));
        }
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
    bool isHerimite = std::is_same<T,HermiteInterpolation>::value;

    std::ofstream cheby_fd;
    std::ofstream reg_fd;
    cheby_fd.open(chebyshev_file);
    reg_fd.open(regular_nodes_file);

    for(int N=2; N <= max_N; N++){
        std::pair<std::vector<double>, std::vector<double>> nodes_and_values = get_chebyshev_nodes(interval, N, isHerimite);
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
        cheby_fd << N << " " << curr_fit << "\n";

        nodes_and_values = get_equally_distributed_nodes(interval, N, isHerimite);
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
        reg_fd << N << " " << curr_fit << "\n";
        std::cout << typeid(T).name() << " " << N << "\n";
    } 
    std::cout << "Best N for " << typeid(T).name() << " by regular nodes: " << best_N_reg << std::endl;
    std::cout << "Best N for " << typeid(T).name() << " interpolation by chebyshev nodes: " << best_N_che << std::endl;
    std::pair<int,int> result(best_N_reg, best_N_che);
    return result;
}

template<class T>
void create_best_fit_data(const std::pair<double,double> & interval, const int& draw_points_amount){
    std::pair<int,int> best_fit = find_best_fit<T>(interval, 40, draw_points_amount);
    int best_N_reg = best_fit.first;
    int best_N_che = best_fit.second;
    std::string type = typeid(T).name();
    bool isHerimite = std::is_same<T,HermiteInterpolation>::value;

    // Rownoodlegle wezly
    std::pair<std::vector<double>, std::vector<double>> nodes_and_values = get_equally_distributed_nodes(interval, best_N_reg, isHerimite);
    std::vector<double> nodes = nodes_and_values.first;
    std::vector<double> node_vals = nodes_and_values.second;
    T interpolation_reg(nodes, node_vals, best_N_reg);
    
    interpolation_reg.create_plot_data(draw_points_amount, interval, type + "_best_fit_reg.txt");

    // Wezly Czebyszewa
    nodes_and_values = get_chebyshev_nodes(interval, best_N_che, isHerimite);
    nodes = nodes_and_values.first;
    node_vals = nodes_and_values.second;
    T interpolation_che(nodes, node_vals, best_N_che);
    
    interpolation_che.create_plot_data(draw_points_amount, interval, type + "_best_fit_che.txt");
}
// Efekt Runge'go 
// Newton - N = 9
// Lagrange - N = 9
// Hermite - N = 21...?
// Tworzy pliki z wynikami dla ktorych widac efekt
void runge_effect(const std::pair<double,double>& interval, const int& draw_points_amount){
    const int N = 9;
    std::pair<std::vector<double>, std::vector<double>> nodes_and_values = get_equally_distributed_nodes(interval, N, false);
    std::vector<double> nodes = nodes_and_values.first;
    std::vector<double> node_vals = nodes_and_values.second;
    NewtonInterpolation newton_inter_reg(nodes, node_vals, N);
    LagrangeInterpolation lagrange_inter_reg(nodes, node_vals, N);
    newton_inter_reg.create_plot_data(draw_points_amount, interval, "newton_runge.txt");
    lagrange_inter_reg.create_plot_data(draw_points_amount, interval, "lagrange_runge.txt");

    const int N2 = 21;
    nodes_and_values = get_equally_distributed_nodes(interval, N2, true);
    nodes = nodes_and_values.first;
    node_vals = nodes_and_values.second;
    HermiteInterpolation hermite_inter_reg(nodes, node_vals, N2);
    hermite_inter_reg.create_plot_data(draw_points_amount,interval, "hermite_runge?.txt");
}

int main(){
    constexpr int draw_points_amount = 1e5;
    std::pair<double, double> interval(-3,3);
    std::string function_data_filename = "function_data.txt";
    create_plot_data(draw_points_amount, interval, function_data_filename);

    std::vector<int> N_list = {19,20,21,22,23,24,25};// { 2, 5, 8, 10, 15, 20};
    for (const int& N : N_list){
        bool isHerimite = false;
        std::pair<std::vector<double>, std::vector<double>> nodes_and_values = get_equally_distributed_nodes(interval, N, isHerimite);
        std::vector<double> nodes = nodes_and_values.first;
        std::vector<double> node_vals = nodes_and_values.second;
        NewtonInterpolation newton_inter_reg(nodes, node_vals, N);
        LagrangeInterpolation lagrange_inter_reg(nodes, node_vals, N);
        isHerimite = true; ////////////////////////////////////////////
        nodes_and_values = get_chebyshev_nodes(interval, N, isHerimite);
        nodes = nodes_and_values.first;
        node_vals = nodes_and_values.second;
        HermiteInterpolation hermite_inter_reg(nodes, node_vals, N);

        std::string outputname = "newton_reg_res_" + std::to_string(N) + ".txt";
        newton_inter_reg.create_plot_data(draw_points_amount, interval, outputname);
        outputname = "lagrange_reg_res_" + std::to_string(N) + ".txt";
        lagrange_inter_reg.create_plot_data(draw_points_amount, interval, outputname);
        outputname = "hermite_reg_res_" + std::to_string(N) + ".txt";
        hermite_inter_reg.create_plot_data(draw_points_amount, interval, outputname);

        isHerimite = false;
        nodes_and_values = get_chebyshev_nodes(interval, N, isHerimite);
        nodes = nodes_and_values.first;
        node_vals = nodes_and_values.second;
        NewtonInterpolation newton_inter_che(nodes, node_vals, N);
        LagrangeInterpolation lagrange_inter_che(nodes, node_vals, N);
        isHerimite = true; ////////////////////////////////////////////
        nodes_and_values = get_chebyshev_nodes(interval, N, isHerimite);
        nodes = nodes_and_values.first;
        node_vals = nodes_and_values.second;
        HermiteInterpolation hermite_inter_che(nodes, node_vals, N);

        outputname = "newton_che_res_" + std::to_string(N) + ".txt";
        newton_inter_che.create_plot_data(draw_points_amount, interval, outputname);
        outputname = "lagrange_che_res_" + std::to_string(N) + ".txt";
        lagrange_inter_che.create_plot_data(draw_points_amount, interval, outputname);
        outputname = "hermite_che_res_" + std::to_string(N) + ".txt";
        hermite_inter_che.create_plot_data(draw_points_amount, interval, outputname);
    }

    create_best_fit_data<NewtonInterpolation>(interval, draw_points_amount);
    create_best_fit_data<LagrangeInterpolation>(interval, draw_points_amount);
    create_best_fit_data<HermiteInterpolation>(interval, draw_points_amount);

    return 0;
}
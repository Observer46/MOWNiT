#include "newton.h"

NewtonInterpolation::NewtonInterpolation(const std::vector<double>& nodes, const std::vector<double>& node_vals, const unsigned& N) : N{N} {
    std::vector<double> result;
    std::vector<double> divided_diffs;
    for (unsigned i=0; i < N; i++)
        divided_diffs.push_back(node_vals[i]);
    result.push_back(divided_diffs[0]);

    for (unsigned i=1; i < N; i++){
        for(unsigned j=N-1; j >= i; j--){
            double numerator = divided_diffs[j] - divided_diffs[j-1];
            double denominator = nodes[j] - nodes[j-i];
            divided_diffs[j] = numerator / denominator;
        }
        result.push_back(divided_diffs[i]);
    }
    this -> a_coefficients = result;
    this -> nodes = nodes;
}

double NewtonInterpolation::value(const double& x) const{
    double a0 = a_coefficients[0];
    double value = a0;
    for (unsigned i=1; i < N; i++){
        double ai = a_coefficients[i];
        double mul=1;
        for (unsigned j=0; j < i; j++)
            mul *= x - nodes[j];
        value += ai * mul;
    }
    return value;
}

void NewtonInterpolation::create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const{
    double step = (interval.second - interval.first) / point_amount;
    double x = interval.first;
    std::ofstream dataForPlot;
    dataForPlot.open(filename);
    for (int i=0; i < point_amount; i++){
        double val = this -> value(x);
        dataForPlot << x << " " << val << "\n";
        x += step;
        // std::cout << x << " " << val << "\n";
    }
}
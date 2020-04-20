#include "lagrange.h"

double LagrangeInterpolation::value(const double& x) const{
    double value = 0.0;
    for (unsigned i=0; i < N; i++){
        double yi = node_vals[i];
        double mul=1;
        for (unsigned j=0; j < N; j++)
            mul *= ( (i==j) ? 1 : (x - nodes[j]) / (nodes[i] - nodes[j]) );
        value += yi * mul;
    }
    return value;
}

void LagrangeInterpolation::create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const{
    double step = (interval.second - interval.first) / point_amount;
    double x = interval.first;
    std::ofstream dataForPlot;
    dataForPlot.open(filename);
    for (int i=0; i < point_amount; i++){
        double val = this -> value(x);
        dataForPlot << x << " " << val << "\n";
        x += step;
    }
}


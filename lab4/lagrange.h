#pragma once

class LagrangeInterpolation {
    std::vector<double> nodes;
    std::vector<double> node_vals;
    const unsigned N;
public:
    LagrangeInterpolation(const std::vector<double>& nodes, const std::vector<double>& node_vals, const unsigned& N) : nodes{nodes}, node_vals{node_vals}, N{N} {};
    ~LagrangeInterpolation() = default;
    double value(const double& x) const;
    void create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const;
};
#include "lagrange.cpp"
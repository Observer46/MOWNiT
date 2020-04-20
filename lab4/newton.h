#pragma once

class NewtonInterpolation : public Interpolation{
    std::vector<double> a_coefficients;
    std::vector<double> nodes;
    const unsigned N;
public:
    NewtonInterpolation(const std::vector<double>& nodes, const std::vector<double>& node_vals, const unsigned& N);
    ~NewtonInterpolation() = default;
    double value(const double& x) const override;
    void create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const;
};
#include "newton.cpp"
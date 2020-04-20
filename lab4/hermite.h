#pragma once
inline long int factor(int n);

class HermiteInterpolation {
    std::vector<double> a_coefficients;
    std::vector<double> nodes;
    const unsigned N;
    unsigned derivative_level;
public:
    HermiteInterpolation(const std::vector<double>& nodes, const std::vector<double>& node_vals, const unsigned& N);
    ~HermiteInterpolation() = default;
    double value(const double& x) const;
    void create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const;
};
#include "hermite.cpp"
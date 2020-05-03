#pragma once

constexpr double PI = 3.141592653589;

class TrigonometricalApproximation {
    std::vector<double> a;
    std::vector<double> b;
    long unsigned n;
    long unsigned m;         // m - stopien wielomianu trygonometrycznego 
    double estimated_err;
    const std::pair<double,double> interval;
public:
    TrigonometricalApproximation(const std::vector<std::pair<double,double>>& sample, const std::pair<double,double>& interval);
    double value(const double& x) const;
    void create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const;
    void create_sampled_points_plot_data(double f(const double&), const std::string& filename) const;
    double get_err()  const   {return this->estimated_err;}

    // Transformuje punkt z przedzialu [a,b] na przedzial [0, 2*pi] wedlug formuly:
    // vi := 2*pi * (x-a)/(b-a)
    double trans_to_trig(const double& x) const  { return 2*PI * (x - interval.first) / (interval.second - interval. first); }
};
#include "trigonometricalApprox.cpp"
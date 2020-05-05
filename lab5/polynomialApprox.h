#pragma once


class PolynomialApproximation {
    AGHMatrix<double> G_mat;
    AGHMatrix<double> A_mat;
    AGHMatrix<double> B_mat;
    unsigned m;
    double estimated_err;
public:                                                     // Przyjmuje probke,funkcje wagi oraz stopiem wielomianu
    PolynomialApproximation(const std::vector<std::pair<double,double>>& sample_points, double w(const double&x), const unsigned& m);
    double value(const double& x) const;
    void create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const;
    double get_err()  const   {return this->estimated_err;}
};
#include "polynomialApprox.cpp"
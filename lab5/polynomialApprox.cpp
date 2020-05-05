#include "polynomialApprox.h"

// Aproksymuje wielomianem stopnia m-1
PolynomialApproximation::PolynomialApproximation(const std::vector<std::pair<double,double>>& sample_points, double w(const double&x), const unsigned& m) : G_mat(m, m, 0.0), A_mat(m, 1, 0.0), B_mat(m, 1, 0.0), m{m} {
    unsigned n = sample_points.size();
    if (m > n)  throw std::invalid_argument("If m > n approximation might not be calculated!");
    
    for(unsigned row=0; row < this->G_mat.get_rows(); row++){
        for(unsigned col=0; col < this->G_mat.get_cols(); col++){
            if (row < 1 || col + 1 >= this->G_mat.get_cols() ){
                double g_sum = 0.0;
                for(unsigned i=0; i < n; i++){
                    double xi = sample_points[i].first;
                    g_sum += w(xi) * pow(xi, row + col);
                }
                this->G_mat(row, col) = g_sum;
            }
            else
                this->G_mat(row,col) = this->G_mat(row-1, col+1);
        }
        double b_sum = 0.0;
        for(unsigned i=0; i < n; i++){
            double xi = sample_points[i].first;
            double fxi = sample_points[i].second;
            b_sum += w(xi) * fxi * pow(xi, row);
        }
        this->B_mat(row, 0) = b_sum;
    }
    
    SOLE<double> sys_of_equations(this->G_mat, this->B_mat);
    this->A_mat = sys_of_equations.solve_gauss();
    
    double err_sum = 0.0;
    for(unsigned i=0; i < n; i++){
        double xi = sample_points[i].first;
        double fxi = sample_points[i].second;
        err_sum += w(xi) * pow(this->value(xi) - fxi, 2);
    }
    this -> estimated_err = err_sum;
}

double PolynomialApproximation::value(const double& x) const{
    double sum = 0.0;
    for(unsigned j=0; j < this->m; j++){
        double aj = this->A_mat(j, 0);
        sum +=  aj * pow(x, j);
    }
    return sum;
}

void PolynomialApproximation::create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const{
    double step = (interval.second - interval.first) / point_amount;
    double x = interval.first;
    std::ofstream dataForPlot;
    dataForPlot.open(filename);
    for (int i=0; i < point_amount; i++){
        double val = this->value(x);
        dataForPlot << x << " " << val << "\n";
        x += step;  
    }
}

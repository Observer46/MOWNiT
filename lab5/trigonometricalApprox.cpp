#include "trigonometricalApprox.h"

TrigonometricalApproximation::TrigonometricalApproximation(const std::vector<std::pair<double,double>>& sample, const std::pair<double,double>& interval) : a{}, b{}, n{sample.size()}, m{(n-1)/2}, estimated_err{}, interval{interval} {
    // m - stopien wielomianu trygonometrycznego 
    double a0 = 0.0;
    for(unsigned i=0; i<n; i++){
        double fvi = sample[i].second;
        a0 += fvi;              // cos(..*0*..) zawsze = 1
    }
    a0 /= n;                    // Juz podzielone przez 2
    this->a.push_back(a0);      // Zerowa iteracja
    this->b.push_back(0.0);
    std::cout << "m = " << this->m << "\n";
     
    for(unsigned k=1; k < m; k++){
        double a_k = 0.0;
        double b_k = 0.0;
        for(unsigned i=0; i < n; i++){
            double vi =  2.0 * PI * i / n;
            double fvi = sample[i].second;      // Podmieniamy f(vi) na f(x) - kompresujemy funkcje z przedzialu [a,b] ma przedzial [0,2pi]
            double arg = (double) k*vi;
            a_k += fvi * (double) cos(arg);
            b_k += fvi * (double) sin(arg);
        }
        a_k *=  2.0 / n;
        b_k *=  2.0 / n;
        this->a.push_back(a_k);
        this->b.push_back(b_k);
    }

    double err_sum = 0.0;
    for(unsigned i=0; i < n; i++){
        double xi = sample[i].first;
        double fxi = sample[i].second;
        err_sum += pow(this->value(xi) - fxi, 2);
    }
    this -> estimated_err = err_sum;
}

double TrigonometricalApproximation::value(const double& x) const{
    double trans_x = this->trans_to_trig(x);
    double sum = 0.0;
    for(unsigned k=0; k < this->m; k++){     // a[0] := a0/2
        double arg = (double) k * trans_x;
        sum +=  this->a[k] * cos(arg) + this->b[k] * sin(arg);
    }
    return sum;
}

void TrigonometricalApproximation::create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const{
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

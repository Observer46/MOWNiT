#include "hermite.h"

inline long int factor(int n){
    long int res = 1;
    for(int i=1; i <= n; i++)   res *= i;
    return res;
}

HermiteInterpolation::HermiteInterpolation(const std::vector<double>& nodes, const std::vector<double>& node_vals, const unsigned& N) : nodes{nodes}, N{N}   {
    this -> derivative_level = (nodes.size() / N) - 1;      // Max. stopien pochodnych
    unsigned size = nodes.size();
    std::vector<double> result;
    std::vector<double> divided_diffs;
    unsigned i_skip = derivative_level + 1;  // Do iteracji po przeplatanym vectorze nodes

    for (unsigned i=0; i < size; i+=i_skip)
        for (unsigned j=0; j < i_skip; j++)
            divided_diffs.push_back(node_vals[i]);
    result.push_back(divided_diffs[0]);

    for (unsigned i=1; i < size; i++){
        bool useDerivate = false;
        if (i < i_skip)     useDerivate = true;    // Niepotrzebne, dodane bardziej dla przezoczystosci
        int counter = i_skip - (int) i - 1;
        for(unsigned j=size-1; j >= i; j--){
            if(useDerivate && counter >= 0)
                divided_diffs[j] = node_vals[j - counter] / factor(i);
            else{
                double numerator = divided_diffs[j] - divided_diffs[j-1];
                double denominator = nodes[j] - nodes[j-i];
                divided_diffs[j] = numerator / denominator;
            }
            counter--;
            if (j % i_skip == 0)     
                counter = i_skip - (int) i - 1;
        }
        result.push_back(divided_diffs[i]);
    }
    this -> a_coefficients = result;
    this -> nodes = nodes;
}

double HermiteInterpolation::value(const double& x) const{
    double a0 = a_coefficients[0];
    double value = a0;
    unsigned size = this->nodes.size();
    for (unsigned i=1; i < size; i++){
        double ai = a_coefficients[i];
        double mul=1;
        for (unsigned j=0; j < i; j++)
            mul *= x - nodes[j];
        value += ai * mul;
    }
    return value;
}

void HermiteInterpolation::create_plot_data(const int& point_amount, const std::pair<double,double>& interval, const std::string& filename) const{
    double step = (interval.second - interval.first) / point_amount;
    double x = interval.first;
    std::ofstream dataForPlot;
    dataForPlot.open(filename);
    for (int i=0; i < point_amount; i++){
        double val = this -> value(x);
        dataForPlot << x << " " << val << "\n";
        x += step;;
    }
}
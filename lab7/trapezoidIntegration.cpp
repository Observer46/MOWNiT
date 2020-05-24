#include "trapezoidIntegration.h"

double TrapezoidIntegration::integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx, const std::string& output_name){
    if (interval.first >= interval.second)
        throw std::invalid_argument("Interval is not defined correctly!");

    double result = -1.0, prev_res = -1.0;
    unsigned n;
    std::ofstream output_file;
    output_file.open(output_name);
    for(n=1; n <= this->max_n; n++){
        prev_res = result;
        result = ( fx(interval.first) + fx(interval.second) ) / 2;
        double dx = (interval.second - interval.first) / n;
        for(unsigned i=1; i <= n-1; i++){     // x1,x2,...,xn-1
            double xi = (double) (interval.first + i * dx);
            double fi = fx(xi);
            result += fi;
        }
        result *= dx;
        output_file << n << " " << result << "\n";
        if (prev_res > 0 && std::abs(result - prev_res)  <= this->eps)
            break;
    }
    return result;
}
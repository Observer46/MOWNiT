#include "simpsonIntegration.h"

double SimpsonIntegration::integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx, const std::string& output_name){
    if (interval.first >= interval.second)
        throw std::invalid_argument("Interval is not defined correctly!");

    double result = -1.0, prev_res = -1.0;
    unsigned n;
    std::ofstream output_file;
    output_file.open(output_name);
    for(n=1; n <= this->max_n; n++){
        prev_res = result;
        result = fx(interval.first) + fx(interval.second);
        double dx = (interval.second - interval.first) / n;
        double si = 0.0;
        double sti = 0.0;       
        for(unsigned i=1; i <= n-1; i++){     // x1,x2,...,xn-1; t2,t3,...,tn-1
            double xi = interval.first + i * dx;
            double ti = xi - dx / 2;
            si += fx(xi);
            sti += fx(ti);
        }
        sti += fx(interval.second - dx / 2);    //f(tn)
        result += 2 * si + 4 * sti;
        result *= dx / 6;
        output_file << n << " " << result << "\n";
        if (prev_res > 0 && std::abs(result - prev_res)  <= this->eps)
            break;
    }
    return result;
}
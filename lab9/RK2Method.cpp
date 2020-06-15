#include "RK2Method.h"

std::vector<std::vector<double>> RK2Method::solve(const double& h, const std::pair<double,double>& interval, const std::string& output_name){
    if (interval.second < interval.first)
        throw std::invalid_argument("Interval is not defined correctly!");

    unsigned step_count = (interval.second - interval.first) / h;
    std::ofstream output(output_name);
    double t = interval.first;
    std::vector<std::vector<double>> results;
    std::vector<double> arg_vals = this->initial_conditions; 
    results.resize(this->odes.size());
    arg_vals.resize(this->odes.size());
    for(unsigned i=0; i < this->initial_conditions.size(); i++)
        results[i].push_back(this->initial_conditions[i]);

    for(unsigned i=0; i < step_count; i++){
        std::vector<double> new_arg_vals, tmp_vector;
        new_arg_vals.resize(arg_vals.size());
        tmp_vector = arg_vals;
        output << t + h;
        for(unsigned j=0; j < this->odes.size(); j++){  // k1
            double k1 = this->odes[j](arg_vals, t);
            tmp_vector[j] += k1 * h / 2.0;              //yn + h/2 * f(tn, yn)
        }
        for(unsigned j=0; j < this->odes.size(); j++){
            double k2 = this->odes[j](tmp_vector, t + h / 2.0);
            double new_val = arg_vals[j] + h * k2;
            results[j].push_back(new_val);
            new_arg_vals[j] = new_val;
            output << " " << new_val;
        }
        arg_vals = new_arg_vals;
        output << "\n";
        t += h;
    }
    output.close();
    return results;
}
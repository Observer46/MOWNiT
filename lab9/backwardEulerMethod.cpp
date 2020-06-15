#include "backwardEulerMethod.h"

std::vector<std::vector<double>> BackwardEulerMethod::solve(const double& h, const std::pair<double,double>& interval, const unsigned& fixed_point_iter, const std::string& output_name){
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
        std::vector<double> new_arg_vals, tmp_vals;
        new_arg_vals.resize(arg_vals.size());
        tmp_vals = arg_vals;
        output << t + h;
        for(unsigned k=0; k < fixed_point_iter; k++){
            for(unsigned j=0; j < this->odes.size(); j++){
                double f_val = this->odes[j](tmp_vals, t);
                new_arg_vals[j] = arg_vals[j] + h * f_val;
            }
            tmp_vals = new_arg_vals;
        }
        for(unsigned j=0; j < this->odes.size(); j++){
            double new_val = new_arg_vals[j];
            results[j].push_back(new_val);
            output << " " << new_val;
        }
        arg_vals = new_arg_vals;
        output << "\n";
        t += h;
    }
    output.close();
    return results;
}
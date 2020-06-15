#include "RK4Method.h"

std::vector<std::vector<double>> RK4Method::solve(const double& h, const std::pair<double,double>& interval, const std::string& output_name){
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

    std::vector<double> tmp_vector, k1, k2, k3, k4;
    tmp_vector.resize(arg_vals.size());
    k1.resize(arg_vals.size());
    k2.resize(arg_vals.size());
    k3.resize(arg_vals.size());
    k4.resize(arg_vals.size());
    
    for(unsigned i=0; i < step_count; i++){
        std::vector<double> new_arg_vals;
        output << t + h;
        for(unsigned j=0; j < this->odes.size(); j++){
            k1[j] = (this->odes[j](arg_vals, t));    
            tmp_vector[j] = (arg_vals[j] + k1[j] * h / 2.0);    //arg for k2
        }
        new_arg_vals = tmp_vector;
        for(unsigned j=0; j < this->odes.size(); j++){
            k2[j] = (this->odes[j](new_arg_vals, t + h / 2.0));
            tmp_vector[j] = arg_vals[j] + k2[j] * h / 2.0;      //arg for k3
        }
        new_arg_vals = tmp_vector;
        for(unsigned j=0; j < this->odes.size(); j++){
            k3[j] = (this->odes[j](new_arg_vals, t + h / 2.0));
            tmp_vector[j] = arg_vals[j] + k3[j] * h;            //arg for k4
        }
        new_arg_vals = tmp_vector;
        for(unsigned j=0; j < this->odes.size(); j++){
            k4[j] = (this->odes[j](new_arg_vals, t + h));
            double new_val = arg_vals[j] + h * (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]) / 6.0;
            tmp_vector[j] = new_val;
            output << " " << new_val;
            results[j].push_back(new_val);
        }
        arg_vals = tmp_vector;
        output << "\n";
        t += h;
    }
    output.close();
    return results;
}
#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

#include "integrationInterface.h"

double euclidean_distance(const std::pair<double,double>& p1, const std::pair<double,double>& p2);

class MonteCarlo : public IntegrationInterface{
private:
    double eps;
    unsigned max_n;
    std::default_random_engine gen;
public:
    // eps is some sort of 'variance' of the result (when change is smaller than eps we stop)
    MonteCarlo(const double& eps, const unsigned& max_n) : eps{eps}, max_n{max_n}, 
        gen(time(NULL)) {};
    ~MonteCarlo() override = default;
    double integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx, 
        const std::string& output_name) override;
        
    double calculate_PI( const unsigned& n, const std::string& output_name, 
        const std::string& convergance_file);
};
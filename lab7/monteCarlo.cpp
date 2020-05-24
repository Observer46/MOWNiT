#include "monteCarlo.h"

double euclidean_distance(const std::pair<double,double>& p1, const std::pair<double,double>& p2){
    double dx = p2.first - p1.first;
    double dy = p2.second - p1.second;
    return std::sqrt(dx * dx + dy * dy);
}

double MonteCarlo::integrate(const std::pair<double,double>& interval, const std::function<double(double)>& fx, const std::string& output_name){
    if (interval.first >= interval.second)
        throw std::invalid_argument("Interval is not defined correctly!");
    double result = 0.0, prev_res = -1.0;  // res - current sum of fx(xi), prev_res - sum without new sample
    unsigned n;
    std::uniform_real_distribution<double> dist(interval.first, interval.second);
    std::ofstream output_file;
    output_file.open(output_name);
    double interval_length = interval.second - interval.first;

    for(n=1; n <= this->max_n; n++){
        double xi = dist(this->gen);
        result += fx(xi);
        double curr_res = result * interval_length / n;
        prev_res *= (n > 1) ? interval_length / (n-1) : 1;
        output_file << n << " " << curr_res << "\n";
        if (prev_res > 0 && std::abs(curr_res - prev_res )  <= this->eps)
            break;
        
        prev_res = result;
    }
    result *= interval_length / n;
    return result;
}

double MonteCarlo::calculate_PI( const unsigned& n, const std::string& output_name, const std::string& convergance_file){
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    std::ofstream output_file, convergance_handle;
    convergance_handle.open(convergance_file);
    output_file.open(output_name);
    
    double radius = 1.0;            // Key part for that estimation
    double res;
    unsigned inside_counter = 0;
    std::pair<double,double> circle_center(0.0, 0.0);       // Circle centered at (0,0) with r = 1
    
    for(unsigned i=0; i < n; i++){
        double x = dist(gen);
        double y = dist(gen);
        std::pair<double,double> point(x,y);
        bool inside_circle = euclidean_distance(circle_center, point) <= radius;
        if (inside_circle)
            inside_counter++;
        output_file << x << " " << y << " " << inside_circle << "\n";
        res = 4 * radius * radius * inside_counter / i;
        convergance_handle << i << " " << res << "\n";
    }
    return res;
}
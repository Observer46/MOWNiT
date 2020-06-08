#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>
#include <exception>
#include <algorithm>
#include <chrono>
#include <fftw3.h>

#include "DFT.h"
#include "FFT.h"

std::vector<std::pair<double, int>> parse_weather_data(const std::string& input, const std::string& output){
    std::ifstream input_file(input);
    std::ofstream output_file;
    output_file.open(output);
    std::vector<std::pair<double, int>> humidity_data;      // pairs (day_and_hour, humidity_value)
    int day = 7;            // 7th of May

    for(std::string line; std::getline(input_file, line); ){
        std::stringstream ss(line);
        int hour, humidity, temp_decoy;
        std::string am_or_pm, temp_unit_decoy;
        ss >> hour >> am_or_pm;
        ss >> temp_decoy >> temp_unit_decoy >> temp_decoy >> temp_unit_decoy;       // skip temperatures
        ss >> humidity;     // Parse % humiditys
        if (hour == 12)         hour = 0;
        if (am_or_pm == "PM")   hour += 12;
        std::pair<double, int> measurement(day + (double) hour / 24.0, humidity);       // day + hour as a double
        output_file << measurement.first << " " << measurement.second << "\n";
        humidity_data.push_back(measurement);
       
        if (hour == 23)     day++;
    }

    input_file.close();
    output_file.close();
    return humidity_data;
}

void weather_data_analysis(const std::string& input, const std::string& output){
    std::vector<std::pair<double, int>> humidity_data = parse_weather_data(input, "parsed_data.txt");
    std::vector<std::complex<double>> dataset;
    for(unsigned i=0; i < humidity_data.size(); i++)
        dataset.push_back( std::complex<double>( (double) humidity_data[i].second, 0.0) );

    FFT freq_analysis(dataset);
    std::ofstream output_file(output);
    for(unsigned i=0; i < freq_analysis.size(); i++)
        output_file << (double) i / freq_analysis.size() << " " << std::abs(freq_analysis[i].real()) << "\n";
    output_file.close();
}

int main(){
    std::default_random_engine gen(time(NULL));
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

    std::cout << "\t\t----------Time test----------\n";
    std::vector<std::vector<std::complex<double>>> test_data;
    
    for(unsigned i=4; i <= 13; i++){        // Create test data (random numbers)
        unsigned pwr = std::pow(2, i);
        std::vector<std::complex<double>> test_vec;
        for(unsigned j=0; j < pwr; j++)
            test_vec.push_back(std::complex<double>(dist(gen), dist(gen)));
        test_data.push_back(test_vec);
    }

    std::ofstream dft_res, fft_res, fftw_res;
    dft_res.open("dft_res.txt");        // amount time real_avg_err imag_avg_err (errors compared to fftw)
    fft_res.open("fft_res.txt");        // amount time real_avg_err imag_avg_err (errors compared to fftw)
    fftw_res.open("fftw_res.txt");      // amount time (no error output, because we use there results as accurate)

    for(unsigned i=0; i < test_data.size(); i++){
        std::vector<std::complex<double>> test_vec = test_data[i];
        std::cout << "\tTest for " << test_vec.size() << " elements:\n";

        fftw_complex* in = (fftw_complex*) malloc(sizeof(fftw_complex) * test_vec.size());     // For veryfing
        fftw_complex* out = (fftw_complex*) malloc(sizeof(fftw_complex) * test_vec.size());
        fftw_plan p;
        for(unsigned j=0; j < test_vec.size(); j++){
            in[j][0] = test_vec[j].real();
            in[j][1] = test_vec[j].imag();
        }
        auto start = std::chrono::high_resolution_clock::now();
        p = fftw_plan_dft_1d(test_vec.size(), in, out, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(p);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); 
        fftw_res << test_vec.size() << " " << elapsed_time << "\n";
        std::cout << "FFTW: Elapsed time: " << elapsed_time << " microseconds\n";

        start = std::chrono::high_resolution_clock::now();
        dft_test = DFT(test_vec);
        end = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::complex<double> dft_err = dft_test.compare_with_fftw(out);
        dft_res << test_vec.size() << " " <<  elapsed_time << " " << dft_err.real() << " " << dft_err.imag() << "\n";
        std::cout << "DFT: Elapsed time: " << elapsed_time << " microseconds\n";
        std::cout << "DFT: Avarage numerical error (compared to fftw): " << dft_err << "\n";

        start = std::chrono::high_resolution_clock::now();
        fft_test = FFT(test_vec);
        end = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::complex<double> fft_err = fft_test.compare_with_fftw(out);
        fft_res << test_vec.size() << " " << elapsed_time << " " << fft_err.real() << " " << fft_err.imag() << "\n";
        std::cout << "FFT: Elapsed time: " << elapsed_time << " microseconds\n";
        std::cout << "FFT: Avarage numerical error (compared to fftw): " << fft_err << "\n";

        fftw_destroy_plan(p);
        free(in);
        free(out);
        std::cout << "\n";
    }
    dft_res.close();
    fft_res.close();
    fftw_res.close();

    weather_data_analysis("vancouver_weather_data_7_to_15_may.txt", "freq_data.txt");

    return 0;
}
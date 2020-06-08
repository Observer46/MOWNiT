#pragma once

#include <cmath>
#include <vector>
#include <complex>
#include <fstream>
#include <iostream>

#include "DFT.h"        

class FFT{
    std::vector<std::complex<double>> transform;
public:
    FFT(const std::vector<std::complex<double>>& dataset);
    std::vector<std::complex<double>> rec_fft(const std::vector<std::complex<double>>& dataset, unsigned N);      // recursive function
    std::complex<double> compare_with_fftw(const fftw_complex out[]) const;

    friend std::ostream& operator <<(std::ostream&  os, FFT& fft);
    std::complex<double> operator[] (const size_t& i) const   { return this->transform[i]; };
    unsigned size() const { return this->transform.size(); };
};
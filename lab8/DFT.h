#pragma once

#include <cmath>
#include <vector>
#include <complex>
#include <fstream>
#include <iostream>
#include <fftw3.h>

#define PI 3.14159265

class DFT{
    std::vector<std::complex<double>> transform;
public:
    DFT(const std::vector<std::complex<double>>& dataset);
    
    friend std::ostream& operator <<(std::ostream&  os, DFT& dft);
    std::complex<double> operator[] (const size_t& i) const   { return this->transform[i]; };
    unsigned size() const { return this->transform.size(); };
    std::complex<double> compare_with_fftw(const fftw_complex out[]) const;
};
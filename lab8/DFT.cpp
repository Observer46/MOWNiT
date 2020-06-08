#include "DFT.h"

DFT::DFT(const std::vector<std::complex<double>>& dataset) : transform{}{
    unsigned N = dataset.size();
    for (unsigned k=0; k < N; k++){
        std::complex<double> xk(0.0,0.0);
        for(unsigned n=0; n < N; n++){
            std::complex<double> i(0.0, 1.0);       // i - imaginary
            xk += dataset[n] * std::exp(-i * 2.0 * PI * (double) k * (double) n / (double) N);
        }
        this->transform.push_back(xk);
    }
}

std::complex<double> DFT::compare_with_fftw(const fftw_complex out[]) const{
    unsigned N = this->transform.size();
    std::complex<double> total_err;
    for(unsigned i=0; i < N; i++){
        std::complex<double> diff(std::abs(this->transform[i].real() - out[i][0]), 
                                    std::abs(this->transform[i].imag() - out[i][1]));
        total_err += diff;
    }
    std::complex<double> avg_err = total_err /  (double) N;
    return avg_err;
}

std::ostream& operator <<(std::ostream&  os, DFT& dft){
    for(unsigned k=0; k < dft.transform.size(); k++)
        os << dft.transform[k] << " ";
    return os;
}
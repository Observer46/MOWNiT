#include "FFT.h"

FFT::FFT(const std::vector<std::complex<double>>& dataset) : transform{}{
    unsigned N = dataset.size();
    this->transform.resize(N);
    this->transform = this->rec_fft(dataset, N);
}

std::vector<std::complex<double>> FFT::rec_fft(const std::vector<std::complex<double>>& dataset, unsigned N){
    if (N == 1){
        return dataset;
    }
    if ( (N & (N-1) ) != 0){
        std::vector<std::complex<double>> vec_for_dft;
        for(unsigned i=0; i < N; i++)
            vec_for_dft.push_back(dataset[i]);
        DFT slow_dft(vec_for_dft);
        std::vector<std::complex<double>> res;
        for(unsigned i=0; i < slow_dft.size(); i++)
            res.push_back(slow_dft[i]);
        return res;
    }
    else{
        std::vector<std::complex<double>> even, odd;
        for(unsigned i=0; i < N; i += 2){
            even.push_back(dataset[i]);
            odd.push_back(dataset[i+1]);
        }
        even = rec_fft(even, N / 2);
        odd = rec_fft(odd, N / 2);
        std::complex<double> im_i(0.0, 1.0);
        std::vector<std::complex<double>> res;
        res.resize(N);
        for(unsigned k=0; k < N / 2; k++){
            std::complex<double> t = even[k];
            std::complex<double> exp_val = odd[k] * std::exp(-2.0 * PI * im_i * (double) k / (double) N);
            res[k] = t + exp_val;
            res[N / 2 + k] = t - exp_val;
        }
        return res;
    }
}

std::complex<double> FFT::compare_with_fftw(const fftw_complex out[]) const{
    unsigned N = this->transform.size();
    std::complex<double> total_err;
    for(unsigned i=0; i < N; i++){
        std::complex<double> diff(std::abs(this->transform[i].real() - out[i][0]), 
                                    std::abs(this->transform[i].imag() - out[i][1]));
        total_err += diff;
    }
    std::complex<double> avg_err = total_err / (double) N;
    return avg_err; 
}

std::ostream& operator <<(std::ostream&  os, FFT& fft){
    for(unsigned k=0; k < fft.transform.size(); k++)
        os << fft.transform[k] << " ";
    return os;
}
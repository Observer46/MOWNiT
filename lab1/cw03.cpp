#include <iostream>
#include <cmath>
#include <iomanip>

float floatFrontwardSumming(int precision){
    float sum = 0.0f;
    for(int i=1; i <= precision; i++)
        sum += (float) pow(2, -(i+1) );
    return sum;
}

float floatBackwardSumming(int precision){
    float sum = 0.0f;
    for(int i=precision; i >= 1; i--)
        sum += (float) pow(2, -(i+1) );
    return sum;
}


double doubleFrontwardSumming(int precision){
    double sum = 0.0;
    for(int i=1; i <= precision; i++)
        sum += (double) pow(2, -(i+1) );
    return sum;
}


double doubleBackwardSumming(int precision){
    double sum = 0.0f;
    for(int i=precision; i >= 1; i--)
        sum += (double) pow(2, -(i+1) );
    return sum;
}

float floatKahanSumming(int precision){
    float sum = 0.0f;
    float err = 0.0f;

    for(int i=1; i <= precision; i++)
    {
        float y = (float) pow(2, -(i+1)) - err;
        float temp = sum + y;
        err = (temp - sum) - y;
        sum = temp; 
    }
    return sum;
}

double doubleKahanSumming(int precision){
    double sum = 0.0f;
    double err = 0.0f;

    for(int i=1; i <= precision; i++)
    {
        double y = (double) pow(2, -(i+1)) - err;
        double temp = sum + y;
        err = (temp - sum) - y;
        sum = temp; 
    }
    return sum;
}


int main(){

    std::cout << std::setprecision(100);
    int precisionArray[] = {50, 100, 200, 500, 800};

    for(int precision : precisionArray){
        std::cout << "\t Pomiary dla n = " << precision << std::endl;
        std::cout << "float sumowanie w przod: " << floatFrontwardSumming(precision) << std::endl;
        std::cout << "float sumowanie wstecz: " << floatBackwardSumming(precision) << std::endl;
    }

    std::cout<<"\n\n";

    for(int precision : precisionArray){
        std::cout << "\t Pomiary dla n = " << precision << std::endl;
        std::cout << "double sumowanie w przod: " << doubleFrontwardSumming(precision) << std::endl;
        std::cout << "double sumowanie wstecz: " << doubleBackwardSumming(precision) << std::endl;
    }

    std::cout<<"\n\n";
    
    std::cout << "\t Sumowanie algorytmem Kahana: " << std::endl;
    for(int precision : precisionArray){
        std::cout << "\t Pomiary dla n = " << precision << std::endl;
        std::cout << "float sumowanie algorytmem Kahana: " << floatKahanSumming(precision) << std::endl;
        std::cout << "double sumowanie algorytmem Kahana: " << doubleKahanSumming(precision) << std::endl;
    }

    return 0;
}
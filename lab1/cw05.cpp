#include <iostream>
#include <cmath>

float unstableAlgorithm(int iterations, float x){       // e^{-x}
    float exp = 1;
    long int n = 1;
    for (int i=1; i < iterations; i++){
        n *= i;
        exp += pow(x, i) / n;
    }
    return exp;
}

float stableAlgorithm(int iterations, float x){         // 1/e^x
    float exp = 1;
    long int n = 1;
    if (x < 0)  x = -x;

    for (int i=1; i < iterations; i++){
        n *= i;
        exp += pow(x,i) / n;
    }
    return 1/exp;
}


int main(){
    float x = -3.5;
    float fx = unstableAlgorithm(10, x);
    float stablefx = stableAlgorithm(10,x);
    std::cout <<"Oczekiwana wartosc: " << exp(x) << ", uzyskana niestablinie: " << fx << ", uzyskana stablinie: " << stablefx << std::endl;

    return 0;
}
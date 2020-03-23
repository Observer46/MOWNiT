#include <iostream>
#include <iomanip>


int main(){
    std::cout << std::setprecision(100);
    float flEps = 1.0f;
    float flOne = 1.0f;
    while( (flOne + flEps*0.5f) != flOne )
        flEps *= 0.5f;

    double dbEps = 1.0;
    double dbOne = 1.0;
    while( (dbOne + dbEps*0.5f) != dbOne )
        dbEps *= 0.5f;

    std::cout << "Maszynowy epsilon dla float: " << flEps << std::endl;
    std::cout << "Maszynowy epsilon dla double: " << dbEps << std::endl;

    return 0;
}
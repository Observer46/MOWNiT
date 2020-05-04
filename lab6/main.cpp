#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <exception>
#include <algorithm>

#include "aghMatrix.h"
#include "testSOLEs.h"

#include "jacobi.h"
#include "gaussseidel.h"
#include "sor.h"

#define test_count 8

int main(){
    TestSOLEs<double> soles_for_tests;
    for(size_t i=0; i < test_count; i++){
        std::vector<AGHMatrix<double>> sole_i = soles_for_tests.get_sole(i);
        Jacobi<double> jacobi_solution(sole_i[0], sole_i[1], 30);
        GaussSeidel<double> gauss_seidel_solution(sole_i[0], sole_i[1], 30);
        SOR<double> sor_solution(sole_i[0], sole_i[1], 1.25, 30);
        std::cout << jacobi_solution.get_solution() << gauss_seidel_solution.get_solution() << sor_solution.get_solution() << "\n\n\n";
    }
    return 0;
}
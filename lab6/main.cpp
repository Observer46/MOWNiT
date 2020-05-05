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
    const double omega = 0.9;
    const unsigned iterations = 30;
    for(size_t i=0; i < test_count; i++){
        std::vector<AGHMatrix<double>> sole_i = soles_for_tests.get_sole(i);
        std::cout << "\t Przyklad " << i + 1 << ":\nA:\n" << sole_i[0] << "b:\n" << sole_i[1] << "Poprawna odpowiedz:\n" << sole_i[2] << "--------\n\n";
        Jacobi<double> jacobi_solution(sole_i[0], sole_i[1], sole_i[2], iterations, i+1);
        GaussSeidel<double> gauss_seidel_solution(sole_i[0], sole_i[1], sole_i[2], iterations, i+1);
        SOR<double> sor_solution(sole_i[0], sole_i[1], sole_i[2], omega, iterations, i+1);
        std::cout << "Jacobi:\n" << jacobi_solution.get_solution() << "Gauss-Seidel:\n" << gauss_seidel_solution.get_solution() << "Successive Over-Relaxation:\n" << sor_solution.get_solution() << "\n\n\n";
    }
    return 0;
}
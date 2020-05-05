#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include "aghMatrix.h"

template <typename T> class SOR    // Successive Over Relaxation
{
private:
    AGHMatrix<T> A_mat;
    AGHMatrix<T> b_mat;
    AGHMatrix<T> x_mat;
    const double omega;
public:
    // eps < 0 oznacza, ze nie patrzymy na warunek roznicy poprzednich wynikow 
    SOR(const AGHMatrix<T>& A_mat, const AGHMatrix<T>& b_mat, const AGHMatrix<T>& solution, const double& omega, const unsigned& iterations, const unsigned& example_no, const double& eps = -1.0);

    AGHMatrix<T> get_A_mat() const { return this->A_mat; }
    AGHMatrix<T> get_b_mat() const { return this->b_mat; }
    AGHMatrix<T> get_solution() const { return this->x_mat; }
}; 

#include "sor.cpp"
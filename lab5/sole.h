#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include "aghMatrix.h"

template <typename T> class SOLE    // System of linear equations
{
private:
    AGHMatrix<T> A_mat;
    AGHMatrix<T> y_vector;
public:
    SOLE(const AGHMatrix<T>& A_mat, const AGHMatrix<T>& y_vector);

    // Solving systems of linear equations
    AGHMatrix<T> solve_gauss() const;
    AGHMatrix<T> solve_jacobi(unsigned iterations) const;

    // Access to parametres
    AGHMatrix<T> get_A_mat() const;
    AGHMatrix<T> get_y_vector() const;
};

#include "sole.cpp"
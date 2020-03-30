#pragma once 

#include <cmath>
#include <iostream>
#include <stdexcept>
#include "aghMatrix.h"

// Zadanie 4
//////////////////////////
template <typename T> class CholeskyFactor 
{
private:
    AGHMatrix<T> original_matrix;
    AGHMatrix<T> lower;
    unsigned rows;
    unsigned cols;

public:
    CholeskyFactor(const AGHMatrix<T>& rhs);
    CholeskyFactor(const std::vector<std::vector<T>>& matrix);
    virtual ~CholeskyFactor() = default;

    // Access to parametres                                                                                                                                                                                             
    AGHMatrix<T> get_original_matrix() const;
    AGHMatrix<T> get_lower() const;
    AGHMatrix<T> get_trans_lower() const;
    unsigned get_rows() const;
    unsigned get_cols() const;

};

#include "choleskyFactor.cpp"
/////////////////////////////
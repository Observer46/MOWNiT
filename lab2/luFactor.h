#pragma once 

#include <iostream>
#include "aghMatrix.h"

// Zadanie 3
/////////////////////
template <typename T> class LUFactor 
{
private:
    AGHMatrix<T> original_matrix;
    AGHMatrix<T> lower;
    AGHMatrix<T> upper;
    unsigned rows;
    unsigned cols;

public:
    LUFactor(const AGHMatrix<T>& rhs);
    LUFactor(const std::vector<std::vector<T>>& matrix);
    virtual ~LUFactor() = default;
    
    // Access to parametres                                                                                                                                                                                        
    AGHMatrix<T> get_original_matrix() const;
    AGHMatrix<T> get_lower() const;
    AGHMatrix<T> get_upper() const;
    unsigned get_rows() const;
    unsigned get_cols() const;

};

#include "luFactor.cpp"
/////////////////////////
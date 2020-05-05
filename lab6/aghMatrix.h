#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T> class AGHMatrix 
{
private:
    std::vector<std::vector<T>> matrix;
    unsigned rows;
    unsigned cols;

public:
    AGHMatrix(const std::vector<std::vector<T>>& matrix);
    AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial);
    AGHMatrix(const AGHMatrix<T>& rhs);
    virtual ~AGHMatrix() = default;

    // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
    AGHMatrix<T>& operator=(const AGHMatrix<T>& rhs);

    // Matrix mathematical operations                                                                                                                                                                                               
    AGHMatrix<T> operator+(const AGHMatrix<T>& rhs);
    AGHMatrix<T> operator*(const AGHMatrix<T>& rhs);

    // Access the individual elements                                                                                                                                                                                               
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;

    // Access whole row (added)
    const std::vector<T>& get_whole_row(const unsigned& row) const;

    // Swap two rows (added)
    void swap_rows(const unsigned& i, const unsigned& j) ;

    // Equality of matrices (added)
    bool operator==(const AGHMatrix<T>& rhs) const;
    bool almost_eq(const AGHMatrix<double>& rhs) const;      // almost equal
    
    // Printing matrix
    std::ostream& operator<<(const AGHMatrix<T>& matrix);

    // Access the row and column sizes                                                                                                                                                                                              
    unsigned get_rows() const;
    unsigned get_cols() const;

    // Checking if matrix is symmetric
    bool is_symmetric() const;

    // T det TODO
    T det() const;

    // Transposition
    AGHMatrix<T>& transpose();

    static AGHMatrix<T> solve_gauss(const AGHMatrix<T>& A, const AGHMatrix<T>& b);
};

template<typename T>
int gaussian_elimination(AGHMatrix<T>& mat);

#include "aghMatrix.cpp"
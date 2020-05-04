#pragma once
;
#include <vector>
#include <iostream>
#include <stdexcept>
#include "aghMatrix.h"

template <typename T> class TestSOLEs    // Test System Of Linear Equations
{
    static constexpr size_t sole_count = 8;
    std::vector< std::vector<AGHMatrix<T>> > soles;   // Uklady trzymamy jako pary macierzy (A, b), zatem kazdy vector wewnatrz ma rozmar 2
    size_t _size;

public:
    TestSOLEs();
    ~TestSOLEs() = default;

    std::vector<AGHMatrix<T>> get_sole(const size_t& i) const   { return (i >= this->_size) ? throw std::out_of_range("There aren't this many soles!") : this->soles[i]; }
    size_t size() const     { return this->_size; }
};
#include "testSOLEs.cpp"
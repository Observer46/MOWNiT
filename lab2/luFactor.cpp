#include "luFactor.h"

// Zadanie 3
/////////////////////
// lower i upper musza w jakis sposob byc zainicjalizowane by konstruktor sie uruchomil (stad taka lista inicjalizacyjna)
template<typename T>
LUFactor<T>::LUFactor(const AGHMatrix<T>& original_matrix) : original_matrix{original_matrix}, lower{original_matrix}, upper{original_matrix} {
    rows = original_matrix.get_rows();
    cols = original_matrix.get_cols();
    T initial{};

    AGHMatrix low(rows, cols, initial);
    lower = low;
    AGHMatrix up(rows, cols, initial);
    upper = up;
    
    for(unsigned i=0; i < rows; i++)
        this -> lower(i, i) = 1;

    for(unsigned i=0; i < rows; i++){

        for(unsigned j=i; j < cols; j++){       // Wyznaczamy wiersz U (upper)
            T sum{};
            for(unsigned k=0; k < i; k++)
                sum += lower(i, k) * upper(k, j);

            upper(i, j) = original_matrix(i, j) - sum;
        }

        for(unsigned j=i+1; j < rows; j++){       // Wyznaczamy kolumne L (lower)
            T sum{};
            for(unsigned k=0; k < i; k++)
                sum += lower(j, k) * upper(k, i);

            lower(j, i) = 1/ upper(i, i) * ( original_matrix(j, i) - sum);
        }
    }
}

template<typename T>
LUFactor<T>::LUFactor(const std::vector<std::vector<T>>& matrix) : LUFactor{AGHMatrix{matrix}} {};

template<typename T>
AGHMatrix<T> LUFactor<T>::get_original_matrix() const{
    return this -> original_matrix;
}

template<typename T>
AGHMatrix<T> LUFactor<T>::get_lower() const{
    return this -> lower;
}

template<typename T>
AGHMatrix<T> LUFactor<T>::get_upper() const{
    return this -> upper;
}

template<typename T>
unsigned LUFactor<T>::get_rows() const{
    return this -> rows;
}

template<typename T>
unsigned LUFactor<T>::get_cols() const{
    return this -> cols;
}
///////////////////////////
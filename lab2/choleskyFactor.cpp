#include "choleskyFactor.h"

// Zadanie 4
/////////////////////////////
// lower musi w jakis sposob byc zainicjalizowane by konstruktor sie uruchomil (stad taka lista inicjalizacyjna)
template<typename T>
CholeskyFactor<T>::CholeskyFactor(const AGHMatrix<T>& original_matrix) : original_matrix{original_matrix}, lower{original_matrix} {
    if ( !original_matrix.is_symmetric() )
        throw std::invalid_argument("Cannot perform Cholsky factorization on unsymmteric matrix!");

    rows = original_matrix.get_rows();
    cols = original_matrix.get_cols();
    T initial{};

    AGHMatrix low(rows, cols, initial);
    lower = low;

    for(unsigned i=0; i < rows; i++){
        
        T sum_for_diag{};           // Liczymy element na przekatnej
        for(unsigned k=0; k < i; k++)        
            sum_for_diag += lower(i, k) * lower(i, k);

        lower(i, i) = sqrt( original_matrix(i, i) - sum_for_diag);

        for(unsigned j=i+1; j < rows; j++){       // Wyznaczamy kolumne L
            T sum{};
            for(unsigned k=0; k < i; k++)
                sum += lower(j, k) * lower(i, k);

            lower(j, i) = ( original_matrix(j, i) - sum ) / lower(i, i);
        }
    }
}

template<typename T>
CholeskyFactor<T>::CholeskyFactor(const std::vector<std::vector<T>>& matrix) : CholeskyFactor{AGHMatrix{matrix}} {};

template<typename T>
AGHMatrix<T> CholeskyFactor<T>::get_original_matrix() const{
    return this -> original_matrix;
}

template<typename T>
AGHMatrix<T> CholeskyFactor<T>::get_lower() const{
    return this -> lower;
}

template<typename T>
AGHMatrix<T> CholeskyFactor<T>::get_trans_lower() const{
    AGHMatrix<T> trans_lower(lower);
    trans_lower.transpose();
    return trans_lower;
}

template<typename T>
unsigned CholeskyFactor<T>::get_rows() const{
    return this -> rows;
}

template<typename T>
unsigned CholeskyFactor<T>::get_cols() const{
    return this -> cols;
}
///////////////////////
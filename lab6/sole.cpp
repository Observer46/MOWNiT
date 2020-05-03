#include "sole.h"


// Augmented musi byc jakos zainicjalizowane, stad jest na liscie inicjalizacjynej
template <typename T>
SOLE<T>::SOLE(const AGHMatrix<T>& A_mat, const AGHMatrix<T>& y_vector) : A_mat{A_mat}, y_vector{y_vector} {
    if( A_mat.get_rows() != y_vector.get_rows() )
        throw std::invalid_argument("Cannot build system of linear equations out of this matrices!");
    if( y_vector.get_cols() != 1)
        throw std:: invalid_argument("y_vector must be a vector (only 1 column)!");
};

// Zadanie 5 - rozwiazanie ukladu rownan metoda eliminacji Gaussa
/////////////////////////////////
template<typename T>
AGHMatrix<T> SOLE<T>::solve_gauss() const{
    unsigned A_rows = A_mat.get_rows();
    unsigned A_cols = A_mat.get_cols();
    T initial{};

    AGHMatrix<T> augmented (A_rows, A_cols + 1, initial);
    for(unsigned i=0; i < A_rows; i++){
        for(unsigned j=0; j < A_cols; j++)
            augmented(i, j) = A_mat(i, j);
        augmented(i, A_cols) = y_vector(i, 0);
    }

    gaussian_elimination(augmented);

    std::vector<std::vector<T>> solution;
    solution.resize( augmented.get_rows() );
    int sol_idx = (int) augmented.get_cols() - 1;

    for(int i=(int) augmented.get_rows() - 1; i >= 0; i-- ){
        T x = augmented(i, sol_idx);
        for(int j=sol_idx - 1; j > i; j--)
            x -= augmented(i, j) * solution[j][0];
        x /= augmented(i, i);
        solution[i].push_back(x);
    }
    AGHMatrix<T> solution_matrix (solution);
    return solution_matrix;
}

// Zadanie 6 - metoda Jacobiego
////////////////////////////////
template<typename T>
AGHMatrix<T> SOLE<T>::solve_jacobi(unsigned iterations) const{
    std::vector<T> solution;
    solution.resize( A_mat.get_rows(), 1);
    unsigned A_rows = A_mat.get_rows();
    unsigned A_cols = A_mat.get_cols();

    for(unsigned k=0; k < iterations; k++){
        std::vector<T> prev_sol(solution);
        for(unsigned i=0; i < A_rows; i++){
            T sum{};
            for(unsigned j=0; j < A_cols; j++)
                sum += (j != i) ? A_mat(i, j) * prev_sol[j] : 0;
            solution[i] = ( y_vector(i, 0) - sum) / A_mat(i, i);
        }
    }
    std::vector<std::vector<T>> sol_vector;
    sol_vector.resize(A_rows);
    for(unsigned i=0; i < A_rows; i++)
        sol_vector[i].resize(1, solution[i]);
    
    AGHMatrix<T> solution_matrix(sol_vector);
    return solution_matrix;
}
///////////////////////////////

template<typename T>
AGHMatrix<T> SOLE<T>::get_A_mat() const{
    return this -> A_mat;
}

template<typename T>
AGHMatrix<T> SOLE<T>::get_y_vector() const{
    return this -> y_vector;
}
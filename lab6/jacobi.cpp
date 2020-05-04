#include "jacobi.h"

template <typename T>                                                 // W jakikolwiek sposob inicjalizujemy x_mat
Jacobi<T>::Jacobi(const AGHMatrix<T>& A_mat, const AGHMatrix<T>& b_mat, const unsigned& iterations, const double& eps) : A_mat{A_mat}, b_mat{b_mat}, x_mat{b_mat} {
    if( A_mat.get_rows() != b_mat.get_rows() )
        throw std::invalid_argument("Cannot build system of linear equations out of this matrices!");
    if( b_mat.get_cols() != 1)
        throw std:: invalid_argument("b_mat must be a vector (only 1 column)!");

    unsigned A_rows = A_mat.get_rows();
    unsigned A_cols = A_mat.get_cols();
    double improv = eps + 1.0;  // Cos, co bedzie spelnialo poczatkowego warunku

    for(unsigned k=0; k < iterations && improv > eps; k++){
        AGHMatrix<T> prev_sol(this->x_mat);
        for(unsigned i=0; i < A_rows; i++){
            T sum{};
            for(unsigned j=0; j < A_cols; j++)
                sum += (j != i) ? A_mat(i, j) * prev_sol(j, 0) : 0;
            this->x_mat(i, 0) = ( b_mat(i, 0) - sum) / A_mat(i, i);
        }

        // Znajdujemy maksymalna poprawe i ja przyjmujemy za improv
        for(unsigned i=0; i < A_rows; i++){
            double delta = abs(this->x_mat(i, 0) - prev_sol(i, 0));
            if (delta > improv)
                improv = delta;
        }
    }
}

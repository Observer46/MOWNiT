#include "sor.h"

template <typename T>                                                 // W jakikolwiek sposob inicjalizujemy x_mat
SOR<T>::SOR(const AGHMatrix<T>& A_mat, const AGHMatrix<T>& b_mat, const double& omega, const unsigned& iterations, const double& eps) : A_mat{A_mat}, b_mat{b_mat}, x_mat{b_mat}, omega{omega} {
    if( A_mat.get_rows() != b_mat.get_rows() )
        throw std::invalid_argument("Cannot build system of linear equations out of this matrices!");
    if( b_mat.get_cols() != 1)
        throw std:: invalid_argument("b_mat must be a vector (only 1 column)!");

    unsigned A_rows = A_mat.get_rows();
    unsigned A_cols = A_mat.get_cols();
    double improv = eps + 1.0;          // Cos, co bedzie spelnialo poczatkowego warunku

    for(unsigned k=0; k < iterations && improv > eps; k++){
        AGHMatrix<T> prev_sol(this->x_mat);
        for(unsigned i=0; i < A_rows; i++){
            T sum{};
            unsigned j;
            for(j=0; j < i; j++)
                sum += A_mat(i, j) * this->x_mat(j, 0);     // Niewiadome az do i-tej sa juz aktualizowane
                
            for(j++; j < A_cols; j++)                       // Pomijamy element na przekatnej poprzez inkrementacje
                sum += A_mat(i, j) * this->x_mat(j, 0);     // Te sa jeszcze nie zaktualizowane

            this->x_mat(i, 0) =(1.0 - omega) * this->x_mat(i, 0) + omega * ( b_mat(i, 0) - sum) / A_mat(i, i);
        }

        // Znajdujemy maksymalna poprawe i ja przyjmujemy za improv
        for(unsigned i=0; i < A_rows; i++){
            double delta = abs(this->x_mat(i, 0) - prev_sol(i, 0));
            if (delta > improv)
                improv = delta;
        }
    }
}

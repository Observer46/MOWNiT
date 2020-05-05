#include "gaussseidel.h"

template <typename T>                                                 // W jakikolwiek sposob inicjalizujemy x_mat
GaussSeidel<T>::GaussSeidel(const AGHMatrix<T>& A_mat, const AGHMatrix<T>& b_mat, const AGHMatrix<T>& solution, const unsigned& iterations, const unsigned& example_no, const double& eps) : A_mat{A_mat}, b_mat{b_mat}, x_mat{b_mat} {
    if( A_mat.get_rows() != b_mat.get_rows() )
        throw std::invalid_argument("Cannot build system of linear equations out of this matrices!");
    if( b_mat.get_cols() != 1)
        throw std:: invalid_argument("b_mat must be a vector (only 1 column)!");

    unsigned A_rows = A_mat.get_rows();
    unsigned A_cols = A_mat.get_cols();
    double improv = eps + 1.0;          // Cos, co bedzie spelnialo poczatkowego warunku

    std::ofstream err_data;
    err_data.open("GaussSeidel_example_" + std::to_string(example_no) + ".txt");

    for(unsigned k=0; k < iterations && improv > eps; k++){
        improv = 0.0;
        AGHMatrix<T> prev_sol(this->x_mat);
        for(unsigned i=0; i < A_rows; i++){
            T sum{};
            unsigned j;
            for(j=0; j < i; j++)
                sum += A_mat(i, j) * this->x_mat(j, 0);     // Niewiadome az do i-tej sa juz aktualizowane
                
            for(j++; j < A_cols; j++)                       // Pomijamy element na przekatnej poprzez inkrementacje
                sum += A_mat(i, j) * this->x_mat(j, 0);     // Te sa jeszcze nie zaktualizowane

            this->x_mat(i, 0) = ( b_mat(i, 0) - sum) / A_mat(i, i);
        }

        // Znajdujemy maksymalna poprawe i ja przyjmujemy za improv
        for(unsigned i=0; i < A_rows; i++){
            double delta = abs(this->x_mat(i, 0) - prev_sol(i, 0));
            if (delta > improv)
                improv = delta;
        }
        if (k < 10){
            double delta_from_res = 0.0;
            for(unsigned i=0; i < A_rows; i++)
                delta_from_res += std::abs(solution(i, 0) - this->x_mat(i, 0));
            err_data << k+1 << " " << delta_from_res << "\n";
        }
    }
    err_data.close();
}

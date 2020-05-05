#include "testSOLEs.h"

// Bardzo dlugi kawalek kodu, tworzacy testowe uklady rownan
template <typename T>
TestSOLEs<T>::TestSOLEs() : soles{}, _size{0}{
    /////////////// 1
    std::vector<std::vector<double>> A1_v = {{3.0, 2.0},
                                            {-1.0, 4.0}};
    std::vector<std::vector<double>> b1_v = {{3.0}, {1.0}}; // Pionowy wektor

    std::vector<AGHMatrix<T>> sole1;
    sole1.push_back(AGHMatrix<T>(A1_v));
    sole1.push_back(AGHMatrix<T>(b1_v));
    sole1.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A1_v), AGHMatrix<T>(b1_v))); // Rozwiazanie
    this->soles.push_back(sole1);
    this->_size++;

    /////////////// 2
    std::vector<std::vector<double>> A2_v = {{5.0, 2.0, 1.0},
                                        {-3.0, 10.0, 4.0},
                                        {20.0, -3.0, 30.0} };
    std::vector<std::vector<double>> b2_v = {{1.0}, {2.0}, {3.0}};

    std::vector<AGHMatrix<T>> sole2;
    sole2.push_back(AGHMatrix<T>(A2_v));
    sole2.push_back(AGHMatrix<T>(b2_v));
    sole2.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A2_v), AGHMatrix<T>(b2_v)));
    this->soles.push_back(sole2);
    this->_size++;

    /////////////// 3
    std::vector<std::vector<double>> A3_v = {{13.5, 5.3, -3.9},
                                            {2.9, 7.1, 1.7},
                                            {1.1, -4.7, 8.1} };
    std::vector<std::vector<double>> b3_v = {{3.5}, {9.7}, {1.7}};

    std::vector<AGHMatrix<T>> sole3;
    sole3.push_back(AGHMatrix<T>(A3_v));
    sole3.push_back(AGHMatrix<T>(b3_v));
    sole3.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A3_v), AGHMatrix<T>(b3_v)));
    this->soles.push_back(sole3);
    this->_size++;

    /////////////// 4
    std::vector<std::vector<double>> A4_v = {{10.23, 2.21, 3.54},
                                            {3.69, 15.72, 8.13},
                                            {-6.93, 1.45, 12.12} };
    std::vector<std::vector<double>> b4_v = {{12.67}, {8.74}, {7.5}};

    std::vector<AGHMatrix<T>> sole4;
    sole4.push_back(AGHMatrix<T>(A4_v));
    sole4.push_back(AGHMatrix<T>(b4_v));
    sole4.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A4_v), AGHMatrix<T>(b4_v)));
    this->soles.push_back(sole4);
    this->_size++;

    /////////////// 5
    std::vector<std::vector<double>> A5_v = {{80.801, -7.4319, 43.6892, 1.0001},
                                            {6.3159, -100.101,  32.135, -57.985},
                                            {-6.3873, -10.555,  54.43, 22.19},
                                            {5.32, -8.234,  -10.345, 46.4343} };
    std::vector<std::vector<double>> b5_v = {{19.1508}, {65.1693}, {1.9015}, {100.31}};

    std::vector<AGHMatrix<T>> sole5;
    sole5.push_back(AGHMatrix<T>(A5_v));
    sole5.push_back(AGHMatrix<T>(b5_v));
    sole5.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A5_v), AGHMatrix<T>(b5_v)));
    this->soles.push_back(sole5);
    this->_size++;

    /////////////// 6
    std::vector<std::vector<double>> A6_v = {{-61.302, 9.3913, 13.8632, 20.2358},
                                            {14.2962, 94.216,  -26.331, 33.8251},
                                            {6.8313, -5.777,  -24.131, -10.139},
                                            {-7.1, 29.741,  -8.918, 56.9661} };
    std::vector<std::vector<double>> b6_v = {{291.1081}, {-40.2311}, {-78.5455}, {62.132}};

    std::vector<AGHMatrix<T>> sole6;
    sole6.push_back(AGHMatrix<T>(A6_v));
    sole6.push_back(AGHMatrix<T>(b6_v));
    sole6.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A6_v), AGHMatrix<T>(b6_v)));
    this->soles.push_back(sole6);
    this->_size++;

    /////////////// 7
    std::vector<std::vector<double>> A7_v = {{43.01, 5.002, -23.112, 0.9201},
                                            {-17.734, 57.101,  -21.531, -4.445},
                                            {-11.1012, 16.761,  -61.7489, 20.1309},
                                            {-19.993, 42.131,  31.6329, 123.123} };
    std::vector<std::vector<double>> b7_v = {{1.1111}, {2.2222}, {3.3333}, {4.4444}};

    std::vector<AGHMatrix<T>> sole7;
    sole7.push_back(AGHMatrix<T>(A7_v));
    sole7.push_back(AGHMatrix<T>(b7_v));
    sole7.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A7_v), AGHMatrix<T>(b7_v)));
    this->soles.push_back(sole7);
    this->_size++;

    /////////////// 8
    std::vector<std::vector<double>> A8_v = {{235.167, -57.439, 17.0921, -138.7552, 5.2057},
                                            {-25.3271, 87.9536,  11.3692, 6.4365, -21.1269},
                                            {-13.3378, -37.179,  -91.382, -11.9683, 6.9215},
                                            {1.593, -2.1479,  -14.6703, 38.4833, -8.7849},
                                            {0.5493, -103.275,  53.684, -83.9674, 341.683} };
    std::vector<std::vector<double>> b8_v = {{3.012}, {78.3318}, {59.4835}, {1265.315}, {363.19}};

    std::vector<AGHMatrix<T>> sole8;
    sole8.push_back(AGHMatrix<T>(A8_v));
    sole8.push_back(AGHMatrix<T>(b8_v));
    sole8.push_back(AGHMatrix<T>::solve_gauss(AGHMatrix<T>(A8_v), AGHMatrix<T>(b8_v)));
    this->soles.push_back(sole8);
    this->_size++;
}
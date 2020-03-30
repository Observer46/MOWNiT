#include <string>
#include <gtest/gtest.h>

#include "aghMatrix.h"
#include "luFactor.h"
#include "choleskyFactor.h"
#include "sole.h"


TEST (TestEx01, Addition){
    AGHMatrix<double> matA1(5, 5, 1.2);
    AGHMatrix<double> matB1(5, 5, 2.8);
    AGHMatrix<double> expected1(5, 5, 4.0);

    AGHMatrix<double> matA2(10, 10, 3.0);
    AGHMatrix<double> matB2(10, 10, 4.0);
    AGHMatrix<double> expected2(10, 10, 7.0);

    EXPECT_EQ (expected1, matA1 + matB1);
    EXPECT_EQ (expected2, matA2 + matB2);
}

TEST (TestEx01, Multiplication){
    AGHMatrix<double> I(5, 5, 1.0);
    for(unsigned i=0; i < I.get_rows(); i++)
        for(unsigned j=0; j < I.get_cols(); j++)
            I(i, j) = (i == j) ? 1.0 : 0;

    AGHMatrix<double> mat1(5, 5, 3.0);
    AGHMatrix<double> mat2(5, 5, 2.0);
    AGHMatrix<double> expected1(5, 5, 30.0);

    AGHMatrix<double> mat3(3, 5, 4.0);
    AGHMatrix<double> mat4(5, 3, 3.5);
    AGHMatrix<double> expected2(3, 3, 70.0);
    AGHMatrix<double> expected3(5, 5, 42.0);

    EXPECT_EQ (mat1, mat1 * I);
    EXPECT_EQ (expected1, mat1 * mat2);
    EXPECT_EQ (expected2, mat3 * mat4);
    EXPECT_EQ (expected3, mat4 * mat3);
}

TEST (TestEx02, IsSymmetric){
    AGHMatrix<double> mat1 (5, 5, 2.5);
    AGHMatrix<int> mat2 (3, 4, 10);
    AGHMatrix<std::string> mat3 (6, 6, "jacek");

    std::vector<std::vector<double>> vect4mat4 = {{1.0, 2.0, 3.0},
                                                    {2.0, 4.0, 5.0},
                                                    {3.0, 5.0, 6.0}};
    AGHMatrix<double> mat4(vect4mat4);

    std::vector<std::vector<double>> vect4mat5 = {{1.0, 2.0, 3.0},
                                                    {2.0, 4.0, 15.0},
                                                    {13.0, 5.0, 6.0}};
    AGHMatrix<double> mat5(vect4mat5);

    EXPECT_EQ(true, mat1.is_symmetric());
    EXPECT_EQ(false, mat2.is_symmetric());
    EXPECT_EQ(true, mat3.is_symmetric());
    EXPECT_EQ(true, mat4.is_symmetric());
    EXPECT_EQ(false, mat5.is_symmetric());
}

TEST (TestEx02, Determinant){
    AGHMatrix<double> mat1(4, 5, 1.0);
    AGHMatrix<double> mat2(5, 5, 2.4);

    std::vector<std::vector<double>> vector4mat3 = { {1.0, 2.0, 3.0},
                                                        {4.0, 5.0, 6.0},
                                                        {7.0, 8.0, 9.0}};
    AGHMatrix<double> mat3(vector4mat3);

    std::vector<std::vector<double>> vect4mat4 = { {6.0, 5.0, 5.0},
                                                    {2.0, 3.0, 3.0},
                                                    {1.0, 2.0, 6.0}};
    AGHMatrix<double> mat4(vect4mat4);
    
    EXPECT_THROW ( mat1.det(), std::logic_error );
    EXPECT_EQ ( 0, mat2.det() );
    EXPECT_EQ ( 0, mat3.det() );
    EXPECT_EQ ( 32.0, mat4.det() );
}

TEST (TestEx02, Transposition){
    AGHMatrix<std::string> mat1 (3, 3, "placek");
    AGHMatrix<std::string> expected1(mat1);

    AGHMatrix<double> mat2 (3, 4, 2.0);
    AGHMatrix<double> expected2(4, 3, 2.0);

    std::vector<std::vector<std::string>> vector4mat3 = { {"ala", "ma", "czarnego", "kota"},
                                                    {"ktory", "lubi", "udawac", "chleb"} };
    AGHMatrix<std::string> mat3(vector4mat3);

    std::vector<std::vector<std::string>> vector4expected3 = { {"ala", "ktory"},
                                                                {"ma", "lubi"},
                                                                {"czarnego", "udawac"},
                                                                {"kota", "chleb"} };
    AGHMatrix<std::string> expected3 (vector4expected3);

    EXPECT_EQ (expected1, mat1.transpose() );

    EXPECT_EQ (expected2, mat2.transpose() );
    EXPECT_EQ (expected2.get_rows(), mat2.get_rows());
    EXPECT_EQ (expected2.get_cols(), mat2.get_cols());

    EXPECT_EQ (expected3, mat3.transpose() );
    EXPECT_EQ (expected3.get_rows(), mat3.get_rows());
    EXPECT_EQ (expected3.get_cols(), mat3.get_cols());
}

TEST (TestEx03, LUFactorization){
    std::vector<std::vector<double>> init_LU {{ 5.0, 3.0, 2.0 }, 
                                          { 1.0, 2.0, 0.0 }, 
                                          { 3.0, 0.0, 4.0 }};
    AGHMatrix<double> mat(init_LU);

    std::vector<std::vector<double>> vector4expectedL = { {1.0, 0.0, 0.0},
                                                        {0.2, 1.0, 0.0},
                                                        {0.6, -9.0/7.0, 1.0}};
    AGHMatrix<double> expectedL (vector4expectedL);

    std::vector<std::vector<double>> vector4expectedU = { {5.0, 3.0, 2.0},
                                                        {0.0, 1.4, -0.4},
                                                        {0.0, 0.0, 16.0/7.0}};
    AGHMatrix<double> expectedU (vector4expectedU);

    LUFactor luFact(mat);

    AGHMatrix<double> mul_res (luFact.get_lower() * luFact.get_upper());

    std::cout << "mat:" << std::endl << mat;
    std::cout << "L:" << std::endl << luFact.get_lower();
    std::cout << "U:" << std::endl << luFact.get_upper();
    
    EXPECT_TRUE ( expectedL.almost_eq(luFact.get_lower()) );
    EXPECT_EQ (expectedU, luFact.get_upper());
    EXPECT_TRUE ( mat.almost_eq(mul_res) );
    
}

TEST (TestEx04, CholeskyFactorization){
    std::vector<std::vector<double>> init_cholesky {{ 4.0, 12.0, -16.0 }, 
                                                { 12.0, 37.0, -43.0 }, 
                                                { -16.0, -43.0, 98.0 }};
    AGHMatrix<double> mat(init_cholesky);

    std::vector<std::vector<double>> vector4decomp {{ 2.0, 0.0, 0.0 }, 
                                                { 6.0, 1.0, 0.0 }, 
                                                { -8.0, 5.0, 3.0 }};
    AGHMatrix<double> expectedDecomp(vector4decomp);

    AGHMatrix<double> expectedDecompTrans(expectedDecomp);
    expectedDecompTrans.transpose();

    std::vector<std::vector<double>> vector4wrong { {1.0, 2.0}, 
                                                    {3.0, 4.0}};
    AGHMatrix<double> wrongMat(vector4wrong);

    CholeskyFactor cholFact(mat);

    std::cout << "mat:" << std::endl << mat;
    std::cout << "L:" << std::endl << cholFact.get_lower();
    std::cout << "L^T:" << std::endl << cholFact.get_trans_lower();

    EXPECT_THROW (CholeskyFactor wrong(wrongMat), std::invalid_argument );
    EXPECT_EQ (expectedDecomp, cholFact.get_lower() );
    EXPECT_EQ (expectedDecompTrans, cholFact.get_trans_lower() );
    EXPECT_EQ (mat, cholFact.get_lower() * cholFact.get_trans_lower() );
}

TEST (TestEx05, GaussianElimination){
    std::vector<std::vector<double>> A = {{0.0001, -5.0300, 5.8090, 7.8320},
                                        {2.2660, 1.9950,  1.2120, 8.0080},
                                        {8.8500, 5.6810,  4.5520, 1.3020},
                                        {6.7750, -2.253,  2.9080, 3.9700}};
    std::vector<std::vector<double>> b = { {9.5740},
                                            {7.2190},
                                            {5.7300},
                                            {6.2910}};
    AGHMatrix<double> A_mat(A);
    AGHMatrix<double> b_mat(b);
    SOLE<double> eq_system(A_mat, b_mat);
    AGHMatrix<double> solution = eq_system.solve_gauss();
    
    std::vector<std::vector<double>> vector4solution = { {0.2160247670},
                                            {-0.0079151061},
                                            {0.6352433265},
                                            {0.7461742761}};
    AGHMatrix<double> expectedSolution(vector4solution);

    std::cout << "A:" << std::endl << A_mat;
    std::cout << "y:" << std::endl << b_mat;
    std::cout << "x:" << std::endl << solution;

    ASSERT_TRUE (expectedSolution.almost_eq(solution));
}

TEST (TestEx06, JacobiMethod){
    std::vector<std::vector<double>> A {{50.3, -5.0300, 5.8090, 7.8320},
                                    {2.2660, 60.8,  1.2120, 8.0080},
                                    {8.8500, 5.6810,  30.5, 1.3020},
                                    {6.7750, -2.253,  2.9080, 20.7}};
    std::vector<std::vector<double>> b = { {9.5740},
                                        {7.2190},
                                        {5.7300},
                                        {6.2910}};
    AGHMatrix<double> A_mat (A);
    AGHMatrix<double> b_mat (b);
    SOLE<double> eq_system(A_mat, b_mat);

    AGHMatrix<double> solutionGauss = eq_system.solve_gauss();      // Zakladamy, ze Gauss dziala i z nim porownujemy wyniki

    AGHMatrix<double> solutionJacobi = eq_system.solve_jacobi(20);

    std::cout << "A:" << std::endl << A_mat;
    std::cout << "y:" << std::endl << b_mat;
    std::cout << "Gauss:" << std::endl << solutionGauss;
    std::cout << "Jacobi:" << std::endl << solutionJacobi;

    ASSERT_TRUE (solutionGauss.almost_eq(solutionJacobi));
}

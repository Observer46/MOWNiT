#include <gtest/gtest.h>

#include <iostream>
#include <iomanip>
#include <string>

///////////////////////////////////
// Zadanie 1 i 2 - aghMatrix.cpp (implementowane jako metody klasy AGHMatrix), zawiera tez eliminacje Gaussa (do liczenia wyznacznika)
// Zadanie 3 - luFactor.cpp
// Zadanie 4 - choleskyFactor.cpp
// Zadanie 5 i 6 - sole.cpp (klasa dotyczaca ukladow rownan - rozwiazywanie eliminacja Gaussa i metoda Jacobiego)
// Wszystkie testy implementowanych funkcji znajduja sie w pliku matrixTests.cpp
///////////////////////////////////
int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
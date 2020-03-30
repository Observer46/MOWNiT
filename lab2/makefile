# Makefile
CCPP = g++ -Wall -std=c++17

main: main.cpp aghMatrix.cpp luFactor.cpp sole.cpp matrixTests.cpp
	$(CCPP)  main.cpp matrixTests.cpp -o main -lgtest -lpthread

clean:
	rm -f main
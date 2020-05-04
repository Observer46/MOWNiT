# Makefile
CCPP = g++ -Wall -std=c++17

main: main.cpp jacobi.cpp gaussseidel.cpp sor.cpp aghMatrix.cpp testSOLEs.cpp
	$(CCPP)  main.cpp -o main

clean:
	rm -f main
	rm -f f1*.txt newton_* f2*.txt
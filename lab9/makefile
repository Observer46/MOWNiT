# Makefile
CCPP = g++ -Wall -std=c++17

main: main.cpp odesolver.h eulerMethod.cpp backwardEulerMethod.cpp RK2Method.cpp RK4Method.cpp
	$(CCPP)  main.cpp eulerMethod.cpp backwardEulerMethod.cpp RK2Method.cpp RK4Method.cpp -o main

clean:
	rm -f main
	rm -f ex4_exact.txt func_*.txt lorenz_*.txt
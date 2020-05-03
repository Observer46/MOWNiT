# Makefile
CCPP = g++ -Wall -std=c++17

main: main.cpp newton.cpp lagrange.cpp hermite.cpp
	$(CCPP)  main.cpp -o main

clean:
	rm -f main
	rm -f function_data.txt newton_* lagrange_* hermite_*
	rm -f *_err.txt
	rm -f *_best_fit_*
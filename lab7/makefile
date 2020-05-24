# Makefile
CCPP = g++ -Wall -std=c++17

test:
	make main
	mkdir output
	./main

main: main.cpp integrationInterface.h quadrature.h rectangleIntegration.cpp trapezoidIntegration.cpp simpsonIntegration.cpp monteCarlo.cpp
	$(CCPP)  main.cpp rectangleIntegration.cpp trapezoidIntegration.cpp simpsonIntegration.cpp monteCarlo.cpp -o main

clean:
	rm -f main
	rm -fdR output
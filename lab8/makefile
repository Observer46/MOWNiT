# Makefile
CCPP = g++ -Wall -std=c++17

test:
	make main
	./main

main: main.cpp DFT.cpp FFT.cpp
	$(CCPP)  main.cpp DFT.cpp FFT.cpp -o main -lfftw3 -lm

clean:
	rm -f main
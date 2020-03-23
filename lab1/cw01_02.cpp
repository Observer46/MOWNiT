#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <chrono>

float iterativeSumming(std::vector<float> &tab, int from, int to){
	float sum = 0.0f;
	for(int i=from; i < to; i++)
	{
		sum += tab[i];
	}
	return sum;
}


float recursiveSumming(std::vector<float> &tab, int from, int to){
	if (from < to)
	{
		int mid = (from + to)/2;
		return recursiveSumming(tab,from, mid) + recursiveSumming(tab, mid+1, to);
	}
	return tab[from];
}

float kahanSumming(std::vector<float> &input, int from, int to){	// Dzieki takiemu naglowkowi mozemy to podac do 
																	// funkcji calculationTime by zmierzyc czas dzialania
	float sum = 0.0f;
	float err = 0.0f;

	for (int i=from; i < to; i++)
	{
		float y = input[i] - err;
		float temp = sum + y;
		err = (temp - sum) - y;
		sum = temp;
	}

	return sum;
}

// Porowania czasowe
double calculationTime(float summingFunction(std::vector<float>&, int, int), std::vector<float> &tab){
	auto start = std::chrono::high_resolution_clock::now();
	int size = (int) tab.size();
	summingFunction(tab, 0, size - 1);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	return elapsed.count();
}

void printAvgCalcTime(std::vector<float> &tab){
	double totalIterTime = 0.0;
	double totalRecurTime = 0.0;
	double totalKahanTime = 0.0;

	for(int i=0; i < 20; i++){
		totalIterTime += calculationTime(iterativeSumming, tab);
		totalRecurTime += calculationTime(recursiveSumming, tab);
		totalKahanTime += calculationTime(kahanSumming, tab);
	}

	double avgIterTime = totalIterTime / 20;
	double avgRecurTime = totalRecurTime / 20;
	double avgKahanTime = totalKahanTime / 20;

	std::cout << std::endl;
	std::cout << "\t Srednie czasy 20 wykonan operacji sumowania:" << std::endl;
	std::cout << "Sredni czas iteracyjnego sumowania: " << avgIterTime << std::endl;
	std::cout << "Sredni czas rekurencyjnego sumowania: " << avgRecurTime << std::endl;
	std::cout << "Sredni czas sumowania algorytmem Kahana: " << avgKahanTime << std::endl;
}





int main(){
	// Inicjalizacja zadania
	int N = 10000000;
	const float smallNumber = 0.4183f;
	std::cout << std::setprecision(10);
	std::vector<float> tab;


	for(int i=0; i<N; i++)
	{
		tab.push_back(smallNumber);
	}

	
	float iterSum = iterativeSumming(tab,0, N-1);
	float expectedResult = smallNumber*N;

	float err = abs(expectedResult - iterSum);
	float relativeErr = abs(err/expectedResult);
	std::cout << "\t Sumowanie iteracyjne:\n";
	std::cout << "Oczekiwane: " << expectedResult << ", wynik sumowania iteracyjnego: " << iterSum << std::endl;
	std::cout << "Blad bezwzgledny: " << err << std::endl;	
	std::cout << "Blad wzgledny: " << relativeErr << std::endl;
	


	// Zapis pomiarow bledu do pliku
	std::vector<float> relativeErrors;	
	std::ofstream outputFile;
	outputFile.open("relativeErrors.txt");
	iterSum = 0.0f;

	for(int i=0; i < N; i++){
		iterSum += tab[i];
		if(i % 25000 == 0){
			float relErr = abs( (iterSum - smallNumber*i)/(smallNumber*i) );
			outputFile<<i<<" "<<relErr<<"\n";
		}
	}
	outputFile.close();

	// Wyniki rekurencyjnego sumowania
	float recursiveSum = recursiveSumming(tab,0, N-1);
	float recursiveErr = abs(expectedResult - recursiveSum);
	float recursiveRelErr = abs(recursiveErr/expectedResult);
	std::cout<<"\nWynik sumowania rekurencyjnego: "<<recursiveSum<<", blad bezwzgledny: "<< recursiveErr<<", blad wzgledny: "<<recursiveRelErr<<std::endl;

	// Wyniki sumowania algorytmem Kahana
	float kahanSum = kahanSumming(tab, 0, N-1);
	float kahanErr = abs(expectedResult - kahanSum);
	float kahanRelErr = abs(kahanErr/expectedResult);
	std::cout<<"\nWynik sumowania algorytmem Kahana: "<<kahanSum<<", blad bezwzgledny: "<< kahanErr<<", blad wzgledny: "<<kahanRelErr<<std::endl;

	printAvgCalcTime(tab);

	return 0;
}

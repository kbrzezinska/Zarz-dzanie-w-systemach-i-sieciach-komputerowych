#pragma once

#include <iostream>
#include <string>
#include<fstream>
#include <algorithm>
#include <vector>
#include <stdlib.h> 
#include <ctime>
#include "timer.h"


using std::string;
using std::cout;
using std::endl;
using std::vector;
class K
{
private:
	Timer t;
	int N = 0,  weight = 0;
	int best_w = 999999;
	vector<int>v ;
	vector<vector<int>> k;
	vector<int>h;
	vector<vector<int>> matrix;
	vector<vector<int>> dp;
	int dynamic(int poz, int visited, int j);//liczy alg prog dynamic 

public:
	double timeBF = 0, timeD = 0;
	void pobierz(string s);
	void display();
	void brute_force();	
	void checkFunction(int weight, int visited, int pos, int index);
	void d();//wyswietla wynik dynamic()
	void gen(int n);//gen maciez
};
void K::gen(int n)
{

	N = n;
	matrix = vector<vector<int>>(N, vector<int>(N));
	
	v.erase(v.begin(),v.end());
	h.erase(h.begin(), h.end());
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j){ matrix[i][j] = - 1; }
			else{ matrix[i][j] = 1 + rand() % 40; }
		}
	}

	for (int i = 1; i < N; i++)
	{
		v.push_back(i); //do bb
	}

	dp = vector<vector<int>>(matrix.size());//do dynamic
	k = vector<vector<int>>(matrix.size());//dynamic
	for (auto& neighbors : dp)
		neighbors = vector<int>((1 << matrix.size()) - 1, INT_MAX);
	for (auto& neighbors : k)
		neighbors = vector<int>((1 << matrix.size()) - 1, NULL);
}
void K::pobierz(string s)
{
	v.erase(v.begin(), v.end());
	h.erase(h.begin(), h.end());
	std::ifstream plik;
	plik.open(s.c_str());
	plik >> this->N;
	matrix = vector<vector<int>>(N, vector<int>(N));
	
	for (int i = 0; i < N && !plik.eof(); i++)
	{
		for (int j = 0; j < N && !plik.eof(); j++){

			plik >> matrix[i][j];
		}

	}
	plik.close(); cout << "close" << endl;


	for (int i = 1; i < N; i++)
	{
		v.push_back(i); //do bb
	}

	dp = vector<vector<int>>(matrix.size());//do dynamic
	k = vector<vector<int>>(matrix.size());//dynamic
	for (auto& neighbors : dp)
		neighbors = vector<int>((1 << matrix.size()) - 1, INT_MAX);
	for (auto& neighbors : k)
		neighbors = vector<int>((1 << matrix.size()) - 1, NULL);
}

void K::display(){

	for (int i = 0; i < N ; i++)
	{
		std::cout << "\t";
		for (int j = 0; j < N ; j++){

			if (-1 < matrix[i][j] && matrix[i][j] < 10){ cout << " "; }
			std::cout<< matrix[i][j]<<" ";

		}
		std::cout << std::endl;
	}
	
}

void K::brute_force()
{
	best_w = 9999999;
	t.start = t.startTimer();
	int iter = 0;
	cout << "load";
	do{
		weight = 0;
		iter++;
		for (int i = 0; i < N-1;i++)
		{
			
			
			if (i == 0){ weight += matrix[0][v[0]]; }
			else 
			{
				
				weight += matrix[v[i - 1]][v[i]]; 
				
			}
		}
	
		weight += matrix[v[N - 2]][0]; 
		if (best_w > weight){ best_w = weight; h = v; }
		
	} while (std::next_permutation(v.begin(),v.end()));

	t.end = t.endTimer();
	timeBF = t.end.QuadPart - t.start.QuadPart;
	cout << "\b\b\b\b";

	cout << 0<< "-> ";
	while (!h.empty())
	{
		int y = h.front(); h.erase(h.begin());
		cout << y << "-> ";
	}
	cout << 0;
	cout << endl << "waga: " << best_w << endl;
	cout << endl << "iteracja: " << iter-1<< endl;
}



//wyglad watku
int K:: dynamic(int pos,int visited,int j)
{

	//zmienne globalne
	int matrixSize = 10;
	int numberOfThread = 3;

	if (visited == ((1 << matrix.size()) - 1))
		return matrix[pos][0]; 

	if (dp[pos][visited] != INT_MAX)
		return dp[pos][visited];

	for(int i = j*matrixSize/numberOfThread; i < (j+1)*matrixSize/numberOfThread; i++)
	{
		// can't visit ourselves unless we're ending & skip if already visited
		if (i == pos || (visited & (1 << i)))//AND !=0  isc glebiej
			continue;
		int weight = matrix[pos][i] + dynamic(i, visited | (1 << i),j);
		checkFunction(weight, visited, pos,i);
	}
	

	return dp[pos][visited];
}

//mutex function
void K::checkFunction(int weight, int visited, int pos, int i){
	//mutex unlock
	if (weight < dp[pos][visited]) {
		dp[pos][visited] = weight;
		k[pos][visited] = i;
	}
}

void K::d(){
	t.start = t.startTimer();
	cout << "waga: " << dynamic(0, 1) << endl;
	t.end = t.endTimer();
	timeD = t.end.QuadPart - t.start.QuadPart;
	cout <<0<<"->"<< k[0][1]<<"->";
	int p = k[k[0][1]][(1 |( 1 << k[0][1]))];
	int q = (1 | (1 << k[0][1]));
	
	for (int i = 0; i < N-3; i++)//poprzedniki i nastepniki
	{
		cout << p << "->";
		q = (q | (1 << p));
		
		p = k[p][(q |( 1 << p))];
	
	}cout <<p<<"->"<< 0 << endl;
	
}

		

#pragma once

#include <iostream>
#include <string>
#include<fstream>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <stdlib.h> 
#include <ctime>
#include "timer.h"
#include <mutex>

using std::string;
using std::cout;
using std::endl;
using std::vector;


std::mutex mutex; 
class K
{
public:
	Timer t;
	int N = 0,  weight = 0;
	int best_w = 999999;
	vector<int>v ;
	int threads=3;
	//int** k;
	vector<int>h;
	vector<vector<int>> matrix;
	//int** dp;
	vector<vector<int>> dp;
	vector<vector<int>> k;
	int dynamic(int poz, long long visited, int id, int *weightt);//liczy alg prog dynamic 
	int download(std::string FILE_IN);

	//int reduce(int k);//redukuje macierz bb
	//void  edge(int ii, int jj);
	//std::pair<int, int>pair;//wiersz,kolumna
	//vector<std::pair<int, int>>road;
public:
	double timeBF = 0, timeD = 0;
	void pobierz(string s);
	void display();
	void brute_force();	
	//int best_w = 999999;
	void d();//wyswietla wynik dynamic()

};

void K::pobierz(string s)
{
	v.erase(v.begin(), v.end());
	h.erase(h.begin(), h.end());
	std::ifstream plik;
	plik.open(s.c_str());
	plik >> this->N;
	//matrix = new int *[N];
	matrix = vector<vector<int>>(N, vector<int>(N));
	//kk = new int[ N];
	
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
	long long ss = pow(2, matrix.size()) - 1;//22

	dp = vector<vector<int>>(matrix.size());//do dynamic
	k = vector<vector<int>>(matrix.size());//dynamic
	for (auto& neighbors : dp)
		neighbors = vector<int>(ss, INT_MAX);
	for (auto& neighbors : k)
		neighbors = vector<int>(ss, NULL);


/*	dp = new int*[(matrix.size())];//do dynamic
	k = new int*[(matrix.size())];//dynamic

	long long ss = pow(2, matrix.size()) - 1;
	cout << ss << endl;
	for (int i = 0; i <1; i++)
	{
		dp[i] = new int [5];
		k[i] = new int[5];

		for (long long j = 0; j <(long long)(pow(2, matrix.size() )- 1); j++)
		{
			dp[i][j] = INT_MAX;
			k[i][j] = NULL;
		}
	}*/
	
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



int K:: dynamic(int pos,long long visited,int id,int *waga)
{
	
	if (visited == (long long)(pow(2,matrix.size()) - 1))//ostatnie
		return matrix[pos][0]; 

	


	mutex.lock();
	if (dp[pos][visited] != INT_MAX && *waga!=0)////////////////////////Bl¹d ,wywala sie na tej linijce
	{
		


		mutex.unlock();
		
		return dp[pos][visited];
	}
	mutex.unlock();
	

	
	

	for (int i = 0; i < matrix.size(); ++i)
	{
		// can't visit ourselves unless we're ending & skip if already visited
		if (i == pos || (long long)(visited & (long long)(pow(2, i))))
			continue;

		

		if (pos == 0 && i == (1 + ((int)(matrix.size() - 1) / threads)*id) && id!=threads) {
			
			//cout <<"id: "<< id << "- stop" << (1 + ((int)(matrix.size() - 1) / threads)*id) << endl;
			 return 0;
		} 
		if (pos == 0 && i < (((int)(matrix.size() - 1) / threads) * (id - 1)) + 1 && id!=threads)

		{
			//cout << "id: " << id << "- start" << (((int)(matrix.size() - 1) / threads) * (id - 1)) + 1 << endl;

			continue; //start
		}

		*waga = matrix[pos][i] + dynamic(i, (visited + pow(2, i)),id,waga);//OR

		//Sleep(1);

		
		
		mutex.lock();
		if (*waga < dp[pos][visited]){
			
			//mutex.lock();

			dp[pos][visited] = *waga;
			k[pos][visited] = i;

			
			//mutex.unlock();
			
		}
		mutex.unlock();
		
	}
	
	return dp[pos][visited];
}


void K::d(){
	t.start = t.startTimer();
	//cout << "waga: " << dynamic(0, 1) << endl;
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



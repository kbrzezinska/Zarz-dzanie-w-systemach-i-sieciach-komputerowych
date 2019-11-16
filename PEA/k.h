#pragma once

#include <iostream>
#include <string>
#include<fstream>
#include <algorithm>
#include <vector>
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
	vector<vector<int>> k;
	vector<int>h;
	vector<vector<int>> matrix;
	vector<vector<int>> dp;
	int dynamic(int poz, int visited, int id, int *weightt);//liczy alg prog dynamic 
	

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
	//void bb();//bound and branch
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

int K:: dynamic(int pos,int visited,int id,int *waga)
{
	
	if (visited == ((1 << matrix.size()) - 1))//ostatnie
		return matrix[pos][0]; 
	

	std::unique_lock<std::mutex> guard(mutex);
	if (dp[pos][visited] != INT_MAX && *waga!=0)//bylo
	{
		

		guard.unlock();
		
		return dp[pos][visited];
	}
	guard.unlock();

	

	for (int i = 0; i < matrix.size(); ++i)
	{
		// can't visit ourselves unless we're ending & skip if already visited
		if (i == pos || (visited & (1 << i)))//AND !=0  isc glebiej
			continue;
		if (pos == 0 && i == matrix.size()/threads+id) return 0;
		if (pos == 0 && i < id) continue;
		
		
		*waga = matrix[pos][i] + dynamic(i, visited | (1 << i),id,waga);//OR

		std::unique_lock<std::mutex> lck(mutex);

		if (*waga < dp[pos][visited]){
			dp[pos][visited] = *waga;
		//	kk[pos] = i;
			k[pos][visited] = i;
			
		}
		lck.unlock();
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



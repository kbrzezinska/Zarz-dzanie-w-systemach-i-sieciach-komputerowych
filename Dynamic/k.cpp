#include "stdafx.h"
#include <iostream>
#include <string>
#include<fstream>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <stdlib.h> 
#include <ctime>
#include "k.h"
#include <mutex>
#include <thread>

using std::string;
using std::cout;
using std::endl;
using std::vector;


std::mutex mutex;

int K::dynamic(int pos, long long visited, int id, int *waga)
{

	if (threads > matrix.size() - 1)threads = matrix.size() - 1;
	if (id > matrix.size() - 1)return 0;
	
	if (visited == (long long)(pow(2, matrix.size()) - 1))//ostatnie
		return matrix[pos][0];




	//mutex.lock();
	if (dp[pos][visited] != INT_MAX )////////////////////////Bl¹d ,wywala sie na tej linijce
	{



	//	mutex.unlock();

		return dp[pos][visited];
	}
	//mutex.unlock();



	

	for (int i = 0; i < matrix.size(); ++i)
	{
		// can't visit ourselves unless we're ending & skip if already visited
		if (i == pos || (long long)(visited & (long long)(pow(2, i))))
			continue;



		if (pos == 0 && i == (1 + ((int)(matrix.size() - 1) / threads)*id) && id != threads) {

			//cout <<"id: "<< id << "- stop" << (1 + ((int)(matrix.size() - 1) / threads)*id) << endl;
			return 0;
		}
		if (pos == 0 && i < (((int)(matrix.size() - 1) / threads) * (id - 1)) + 1 )

		{
			//cout << "id: " << id << "- start" << (((int)(matrix.size() - 1) / threads) * (id - 1)) + 1 << endl;

			continue; //start
		}

		*waga = matrix[pos][i] + dynamic(i, (visited + pow(2, i)), id, waga);//OR

		//Sleep(1);



		//mutex.lock();
		if (*waga < dp[pos][visited]){

			//mutex.lock();

			dp[pos][visited] = *waga;
			k[pos][visited] = i;


			//mutex.unlock();

		}
		//mutex.unlock();

	}

	return dp[pos][visited];
}


void K::d(){
	//cout << "waga: " << dynamic(0, 1) << endl;
	
	cout << 0 << "->" << k[0][1] << "->";
	int p = k[k[0][1]][(1 | (1 << k[0][1]))];
	int q = (1 | (1 << k[0][1]));

	for (int i = 0; i < N - 3; i++)//poprzedniki i nastepniki
	{
		cout << p << "->";
		q = (q | (1 << p));

		p = k[p][(q | (1 << p))];

	}cout << p << "->" << 0 << endl;

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

	v = vector<vector<int>>(N-1, vector<int>(N-1));
	for (int j = 0; j < N-1; j++)
	{
		v[j][0] = j + 1;
		for (int i = 1, k = 1; i < N - 1; i++,k++) ///////////////////////spr
		{
			if (j+1==i)k++;
			v[j][i]=k; //do bf
		}
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
int bf(vector<vector<int>>matrix, vector<int>v,int N)
{
	int best_w = INT_MAX;
	do{
		int weight = 0;
		
		for (int i = 0; i < N - 1; i++)
		{


			if (i == 0){ weight += matrix[0][v[0]]; }
			else
			{

				weight += matrix[v[i - 1]][v[i]];

			}
		}

		weight += matrix[v[N - 2]][0];
		if (best_w > weight){ best_w = weight;  }

	} while (std::next_permutation(v.begin()+1, v.end()));
	cout <<"bbb = "<< best_w << endl;
	return best_w;
}

void K::brute_force()
{
	best_w = 9999999;
	
	int iter = 0;
	cout << "load";
		//for (int i = 0; i < 1; i++)
		//{

			std::thread t(bf, matrix, v[0], N);
			t.join();
		//}

		

	

	/*cout << 0 << "-> ";
	while (!h.empty())
	{
		int y = h.front(); h.erase(h.begin());
		cout << y << "-> ";
	}*/
	cout << 0;
	cout << endl << "waga: " << best_w << endl;
	cout << endl << "iteracja: " << iter - 1 << endl;
}

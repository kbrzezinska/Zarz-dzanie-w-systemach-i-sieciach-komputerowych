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
	int dynamic(int poz, int visited);//liczy alg prog dynamic 


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

int K:: dynamic(int pos,int visited)
{
	

	if (visited == ((1 << matrix.size()) - 1))//ostatnie
		return matrix[pos][0]; 

	if (dp[pos][visited] != INT_MAX)//bylo
		return dp[pos][visited];

	for (int i = 0; i < matrix.size(); ++i)
	{
		// can't visit ourselves unless we're ending & skip if already visited
		if (i == pos || (visited & (1 << i)))//AND !=0  isc glebiej
			continue;
		
		
		weight = matrix[pos][i] + dynamic(i, visited | (1 << i));//OR
	
		if (weight < dp[pos][visited]){
			dp[pos][visited] = weight;
		//	kk[pos] = i;
			k[pos][visited] = i;
			
		}
	}
	
	return dp[pos][visited];
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


/*
int K::reduce(int k)
{
	int min, cost = 0; int ii, jj;
	for (int i = 0; i < N; i++)
	{
		min = INT_MAX;
		for (int j = 0; j < N; j++)
		{
			if (j != i && matrix[i][j] != -1)
			{
				if (min > matrix[i][j]){ min = matrix[i][j]; ii = i; jj = j; }
				//min = fmin(min, matrix[i][j]);//najniejsza wartosc w wierszu
			}
			if(j==i){ matrix[i][j] = -1; }//przekatna=inf
		}
		if ( min!=INT_MAX){
			for (int j = 0; j < N; j++)
			{
				if (j != i && matrix[i][j] != -1)
				{
					matrix[i][j] = matrix[i][j] - min;//redukcja wierszy
					if (k == N - 2 && min != 0 ){
						pair.first = ii; pair.second = jj;
						road.push_back(pair); cout << ii << "" << jj << endl;
					}
				}
			}cost += min;
		}
		
	}
	
	
	for (int i = 0; i < N; i++)
	{
		min = INT_MAX;
		for (int j = 0; j < N; j++)
		{
			if (i != j && matrix[j][i] != -1)
			{
				if (min > matrix[j][i]){ min = matrix[j][i]; ii = j; jj = i; }
				//min = fmin(min, matrix[j][i]);//najmniejsza wartoœc w kolumnie
			}

		}
		if ( min != INT_MAX)
		{		
			for (int j = 0; j < N; j++)
			{
				if (i != j && matrix[j][i]!=-1)
				{
					matrix[j][i] = matrix[j][i] - min;//redukcja kolumny
					if (k == N - 2 && min!=0){
						pair.first = ii; pair.second = jj;
						road.push_back(pair); cout << ii << "" << jj << endl;
					}
				}
			}cost += min;
		}
		
	}
	return cost;
}
void K:: edge(int ii, int jj)
{
	
	for (int i = 0; i < N; i++)
	{
		matrix[ii][i] = -1;
		matrix[i][jj] = -1;
	
	}
	
}
void K::bb()
{
	std::pair<int, int>p;//wiersz,kolumna
	vector<std::pair<int, int>>r; 
	vector<vector<int>>m(N, vector<int>(N));
	m = matrix;//zapamietujemy macierz wag
	int granica = 0;
	// cost = matrix;
	vector<int>t(N);
	int y, yw, yk, wk, xw, xk, x, iw, ik, jw, jk;;
	for (int k = 0; k < N -1; k++){

		granica += reduce(k);// display();
		int maxw = 0, maxk = 0, max = 0;

		for (int i = 0; i < N; i++)
		{
			int minw = INT_MAX, mink = INT_MAX;
			for (int j = 0; j < N; j++)
			{
				if (matrix[i][j]>0)
				{
					if (minw > matrix[i][j]){ minw = matrix[i][j];  yw = i; xw = j; }//najmniejszy element w weirsz
				}

				if (matrix[j][i]>0)
				{
					if (mink > matrix[j][i]){
						mink = matrix[j][i];  yk = j; xk = i;
						//cout  << "yk" << yk << " xk" << xk << endl; 
					}//najmniejszy element w weirsz
				}



			}
			if (maxw < minw  &&  minw != INT_MAX){ maxw = minw; jw = xw, iw = yw; }
			if (maxk < mink  &&  mink != INT_MAX){ maxk = mink; ik = yk, jk = xk; }
		}
		// cout << "max:" << max << "x"<<x<<"y"<<y<<endl;; 
		
			
			
				if (k>1)
				{
					cout << "kkkk" << endl;
					cout << "kss: " << r.size() << endl;
					r = road;
					int t = r[r.size()-1 ].first, tt = r[r.size() -1].second;
					while (!r.empty())
					{
						cout << r.front().first << " " << r.front().second << endl;
						r.erase(r.begin());
					}r = road;
					
					r.pop_back();

						
						
						while (!r.empty())
						{

							if (t == r.front().second){ matrix[tt][r.front().first] = -1; break; }//2132
							
							if (tt == r.front().first){ matrix[r.front().second][t] = -1; break; }

							 r.erase(r.begin());  
							
					}
						
				}
			

		

		if (maxw >= maxk)
		{
			cout << "maxw:" << maxw << endl;
			max = maxw; y = iw; x = jw;
			for (int i = 0; i < N; i++)
			{
				if (matrix[y][i] == 0)
				{
					edge(y, i); //cout << "i:" << i << "j:" << y << endl;
					pair.first = y; pair.second = i;
					road.push_back(pair);
					matrix[i][y] = -1; break;//macierz nieskrócona
				}
			}
		}
		if(maxk>maxw){
			cout << "maxk:" << maxk << endl;
			max = maxk; y = ik; x = jk;

			for (int i = 0; i < N; i++)
			{
				if (matrix[i][x] == 0)
				{
					edge(i, x); //cout << "i:" << i << "j:" << y << endl;
					pair.first = i; pair.second = x;
					road.push_back(pair);
					matrix[x][i] = -1; break;//macierz nieskrócona
				}
			}
		}
		granica += max;

		cout << "max:" << max << "x" << x << "y" << y << endl;;
		cout << "r:" << road.size() << endl;
		r = road;
	}
	best_w = 0; matrix = m;
	while (!road.empty())
	{
		int  r = road.front().first;
		int rr = road.front().second;
		road.erase(road.begin());
		t[r] = rr;
		best_w += matrix[r][rr];
		cout << r << " " << rr << " " << matrix[r][rr] << endl;
	}
	int j = 0; cout << j;
	for(int i = 0; i < N;i++ )
	{
		cout << "->" << t[j] ;
		j = t[j];
	}
	cout << endl;
	 display();
	 cout <<endl<< granica << endl;
	 cout << "waga "<< best_w << endl;
}*/
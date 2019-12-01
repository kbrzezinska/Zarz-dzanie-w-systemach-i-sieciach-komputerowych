#pragma once

#include <iostream>
#include <string>
#include<fstream>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <stdlib.h> 
#include <ctime>

#include <mutex>

using std::string;
using std::cout;
using std::endl;
using std::vector;


class K
{
public:
	int N = 0, weight = 0;
	int best_w = 999999;
	vector<vector<int>> v;
	int threads = 3;
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





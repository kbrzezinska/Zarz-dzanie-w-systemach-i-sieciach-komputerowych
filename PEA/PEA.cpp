// PEA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "k.h"
#include "menu.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
//#include<fstream>
#define Threads 8	//2-8 dzia³a,10 -nie
std::mutex print;

class Pr{
public: 
	int  *weight;
	int id;
	K *k;
	Pr( K *k, int id){  this->k = k; this->id = id; }
	void operator()(){ 
	
	//	cout << id << endl;
		
		int waga = 0;
		weight =&waga;
		k->dynamic(0,1,id,weight); 
		//print.lock();
		// cout <<"id: "<<id<<" waga: "<< *weight << endl;
		// print.unlock();
	
	
	
	
	
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	K *k = new K(); 
	k->threads = Threads;
	k->pobierz("tsp_17.txt");
	//k->display();
	
	cout << "size dp" << k->dp.size()<< endl;
	
	cout << "visited all " <<  (long long)(pow(2,k->matrix.size())-1 )<< endl;
	
	cout << k->dp[0].size() << endl;

	cout << "threads: " << Threads << endl;
	srand(time(0));
	vector<std::thread> threads;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	
	
	start = std::chrono::system_clock::now();
	for (int i = 0; i < Threads; i++)
	{
		Pr p(k, i+1);
		threads.push_back( std::thread(p));
	}
	for (int i = 0; i < Threads; i++)
	{
		
		threads[i].join();
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	//cout << k->weight<< endl;
	k->d();
	cout << "time: " << elapsed_seconds.count()<<" s"<< endl;

	
	
	//Menu m=Menu();





	/*
	string s = "wyniki.txt";
	std::ofstream plik(s.c_str());
	for (int i = 0; i < 1; i++)
	{
		k.gen(20); cout << endl;
		k.display();
		k.d();
		//plik << k.timeBF << endl;;
	}

	plik.close();
	*/
	return 0;
}


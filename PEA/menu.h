#pragma once
#include <iostream>
#include "k.h"
using std::cout;
using std::endl;

class Menu{

private:
	K k;
	void alg()
	{
		cout << "wybierz" << endl;
		cout << "1-brute force" << endl;
		cout << "2-prog dynamiczne" << endl;
		int i; std::cin >> i; cout << endl;
		switch (i)
		{
		case 1:
			k.brute_force();
			break;
		case 2:
			k.d();
			break;
		default:
			break;
		}
	}
	void pobierz(){
		cout << "wybierz" << endl;
		cout << "1-tsp_6_1.txt" << endl;
		cout << "2-tsp_6_2.txt" << endl;
		cout << "3-tsp_10.txt" << endl;
		cout << "4-tsp_12.txt" << endl;
		cout << "5-tsp_13.txt" << endl;
		cout << "6-tsp_14.txt" << endl;
		cout << "7-tsp_15.txt" << endl;
		cout << "8-tsp_17.txt" << endl;

		int i;
		std::cin >> i;
		k = K(); cout << endl;
		switch (i)
		{
		case 1:
			k.pobierz("tsp_6_1.txt");
			break;

		case 2:
			k.pobierz("tsp.txt");
			break;
		case 3:
			k.pobierz("tsp_10.txt");
			break;
		case 4:
			k.pobierz("tsp_12.txt");
			break;
		case 5:
			k.pobierz("tsp_13.txt");
			break;
		case 6:
			k.pobierz("tsp_14.txt");
			break;
		case 7:
			k.pobierz("tsp_15.txt");
			break;
		case 8:
			k.pobierz("tsp_17.txt");
			break;
		

		default:
			break;
		}
		
	}
	
public:Menu(){
	int u = 0;
	while (u < 4){
		cout << "wybierz" << endl;
		if (u != 3)	{
			if (u == 0){ cout << "1-pobierz" << endl; }
			cout << "2-wyœwietl" << endl;
		}
		cout << "3-algorytm" << endl;
		int i;
		std::cin >> i;
		cout << endl;
		if (u == 0 && i != 1){ cout << "najpierw musisz pobrac" << endl;  continue; }
		switch (i)
		{
			if (u != 3){
				if (u == 0){
		case 1:
			pobierz();
			break;
				}
				if (u == 0)
	case 2:
			k.display();
			break;
			}
		case 3:
			alg();
			break;

		default:
			break;
		}
		u++;
	}
}
};
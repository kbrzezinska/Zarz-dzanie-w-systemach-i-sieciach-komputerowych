// PEA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "k.h"
#include "menu.h"
#include <iostream>
#include <stdio.h>
//#include<fstream>




int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(0));
	
	K k = K(); 
	
	Menu m=Menu();
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


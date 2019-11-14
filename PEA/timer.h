#pragma once
#include <iostream>
#include <windows.h>
class Timer{

public:
	

	LARGE_INTEGER startTimer()
	{
		LARGE_INTEGER start;
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&start);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		return
			start;
	}
	LARGE_INTEGER endTimer()
	{
		LARGE_INTEGER stop;
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
		QueryPerformanceCounter(&stop);
		SetThreadAffinityMask(GetCurrentThread(), oldmask);
		return
			stop;
	}
	LARGE_INTEGER start, end;

};
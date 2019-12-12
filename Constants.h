#pragma once
#include "mpi.h"
#include <iostream>
using namespace std;
class Constants
{
private:
	
public:	
	static const int COLORS = 8 ;
	static const int SPOTS = 8;
	static const int ErrorBit = SPOTS + 1;
	//static  int COLORS = 2;
	//static  int SPOTS = 2;
	//static void GetColors();
	//static void GetSpots();
	static int TotalNodes();
	static int ChallengerNodes();
};


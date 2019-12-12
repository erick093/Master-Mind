#pragma once
#pragma once
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <random>
#include "Challenger.h"
using namespace std;
class Operations
{
private:
	


public:
	int* GenerateKey(int colors, int spots);
	static void PrintArray(int* array, int size, string message);
	static int GetID();
	static bool Winner(int* evaluation, int ID);

};


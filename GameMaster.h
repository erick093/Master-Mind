#pragma once
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>
#include<vector>
using namespace std;
class GameMaster
{
private:
	int ID;
	vector<int> key;
	void GetKey();
	void PrintKey(std::vector<int> const& input);
public:
	 GameMaster(int ID);
};


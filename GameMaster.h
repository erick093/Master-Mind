#pragma once
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>
#include<vector>
#include "mpi.h"
using namespace std;
class GameMaster
{
private:
	int ID;
	vector<int> key;
	//const vector<int> key = {2,1,1};
	void GetKey();
	void PrintKey(std::vector<int> const& input);
	void PrintEvaluation(int *evaluation);
public:
	 GameMaster(int ID);
	 int* ReceiveData(void* send_data, MPI_Datatype receive_datatype, MPI_Comm communicator);
	 int* RandomChoice(int* data, MPI_Datatype datatype);
	 int* EvaluateChoice(int* data);
};


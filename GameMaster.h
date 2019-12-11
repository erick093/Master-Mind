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
	
	//const vector<int> key = {2,1,1};
	void GetKey();
	vector<int> key;
	void PrintEvaluation(int *evaluation);
	void CheckIDLE(int* data);
public:
	
	 GameMaster(int ID);
	 int* ReceiveData(void* send_data, MPI_Datatype receive_datatype, MPI_Comm communicator);
	 int* RandomChoice(int* data, MPI_Datatype datatype);
	 int* EvaluateChoice(int* data);
	 //void PrintKey(std::vector<int> const& input);
	 void PrintKey();
	 void SendEvaluation(int* send_data, MPI_Datatype send_datatype, MPI_Comm communicator);
	 
};


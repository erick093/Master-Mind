#pragma once
#include <vector>
#include "Constants.h"

class Challenger
{
private:

	int ID;
	void CombinationRecursive(vector<int> solution, int position);
	void WriteToFile();
	
public:	
	//static vector<int> current;
	//static vector<int> elements;
	Challenger(int ID);
	vector<vector<int>> combinations;
	void CreateSet();
	//int* PickRandomGuess();
	vector<int> PickRandomGuess();
	void PrintCombination();
	void SendData(void* send_data, MPI_Datatype send_datatype, MPI_Comm communicator);

};


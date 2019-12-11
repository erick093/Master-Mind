#pragma once
#include <vector>
#include "Constants.h"

class Challenger
{
private:

	int ID;
	void CombinationRecursive(vector<int> solution, int position);
	void WriteToFile();
	void WriteToFile_2();
	bool CheckGuess(vector<int> guess, int* evaluation);
	
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
	void ReceiveEvaluation(int* receive_data, MPI_Datatype datatype, MPI_Comm communicator);
	void FilterGuesses(int* evaluation);
	bool NotEmptyGuesses();
	void SendError(MPI_Comm communicator);

};


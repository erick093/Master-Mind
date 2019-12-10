#include "Challenger.h"
#include "Constants.h"
#include "Operations.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string> 
#include <ctime>
//vector<vector<int>> Challenger::combinations;

Challenger::Challenger(int ID)
{
	this->ID = ID;

	this->CreateSet();
	//this->PrintCombination();
	this->WriteToFile();
}


//void Challenger::CreateSet() {
//	static vector<int> elements;
//	vector<int> current(Constants::SPOTS, 0);
//	for (int i = 1; i <= Constants::COLORS; ++i) {
//		elements.push_back(i);
//	}
//
//	CombinationRecursive(Constants::SPOTS, 0, current, elements);
//}

//void Challenger::CombinationRecursive(int combinationLength, int position, vector<int>& current, vector<int>& elements) {
//
//	if (position >= combinationLength) {
//		Challenger::combinations.push_back(current);
//		return;
//	}
//
//	for (size_t j = 0; j < elements.size(); ++j) {
//		current[position] = elements[j];
//		Challenger::CombinationRecursive(combinationLength, position + 1, current, elements);
//	}
//	return;
//}
void Challenger::PrintCombination() {
	for (size_t i = 0; i < Challenger::combinations.size(); i++)
	{
		for (size_t j = 0; j < Challenger::combinations[i].size(); j++) std::cout << Challenger::combinations[i][j] << ' ';
		std::cout << std::endl;
	}
}

void Challenger::CreateSet()
{
	vector<int> vec_sol(Constants::SPOTS);
	int i;
	//int ID = Operations::GetID();
	int fixed_colors = floor(Constants::COLORS / (Constants::ChallengerNodes()));
	//cout << "solution number: " << solution_number << endl;
	i = fixed_colors;
	while (i>0)
	{
		vec_sol[0] = this->ID * fixed_colors - i;
		this->CombinationRecursive(vec_sol, 1);
		i--;
	}

	int  extra_colors = Constants::COLORS % (Constants::ChallengerNodes());

	if (extra_colors - this->ID >= 0 )
	{
		vec_sol[0] = Constants::COLORS - (extra_colors - this->ID) - 1;
		this->CombinationRecursive(vec_sol, 1);
	}
}
void Challenger::CombinationRecursive(vector<int> solution, int position)
{
	int i;

	for (i = 0; i < Constants::COLORS; i++)
	{
		solution[position] = i;
		
		if (position < Constants::SPOTS - 1)
		{
			this->CombinationRecursive(solution, position + 1);
		}
		else
		{
			this->combinations.push_back(solution);
		}
	}
}


void Challenger::SendData(void* send_data, MPI_Datatype send_datatype, MPI_Comm communicator)
{
	//int datatype_size;
	int* guess	 = (int*)send_data;

	//MPI_Type_size(datatype, &datatype_size);
	
	guess[Constants::ErrorBit] = 0; //Setting error bit to 0 
	int send_count = Constants::SPOTS + 1;
	int root = 0; //GameMaster ID
	MPI_Gather(guess, send_count, send_datatype, NULL, send_count,
		send_datatype, root, communicator);
}


void Challenger::WriteToFile()
{

	ID = this->ID;
	std::ofstream Out(std::to_string(ID) + "_Challenger.txt");
	//ostream_iterator<int> output_iterator(outFile, "\t");
	ostream_iterator<int> output_iterator(Out, "\t");
	for (int i = 0; i < this->combinations.size(); i++)
	{
		copy(this->combinations.at(i).begin(), this->combinations.at(i).end(), output_iterator);
		Out << '\n';
	}

	
}

vector<int>  Challenger::PickRandomGuess()
{
	srand(time(0));
	vector<int> RandomGuess = this->combinations[rand() % this->combinations.size()];



	return RandomGuess;
}

//int* Challenger::PickRandomGuess()
//{
//	srand(time(0));
//	vector<int> RandomGuess = this->combinations[rand() % this->combinations.size()];
//	static int RandomGuess_array[Constants::SPOTS];
//
//	int i;
//	cout << "Guess Choosen by Challenger_" << this->ID << " is: ";
//	for (i = 0; i < RandomGuess.size(); i++)
//	{
//		RandomGuess_array[i] = RandomGuess[i];
//		cout << RandomGuess_array[i];
//	}
//
//
//	return RandomGuess_array;
//}

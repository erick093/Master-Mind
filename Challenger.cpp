#include "Challenger.h"
#include "Constants.h"
#include "Operations.h"
#include <vector>
#include <fstream>
//vector<vector<int>> Challenger::combinations;

Challenger::Challenger(int ID)
{
	this->ID = ID;

	this->CreateSet();
	//this->PrintCombination();
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
	vector<int> solution(Constants::SPOTS);
	int i;

	int solution_number = floor(Constants::COLORS / (Constants::ChallengerNodes()));

	for (i = solution_number; i > 0; i--)
	{
		solution[0] = this->ID * solution_number - i;
		this->CombinationRecursive(solution, 1);
	}

	//if (this->IscomputingExtraSolutions())
	//{
	//	solution[0] = Constants::COLORS - (Constants::ExtraComputations() - this->ID) - 1;
	//	this->CombinationRecursive(solution, 1);
	//}
}
void Challenger::CombinationRecursive(vector<int> solution, int position)
{
	int i;

	for (i = 0; i < Constants::COLORS; i++)
	{
		int current_position = position - 1;
		bool is_existing_symbol = false;
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
#include "Challenger.h"
#include "Constants.h"
#include "Operations.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string> 
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
	vector<int> solution(Constants::SPOTS);
	int i;
	int ID = Operations::GetID();
	int solution_number = floor(Constants::COLORS / (Constants::ChallengerNodes()));
	cout << "solution number: " << solution_number << endl;

	for (i = solution_number; i > 0; i--)
	{
		solution[0] = this->ID * solution_number - i;
		this->CombinationRecursive(solution, 1);
		cout << "entering for loop ID: "<< ID <<endl;
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

void Challenger::WriteToFile()
{
	//ofstream file;
	//file.open((Operations::GetID() + ".txt").c_str());
	//file.open(Operations::GetID() + ".zip");
	//std::vector<std::string> v{ "one", "two", "three" };
	//std::ofstream outFile( Operations::GetID() + "_Challenger.txt");
	// the important part
	//for (const auto& e : this->combinations) outFile << e << "\n";
	ID = this->ID;
	std::ofstream Out(std::to_string(ID) + "Challenger.txt");
	//ostream_iterator<int> output_iterator(outFile, "\t");
	ostream_iterator<int> output_iterator(Out, "\t");
	for (int i = 0; i < this->combinations.size(); i++)
	{
		copy(this->combinations.at(i).begin(), this->combinations.at(i).end(), output_iterator);
		Out << '\n';
	}

	//for (const auto& vt : this->combinations) {
	//	std::copy(vt.cbegin(), vt.cend(),
	//		std::ostream_iterator<int>(std::cout, " "));
	//	std::cout << '\n';
	//}
	//vector< vector<int> >::iterator row_it = this->combinations.begin();
	//vector< vector<int> >::iterator row_end = this->combinations.end();
	//for (; row_it != row_end; ++row_it)
	//{

	//	vector<char>::iterator col_it = row_it->begin();
	//	vector<char>::iterator col_end = row_it->end();

	//	for (; col_it != col_end; ++col_it)
	//		Out << *col_it;
	//	Out << '\n';
	//}

	//Out.close();

	
}
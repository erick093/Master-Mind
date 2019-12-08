// Mastermind.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Operations.h"
#include "Constants.h"
#include "Challenger.h"
using namespace std;



int main(int argc, char* argv[])
{
	int id, nb_instance, len;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int numberofnodes;
	int *key;
	int ID;
	Operations *operations;
	operations = new Operations();
	Challenger *challenger;
	MPI_Init(&argc, &argv);

	ID = Operations::GetID();

	if ( ID == 0)
	{
		numberofnodes = Constants::TotalNodes();
		cout << "Total_nodes: " << numberofnodes << endl;
		cout << "Game_Master_ID: " << ID << endl;
		//Constants::GetColors();
		//Constants::GetSpots();
		//cout << "Spots_number: " << Constants::SPOTS << endl;
		//cout << "Colors_number: " << Constants::COLORS << endl;
		key = operations->GenerateKey(Constants::COLORS, Constants::SPOTS);
		//Operations::PrintArray(key, Constants::SPOTS, "key is: ");
		//Challenger::CreateSet();
		//Challenger::PrintCombination();
	}
	else if ( ID == 1)
	{
		cout << "Challenger_ID: " << ID << endl;
		challenger = new Challenger(ID);
		//challenger->CreateSet();
		challenger->PrintCombination();
	}
	else if (ID == 2){
		cout << "Challenger_ID: " << ID << endl;
		challenger = new Challenger(ID);
		//challenger->CreateSet();
		challenger->PrintCombination();
	}


	MPI_Finalize();
	//MPI_Init(&argc, &argv);
	//MPI_Comm_rank(MPI_COMM_WORLD, &id); 
	//MPI_Comm_size(MPI_COMM_WORLD, &nb_instance); 
	//MPI_Get_processor_name(processor_name, &len);
	//cout << "Hello world! I am " << id << " of " << nb_instance << " on " << processor_name <<endl;
	//numberofnodes = Constants::NumberOfNodes();
	//cout << "Number of Nodes is : " << numberofnodes << endl;
	//MPI_Finalize();

	 


    //std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

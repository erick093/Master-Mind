// Mastermind.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Operations.h"
#include "Constants.h"
#include "Challenger.h"
#include "GameMaster.h"
#include "mpi.h"
using namespace std;
bool Winner(int* evaluation,int ID)
{
	bool win = false;
	int number_of_perfects = evaluation[Constants::SPOTS];
	//cout << "number of perfects: " << number_of_perfects;
	//cout << "Spots" << Constants::SPOTS;
	if (number_of_perfects == Constants::SPOTS)
	{
		if (ID==0)
		{
			cout << "Challenger guessed the solution.";

		}
		win = true;
	}
	//cout << "Boolean: " << win;
	return win;
}


int main(int argc, char* argv[])
{
	MPI_Init(NULL, NULL);
	//int count = 10;
//	int id, nb_instance, len;
	//char processor_name[MPI_MAX_PROCESSOR_NAME];
	int numberofnodes;
	//int *key;
	int ID;
	Operations *operations;
	Challenger* challenger= NULL;
	GameMaster* gamemaster = NULL;
	operations = new Operations();
	int guesses_array[Constants::SPOTS];
	//int* guess;
	int *received_data, *choosen_guess;
	int* evaluated_guess{};
	evaluated_guess = (int*)malloc(sizeof(int) * (Constants::SPOTS + 2));
	ID = Operations::GetID();
	int count_perfects;
	
	//bool ready = false;
	//Verify if  Node is GameMaster or Challenger
	if (ID != 0)
	{
		cout << "Challenger_ID: " << ID << endl;
		challenger = new Challenger(ID);
	}
	else
	{
		
		gamemaster = new GameMaster(0);
	}
	do {

		//ready = false;
		if ( ID == 0)
		{

			numberofnodes = Constants::TotalNodes();
			//cout << "Total_nodes Playing: " << numberofnodes << endl;
			cout << "Game_Master_ID: " << ID << endl;
			gamemaster->PrintKey();
			received_data = gamemaster->ReceiveData(&guesses_array, MPI_INT, MPI_COMM_WORLD);
			choosen_guess = gamemaster->RandomChoice(received_data, MPI_INT);
			evaluated_guess = gamemaster->EvaluateChoice(choosen_guess);
			gamemaster->SendEvaluation(evaluated_guess, MPI_INT, MPI_COMM_WORLD);
			//ready = true;
			//free(evaluated_guess);

			//all_guesses = gamemaster->ReceiveData(&guesses_array, MPI_INT, MPI_COMM_WORLD);
			//for (int i = 0; i < sizeof(all_guesses); ++i) printf("%d ", all_guesses[i]);
			//size_t n = sizeof(all_guesses) / sizeof(all_guesses[0]);
			//size_t n = sizeof(all_guesses);
			//cout << "value of n: " << n <<endl;
			//// loop through the elements of the array
			//for (size_t i = 0; i < n; i++) {
			//	std::cout << all_guesses[i] << ' ';
			//}

			//gamemaster->ReceiveData(,MPI_INT,MPI_COMM_WORLD);
			/*testing part begin*/ 
		/*	key = operations->GenerateKey(Constants::COLORS, Constants::SPOTS);
			Operations::PrintArray(key, Constants::SPOTS, "key (2) is: ");*/
			/*testing part end*/

		}

		else
		{

			//int* received_temp{};
			vector<int> guess;
			if (challenger->NotEmptyGuesses()) 
			{
				guess = challenger->PickRandomGuess();
				unsigned int i;
				cout << "Guess Choosen by Challenger_" << ID << " is: ";
				for (i = 0; i < guess.size(); i++)
				{
					guesses_array[i] = guess[i];
					cout << guesses_array[i];
				}
				cout << endl;
				challenger->SendData(&guesses_array, MPI_INT, MPI_COMM_WORLD);
			
			
			}
			else {
				cout << "Sending Error "<<endl;
				challenger->SendError(MPI_COMM_WORLD);
			}
			//if (ready) {
				//cout << " Ready True!";
				challenger->ReceiveEvaluation(evaluated_guess, MPI_INT, MPI_COMM_WORLD);
				cout << ID <<"_Received" <<endl;
				for (size_t i = 0; i < sizeof(evaluated_guess) + 1; i++)
				{
					
					cout << evaluated_guess[i];
				}
				cout << endl;
			challenger->FilterGuesses(evaluated_guess);
			count_perfects = evaluated_guess[Constants::SPOTS];
			//cout << "My counter is: "<< count_perfects;
			//free(evaluated_guess);
			//}
			//challenger->FilterGuesses(evaluated_guess);

		}
		//count--;
		//cout << "aqui stoyxdxd";
	} while (!(Winner(evaluated_guess,ID)));
	MPI_Finalize();
	return EXIT_SUCCESS;
}


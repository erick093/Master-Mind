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

int main()
{
	MPI_Init(NULL, NULL);
	int ID;
	Challenger* challenger= NULL;
	GameMaster* gamemaster = NULL;
	int guesses_array[Constants::SPOTS];
	int *received_data, *choosen_guess;
	int* evaluated_guess=(int*)malloc(sizeof(int) * (Constants::SPOTS + 2));
	//cout << "Size of Buffer: "<< sizeof(evaluated_guess);
	ID = Operations::GetID();
	if (ID != 0)
	{
		cout << "Challenger_ID: " << ID << endl;
		challenger = new Challenger(ID);
		
	}
	else
	{
		cout << "Game_Master_ID: " << ID << endl;
		gamemaster = new GameMaster(0);
		gamemaster->PrintKey();
	}
	do {
		if ( ID == 0)
		{
			//cout << "Entering...";
			received_data = gamemaster->ReceiveData(&guesses_array, MPI_INT, MPI_COMM_WORLD);
			choosen_guess = gamemaster->RandomChoice(received_data, MPI_INT);
			evaluated_guess = gamemaster->EvaluateChoice(choosen_guess);
			//Send to other nodes
			gamemaster->SendEvaluation(evaluated_guess, MPI_INT, MPI_COMM_WORLD);
		}

		else
		{
			vector<int> guess;
			//cout << "Before paussible guess" << ID << endl;
			if (challenger->NotEmptyGuesses()) 
			{
				//cout << "Before random guess" << ID << endl;
				guess = challenger->PickRandomGuess();
				//cout << "After random guess" << ID << endl;
				for (size_t i = 0; i < guess.size(); i++)
				{
					guesses_array[i] = guess[i];
				}
				//cout << "Sending guess" <<ID <<endl;
				challenger->SendData(&guesses_array, MPI_INT, MPI_COMM_WORLD);
			}
			else 
			{
				//cout << "Sending Error "<<endl;
				challenger->SendError(MPI_COMM_WORLD);
			}
			challenger->ReceiveEvaluation(evaluated_guess, MPI_INT, MPI_COMM_WORLD);
			challenger->FilterGuesses(evaluated_guess);
		}
	} while (!(Operations::Winner(evaluated_guess,ID)));
	MPI_Finalize();
	return EXIT_SUCCESS;
}


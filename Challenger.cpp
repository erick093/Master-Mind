#include "Challenger.h"
#include "Constants.h"
#include "Operations.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string> 
#include <ctime>
#include <algorithm>
#include "mpi.h"
//vector<vector<int>> Challenger::combinations;

Challenger::Challenger(int ID)
{
	this->ID = ID;
	this->CreateSet();
	this->WriteToFile();
	this->InitFile();
}


bool Challenger::NotEmptyGuesses()
{
	return this->combinations.size() >= 1;
}
void Challenger::SendError(MPI_Comm communicator)
{
	int random_data[Constants::SPOTS + 1] = {};

	random_data[Constants::SPOTS] = 1;

	MPI_Gather(random_data, Constants::SPOTS + 1, MPI_INT, NULL, Constants::SPOTS + 1,
		MPI_INT, 0, communicator);
}

void Challenger::PrintCombination() {
	for (size_t i = 0; i < Challenger::combinations.size(); i++)
	{
		for (size_t j = 0; j < Challenger::combinations[i].size(); j++) std::cout << Challenger::combinations[i][j] << ' ';
		std::cout << std::endl;
	}
}

void Challenger::CreateSet()
{
	//cout<<"Intentando crear set...";
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
	int datatype_size;
	//int datatype_size;
	int* guess	 = (int*)send_data;
	MPI_Type_size(send_datatype, &datatype_size);
	//MPI_Type_size(datatype, &datatype_size);
	
	guess[Constants::ErrorBit] = 0; //Setting error bit to 0 
	int send_count = Constants::SPOTS + 1;
	int root = 0; //GameMaster ID
	cout << endl;
	cout << "sending challenger info"<<endl;
	MPI_Gather(guess, send_count, send_datatype, NULL, send_count,
		send_datatype, root, communicator);
}


void Challenger::WriteToFile()
{

	ID = this->ID;
	std::ofstream Out(std::to_string(ID) + "_Total_Pool_Challenger.txt");
	ostream_iterator<int> output_iterator(Out, "\t");
	for (size_t i = 0; i < this->combinations.size(); i++)
	{
		copy(this->combinations.at(i).begin(), this->combinations.at(i).end(), output_iterator);
		Out << '\n';
	}

	
}
void Challenger::InitFile() {
	ID = this->ID;
	std::ofstream Out(std::to_string(ID) + "_Challenger_Filtered.txt");
}
void Challenger::WriteToFile_2()
{
	ID = this->ID;
	//std::ofstream Out(std::to_string(ID) + "_Challenger_Filtered.txt");
	std::ofstream Out;
	Out.open(std::to_string(ID) + "_Challenger_Filtered.txt", std::ios_base::app);
	Out << "############################################";
	for (size_t i = 0; i < Constants::SPOTS; i++)
	{
		Out << this->temp_eval[i];
	}
	Out << "############################################";
	Out << '\n';
	//ostream_iterator<int> output_iterator(outFile, "\t");
	ostream_iterator<int> output_iterator(Out, "\t");
	for (size_t i = 0; i < this->combinations.size(); i++)
	{
		copy(this->combinations.at(i).begin(), this->combinations.at(i).end(), output_iterator);
		Out << '\n';
	}


}

vector<int>  Challenger::PickRandomGuess()
{
	srand((unsigned int)time(0));
	vector<int> RandomGuess = this->combinations[rand() % this->combinations.size()];
	return RandomGuess;
}

void Challenger::ReceiveEvaluation(int* receive_data, MPI_Datatype send_datatype, MPI_Comm communicator)
{
	int error = 0, eclass, len;
	char estring[MPI_MAX_ERROR_STRING];
	MPI_Error_class(error, &eclass);
	MPI_Error_string(error, estring, &len);
	MPI_Status status;
	int total = Constants::SPOTS + 2;
	//cout <<this->ID << "_Receiving"  ;
	//cout << endl;
	//MPI_Recv(&(receive_data[0]), total, send_datatype, 0, 0, communicator, MPI_STATUS_IGNORE); ///MPI STATUS IGNORE in order to not allocate the status message.
	error = MPI_Recv(receive_data, total, send_datatype, 0, 0, communicator, &status);

	this->temp_eval = receive_data;

	//printf("Error %d: %s\n", eclass, estring); fflush(stdout);
	//cout <<this->ID<<"_Received data: ";
	//for (size_t i = 0; i < Constants::SPOTS + 2; i++)
	//{
	//	cout <<receive_data[i] ;
	//}
	//cout << endl;
}



void Challenger::FilterGuesses(int* evaluation )
{

	//for (size_t i = 0; i < this->combinations.size(); i++)
	//{
	//	if (this->CheckGuess(this->combinations[i], evaluation))
	//	{
	//		this->combinations.push_back(this->combinations[i]);
	//	}
	//}
	vector<vector<int> > positions_to_filter;
	for (vector<int> guess : this->combinations)
	{
		if (this->CheckGuess(guess, evaluation))
		{
			positions_to_filter.push_back(guess);
		}
	}

	this->combinations = positions_to_filter;
	this->WriteToFile_2();
}



bool Challenger::CheckGuess(vector<int> guess, int* evaluation)
{
	int temp[Constants::SPOTS+2];
	//cout << "New Temp: ";
	for (size_t i = 0; i < Constants::SPOTS + 2; i++)
	{
		 temp[i]= evaluation[i];
		 //cout << temp[i];
	}
	//cout << endl;


	int guess_perfect = 0;
	int guess_color = 0;
	vector<int> copy_guess = guess;
	//int perfect_bit = Constants::SPOTS;
	//int color_bit = Constants::SPOTS + 1;
	
	int evaluation_perfect = evaluation[Constants::SPOTS];
	int evaluation_color = evaluation[Constants::SPOTS +1];
	//cout << "Received Perfect: Received Color: " << evaluation_perfect<<evaluation_color ;
	//cout << "Guess_";
	for (int i = 0; i < Constants::SPOTS; ++i) {
		//evaluation[i] = data[i];
		//cout<<"TESTING!!" << guess[i] << temp[i];
		if (guess[i] == temp[i]) {
			guess_perfect ++;
			temp[i] += 1;
			temp[i] *= -1;
			copy_guess[i] += 1;
			copy_guess[i] *= -1;
			
			
			//cout << "Perfect found" << endl;
		}

	}
	
	//cout << endl;
	for (int j = 0; j < Constants::SPOTS; ++j) {
		if (copy_guess[j] >= 0)
		{
			//cout << "Copy Key: " << copy_key[j] << "index j: " << j << endl;
			for (int x = 0; x < Constants::SPOTS; ++x) {
				if (temp[x] >= 0 && temp[x] == copy_guess[j])
				{
					guess_color++;
					//cout << "Guess: "<<data[x]<<"index x: "<< x <<endl;
					temp[x] += 1;
					temp[x] *= -1;
					break;
				}
			}
		}
	}
	//cout << "Calculated Perfect: Calculated Color: " << guess_perfect << guess_color;
	//cout << endl;
	if (guess_perfect == evaluation_perfect && guess_color >= evaluation_color)
	{
		return true;
	}
	else
	{
		return false;
	}

}




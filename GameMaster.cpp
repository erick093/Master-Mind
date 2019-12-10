#include "GameMaster.h"
#include "Constants.h"
#include "Operations.h"
#include <algorithm>
#include <map>
using namespace std;

GameMaster::GameMaster(int ID = 0)
{
	this->ID = ID;
	this->GetKey();
	this->PrintKey(this->key);
}

void GameMaster::GetKey() {

	//vector<int> code;
	int max =Constants::COLORS;
	int min = 0;
	int random;
	srand(time(0));

	for (int i = 0; i < Constants::SPOTS; ++i) {

		random = min + (rand() % (max - min));
		key.push_back(random);
	}

	//return code;
}

void GameMaster::PrintKey(vector<int> const& input)
{	
	cout << "Key is: " <<endl;
	for (auto const& i : input) {
		cout << i << " ";
	}
	cout << endl;
}

int* GameMaster::ReceiveData(void* send_data, MPI_Datatype receive_datatype, MPI_Comm communicator)
{
	int data_buffer_size;
	int total_size;
	int* data_buffer;
	int receive_count = Constants::SPOTS + 1;
	int root = 0; //GameMaster ID
	MPI_Type_size(receive_datatype, &data_buffer_size);
	
	total_size = data_buffer_size * Constants::TotalNodes() * (receive_count);  // allocating space for all guesses from all challengers
	data_buffer = (int*)malloc(total_size);
	
	MPI_Gather(send_data, receive_count, receive_datatype, data_buffer, receive_count,
		receive_datatype, root, communicator);

	return data_buffer;
}

int* GameMaster::RandomChoice(int* data, MPI_Datatype datatype)
{
	int datatype_size;
	MPI_Type_size(datatype, &datatype_size);

	int i;
	
	int selected_node = rand() % (Constants::ChallengerNodes()) + 1;
	cout << "Selected Challenger: " << selected_node << endl;
	int* guess = (int*)malloc(Constants::SPOTS * sizeof(int));

	
	while (data[(Constants::ErrorBit) * selected_node + Constants::SPOTS] == 1)
	{
		selected_node = rand() % (Constants::ChallengerNodes()) + 1;
	}
	cout << "Master selected_guess: ";
	for (i = 0; i < Constants::SPOTS; i++)
	{
		guess[i] = data[(Constants::SPOTS + 1) * selected_node + i];
		cout  << guess[i];
	}

	return guess;
}

int* GameMaster::EvaluateChoice(int* data) {
	//Get Perfect and Colors
	int perfect = 0;
	int color = 0;
	int* evaluation = (int*)malloc((Constants::SPOTS + 2) * sizeof(int)); // +2 since we add 1 "bit" for perfect counter and 1 "bit" for color counter
	int perfect_bit = Constants::SPOTS;
	int color_bit = Constants::SPOTS + 1;
	vector<int> copy_key = this->key;

	for (int i = 0; i < Constants::SPOTS; ++i) {
		evaluation[i] = data[i];
		if (this->key[i] == data[i]) {
			perfect += 1;
			data[i] *= -1;
			copy_key[i] *= -1;
			//cout << endl;
			//cout << "Perfect found" << endl;
		}

	}

	for (int j = 0; j < Constants::SPOTS; ++j) {
		if (copy_key[j] > 0)
		{
			//cout << "Copy Key: " << copy_key[j] << "index j: " << j << endl;
			for (int x = 0; x < Constants::SPOTS; ++x) {
				if (data[x]>0 && data[x]==copy_key[j] )
				{
					color++;
					//cout << "Guess: "<<data[x]<<"index x: "<< x <<endl;
					data[x] *= -1;
					break;
				}
			}
		}
	}
	evaluation[perfect_bit] = perfect;
	evaluation[color_bit] = color;
	this->PrintEvaluation(evaluation);
	return evaluation;

}


void GameMaster::PrintEvaluation(int* evaluation) {
	int size = Constants::SPOTS + 2;
	cout << endl;
	cout << "Evaluation is :" ;
	for (int i = 0; i < size; i++)
	{
		cout << evaluation[i];
	}
}
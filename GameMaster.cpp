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
	//this->PrintKey(this->key);
}

void GameMaster::GetKey() {

	//vector<int> code;
	int max =Constants::COLORS;
	int min = 0;
	int random;
	srand((unsigned int)time(0));

	for (int i = 0; i < Constants::SPOTS; ++i) {

		random = min + (rand() % (max - min));
		key.push_back(random);
	}

	//return code;
}

//void GameMaster::PrintKey(vector<int> const& input)
//{	
//	cout << "Key is: " <<endl;
//	for (auto const& i : input) {
//		cout << i << " ";
//	}
//	cout << endl;
//}

void GameMaster::PrintKey()
{
	cout << "Key is: " << endl;
	for (auto const& i : key) {
		cout << i << " ";
	}
	cout << endl;
}

void GameMaster::CheckIDLE(int* data)
{
	int i;
	int status_code;
	int number_challengers = Constants::TotalNodes();

	for (i = 0; i < number_challengers; i++)
	{
		status_code = data[i * (Constants::SPOTS + 1) + Constants::SPOTS];

		if (status_code == 1)
		{
			cout << "Challenger_" << i << " IDLE" << endl;
		}
	}
}

int *GameMaster::ReceiveData(void* send_data, MPI_Datatype receive_datatype, MPI_Comm communicator)
{
	int data_buffer_size;
	int total_size;
	int* data_buffer;
	int receive_count = Constants::SPOTS + 1;
	int root = 0; //GameMaster ID
	MPI_Type_size(receive_datatype, &data_buffer_size);
	total_size = data_buffer_size * Constants::TotalNodes() * (Constants::SPOTS + 1);  // allocating space for all guesses from all challengers
	data_buffer = (int*)malloc(total_size);
	//cout << "before gather" << endl;
	MPI_Gather(send_data, Constants::SPOTS + 1, receive_datatype, data_buffer, Constants::SPOTS + 1,
		receive_datatype, root, communicator);
	//cout << "after gather" << endl;
	this->CheckIDLE(data_buffer);

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
	//cout << "Size of Buffer(Inside): " << sizeof(evaluation);
	int perfect_bit = Constants::SPOTS;
	int color_bit = Constants::SPOTS + 1;
	vector<int> copy_key = this->key;
	//cout <<endl;
	//cout << "In evaluation" << endl;
	for (int i = 0; i < Constants::SPOTS; ++i) {
		evaluation[i] = data[i];
		if (this->key[i] == data[i]) {
			perfect += 1;
			data[i] += 1;
			data[i] *= -1;			
			copy_key[i] += 1;
			copy_key[i] *= -1;
			//cout << endl;
			//cout << "Perfect found" << evaluation[i]<< endl;
		}

	}
	//cout << "After perfects" <<endl;
	for (size_t j = 0; j < Constants::SPOTS; ++j) {
		if (copy_key[j] >= 0)
		{
			//cout << "Copy Key: " << copy_key[j] << "index j: " << j << endl;
			for (size_t x = 0; x < Constants::SPOTS; ++x) {
				//cout <<"Important!!" <<data[x] << copy_key[j];
				if (data[x]>=0 && data[x]==copy_key[j] )
				{
					color++;
					//cout << "Guess: "<<data[x]<<"index x: "<< x <<endl;
					data[x] += 1;
					data[x] *= -1;
					break;
				}
			}
		}
	}
	//cout << "After colors" << endl;
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
	cout << endl;
}

void GameMaster::SendEvaluation(int* send_data, MPI_Datatype send_datatype, MPI_Comm communicator)  
{
	int total = Constants::SPOTS + 2;
	int error=0,eclass,len;
	char estring[MPI_MAX_ERROR_STRING];
	MPI_Error_class(error, &eclass);
	MPI_Error_string(error, estring, &len);
	for (int i = 1; i < Constants::TotalNodes() ; i++)
	{
		
		if (i != this->ID) {
			//cout << "Send node" << i << endl;
			error = MPI_Send((send_data), total, send_datatype, i, 0, communicator);
			//printf("Error %d: %s\n", eclass, estring); fflush(stdout);
			//cout << "Sending info Master to Challenger_" << i << endl;
		}

	}


}


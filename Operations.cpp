#include "Operations.h"
using namespace std;
#include <ctime>
#include "mpi.h"
int* Operations::GenerateKey(int colors, int spots)
{	
	srand((unsigned)time(0));
	int* key = (int*)malloc((spots) * sizeof(int));
	int random;
	for (int i = 0; i < spots; i++)
	{
	random = rand() % (colors);
	//do
	//{
	//	random = rand() % (colors+1);
	//} while (random == 0);
	key[i] = random;	
	}
	return key;
}
void Operations::PrintArray(int* array, int size, string message)
{
	cout << message << endl;
	for (int i = 0; i < size; i++)
	{
		cout << array[i];
	
	}
	cout << endl;
}

int Operations::GetID()
{
	int PROCESS_ID;

	MPI_Comm_rank(MPI_COMM_WORLD, &PROCESS_ID);

	return PROCESS_ID;
}

bool Operations::Winner(int* evaluation, int ID)
{
	bool win = false;
	int number_of_perfects = evaluation[Constants::SPOTS];
	if (number_of_perfects == Constants::SPOTS)
	{
		if (ID == 0)
		{
			cout << "Challenger guessed the solution:";
			for (size_t i = 0; i < Constants::SPOTS; i++)
			{
				cout << evaluation[i];
			}
		}
		win = true;
	}
	

	return win;
}
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
	random = rand() % (colors+1);
	do
	{
		random = rand() % (colors+1);
	} while (random == 0);
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
#include "Constants.h"
//int Constants::COLORS = 0;
//int Constants::SPOTS = 0;
//void Constants::GetColors() {
//	int x;
//	cout << "Number of Colors: " << endl;
//	cin >> x;
//	Constants::COLORS = x;
//}
//void Constants::GetSpots() {
//	cout << "Number of Spots: " << endl;
//	cin >> Constants::SPOTS;
//
//}

int Constants::TotalNodes(){
	int comm_size;

	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	return comm_size;
}
int Constants::ChallengerNodes() {
	int total_nodes;
	total_nodes = Constants::TotalNodes();
	return total_nodes - 1;
}
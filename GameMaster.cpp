#include "GameMaster.h"
#include "Constants.h"
#include "Operations.h"
using namespace std;

GameMaster::GameMaster(int ID)
{
	this->ID = ID;
	this->GetKey();
	this->PrintKey(this->key);
}

void GameMaster::GetKey() {

	//vector<int> code;B
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
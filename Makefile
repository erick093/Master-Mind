#Makefile for Mastermind.cpp

mastermind: Mastermind.o Constants.o Operations.o Challenger.o GameMaster.o 
	mpic++ Mastermind.o Constants.o Operations.o Challenger.o GameMaster.o -o mastermind

Mastermind.o: Mastermind.cpp   Constants.h Operations.h Challenger.h GameMaster.h
	mpic++ -Wall -c Mastermind.cpp

Constants.o: Constants.cpp Constants.h
	mpic++ -Wall -c Constants.cpp

Operations.o: Operations.cpp Operations.h Challenger.h
	mpic++ -Wall -c Operations.cpp

Challenger.o: Challenger.cpp Challenger.h Constants.h Operations.h
	mpic++ -Wall -c Challenger.cpp

GameMaster.o: GameMaster.cpp GameMaster.h Constants.h Operations.h
	mpic++ -Wall -c GameMaster.cpp



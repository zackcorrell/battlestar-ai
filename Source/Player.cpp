/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Player.h"

Player::Player(char* Name, int BoardWidth, int BoardHeight)
{
	// Validate input
	if(Name == NULL)
	{
		printf("Invalid name for Player.\n");
		exit(-1);
	}

	// Copy name
	PlayerName = new char[strlen(Name) + 1];
	strcpy(PlayerName, Name);

	// Copy over width / height
	this->BoardWidth = BoardWidth;
	this->BoardHeight = BoardHeight;
}

Player::~Player()
{
	delete[] PlayerName;
}	

char* Player::GetName()
{
	return PlayerName;
}

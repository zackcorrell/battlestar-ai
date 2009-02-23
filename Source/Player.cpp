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
		Printf("Invalid name for Player.\n");
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

void Player::AddShipsStat(queue<Ship> Ships)
{
	// Warning: This assumes the given queue goes from low to high lengths
	int index = 0;
	while(!Ships.empty())
	{		
		// Get the current ship
		Ship TempShip = Ships.front();
		Ships.pop();

		// For the ship length
		for(int i = 0; i < (int)TempShip.ship; i++)
		{
			// Get base position
			int x = TempShip.x, y = TempShip.y;

			// Offset appropriately
			switch(TempShip.direction)
			{

			// Grow ship towards north
			case North:
				y -= i;
				break;

			// Grow ship towards north
			case East:
				x += i;
				break;

			// Grow ship towards north
			case South:
				y += i;
				break;

			// Grow ship towards north
			case West:
				x -= i;
				break;

			default: break;
			}

			// Grow stat
			PlacementBoard[index][y * BoardWidth + x]++;
		}

		// Grow index
		index++;
	}
}

void Player::PrintStat()
{
	// For each ship type
	for(int i = 0; i < 5; i++)
	{
		// Header
		Printf(">> Ship placement for ship[%d] by %s\n", i, GetName());

		// Print table
		for(int y = 0; y < BoardHeight; y++)
		{
			for(int x = 0; x < BoardWidth; x++)
			{
				// Output current element
				Printf("(%d)\t", PlacementBoard[i][y * BoardWidth + x]);
			}
			Printf("\n");
		}

		// Ender
		Printf(">> Done\n");
	}
}


/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Player.h"

Player::Player(char* Name, int Board1Width, int Board1Height)
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
	this->Board1Width = Board1Width;
	this->Board1Height = Board1Height;

	// Allocate placement board (For use with stat measurements)
	for(int i = 0; i < 5; i++)
	{
		PlacementBoard1[i] = new int[Board1Width * Board1Height];
		for(int j = 0; j < Board1Width * Board1Height; j++)
			PlacementBoard1[i][j] = 0;
	}
}

Player::~Player()
{
	// Print out game stats (if not silent)
	PrintStat();

	// Release player name
	delete[] PlayerName;

	// Release placement board
	for(int i = 0; i < 5; i++)
		delete [] PlacementBoard1[i];
}	

char* Player::GetName()
{
	return PlayerName;
}

void Player::Reset()
{
	// Should be implemented by the child class...
}

void Player::Setup(Ship *Ships, int ShipCount)
{
	// Setup function passes onto the public static setup function that's pretty generic
	SetupStatic(Ships, ShipCount, Board1Width, Board1Height);

	// Add placement to placement history (For stats)
	AddShipsStat(Ships, ShipCount);
}

void Player::SetupStatic(Ship *Ships, int ShipCount, int Board1Width, int Board1Height)
{
	// Validate input
	if(Ships == NULL)
	{
		Printf("Invalid Ships pointer given to Setup(...).\n");
		exit(-1);
	}

	// Default behavior is randomization
	for(int i = 1; i <= ShipCount; i++)
	{
		// Choose the appropriate type
		int length = i;
		if(i == 1)
			length = 2;
		else if(i == 2)
			length = 3;

		// Choose a random direction
		Direction dir = (Direction)(rand() % 4);

		// Choose a random starting position
		int x = rand() % Board1Width;
		int y = rand() % Board1Height;

		// Create the ship and place into memory
		Ship ship((ShipType)length, x, y, dir);
		Ships[i - 1] = ship;

		// Validate if this new ship is any good
		if( Board1::ValidateShips(Ships, i, Board1Width, Board1Height) == false)
			i--;
	}
}

void Player::Shoot(int *x, int *y)
{
	// Should be implemented by the child class...
}

void Player::ShootResult(int x, int y, ShotState state)
{
	// Should be implemented by the child class...
}

void Player::EnemyResult(int x, int y, ShotState state)
{
	// Should be implemented by the child class...
}

void Player::AddShipsStat(Ship *Ships, int ShipCount)
{
	// Check for valid ships list
	if(Ships == NULL)
	{
		Printf("Invalid Ships pointer given in AddShipsStat(...).\n");
		exit(-1);
	}

	// For each ship
	for(int i = 0; i < ShipCount; i++)
	{
		// Get the current ship
		Ship TempShip = Ships[i];

		// For the ship length
		for(int j = 0; j < (int)TempShip.Type; j++)
		{
			// Get position
			int x = TempShip.x[j], y = TempShip.y[j];

			// Grow stat
			PlacementBoard1[i][y * Board1Width + x]++;
		}
	}

	// All ships processed...
}

void Player::PrintStat()
{
	// For each ship type
	for(int i = 0; i < 5; i++)
	{
		// Header
		Printf(">> Ship placement for ship[%d] by %s\n", i, GetName());

		// Print table
		for(int y = 0; y < Board1Height; y++)
		{
			for(int x = 0; x < Board1Width; x++)
			{
				// Output current element
				Printf("(%d)\t", PlacementBoard1[i][y * Board1Width + x]);
			}
			Printf("\n");
		}

		// Ender
		Printf(">> Done\n");
	}
}

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "DumbPlayer.h"

DumbPlayer::DumbPlayer(int BoardWidth, int BoardHeight)
	: Player("DumbPlayer AI", BoardWidth, BoardHeight)
{
	// Allocate "hit" board
	Board = new bool[BoardWidth * BoardHeight];
}

DumbPlayer::~DumbPlayer()
{
	// Release "hit" board
	delete [] Board;
}

void DumbPlayer::Reset()
{
	// Reset "hit" board
	for(int i = 0; i < BoardWidth * BoardHeight; i++)
	{
		Board[i] = false;
	}
}

void DumbPlayer::Setup(queue<Ship> *Ships)
{
	// Randomly choose ship positions
	Ship TempShip;
	for(int i = 5; i > 0; i--)
	{
		// Choose the appropriate type
		TempShip.ship = (ShipType)i;
		if(i == 2)
			TempShip.ship = (ShipType)3;
		else if(i == 1)
			TempShip.ship = (ShipType)2;

		// Choose a random direction
		TempShip.direction = (Direction)(rand() % 4);

		// Choose a random position
		TempShip.x = rand() % BoardWidth;
		TempShip.y = rand() % BoardHeight;

		// Validate if this new ship is any good
		if( Board::ValidateShip(Ships, &TempShip, BoardWidth, BoardHeight) )
			Ships->push(TempShip);
		// Try again
		else
			i++;
	}
}

void DumbPlayer::Shoot(int *x, int *y)
{
	while(true)
	{
		*x = rand() % BoardWidth;
		*y = rand() % BoardHeight;

		// If we have not yet shot this position, shoot it
		if(Board[*y * BoardWidth + *x] == false)
			break;
	}

	Board[*y * BoardWidth + *x] = true;
}

void DumbPlayer::ShootResult(int x, int y, ShotState state)
{
	// Nothing to do...
}

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int BoardWidth, int BoardHeight)
	: Player("HumanPlayer", BoardWidth, BoardHeight)
{
	// Nothing to do...
}

HumanPlayer::~HumanPlayer()
{
	// Nothing to do...
}

void HumanPlayer::Reset()
{
	// Nothing to do...
}

void HumanPlayer::Setup(queue<Ship> *Ships)
{
	// Randomly choose ship positions
	Ship TempShip;
	for(int i = 1; i <= 5; i++)
	{
		// Choose the appropriate type
		TempShip.ship = (ShipType)i;
		if(i == 1)
			TempShip.ship = (ShipType)2;
		else if(i == 2)
			TempShip.ship = (ShipType)3;

		// Get the target ship position
		printf(">>> Please enter the position of ship length %d: ", (int)TempShip.ship);
		scanf("%d %d", &TempShip.x, &TempShip.y);

		// Get the target ship direction
		printf(">>> Please enter the ship's direction (0 = N, 0 = E, ...): ");
		int dir;
		scanf("%d", &dir);
		TempShip.direction = (Direction)(dir);

		// Validate if this new ship is any good
		if( dir >= 0 && dir <= 3 && Board::ValidateShip(Ships, &TempShip, BoardWidth, BoardHeight) )
			Ships->push(TempShip);
		// Try again
		else
		{
			// The given ship is invalid
			printf(">>> The given ship was invalid. Try again.\n");
			i--;
		}
	}

	// Add placement to placement history
	AddShipsStat(*Ships);
}

void HumanPlayer::Shoot(int *x, int *y)
{
	// Set default data
	*x = -1;
	*y = -1;

	// Keep asking for valid data
	while(*x < 0 || *x >= BoardWidth || *y < 0 || *y >= BoardHeight)
	{
		// Get a position to shoot
		printf(">>> Please enter a correct x and y to shoot: ");
		scanf("%d %d", x, y);
	}
}

void HumanPlayer::ShootResult(int x, int y, ShotState state)
{
	// Nothing to do...
	printf("Result: (%d, %d):%d\n", x, y, state);
}

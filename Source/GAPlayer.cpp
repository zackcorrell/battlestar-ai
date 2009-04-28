/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GAPlayer.h"

GAPlayer::GAPlayer(int BoardWidth, int BoardHeight)
	: Player("GAPlayer AI", BoardWidth, BoardHeight)
{
	GASinking Pool(10, 10, "zkg5001");
	Ship Ships[5];
	Player::SetupStatic(Ships, 5, 10, 10);
	Pool.SaveEnemyBoard(Ships, 5);
	for(int i = 0; i < 10; i++)
		Pool.Update();
}

GAPlayer::~GAPlayer()
{
	// ...
}

void GAPlayer::Reset()
{
	// ...
}

void GAPlayer::Setup(Ship *Ships, int ShipCount)
{
	// ...
}

void GAPlayer::Shoot(int *x, int *y)
{
	// ...
}

void GAPlayer::ShootResult(int x, int y, ShotState state)
{
	// ...
}

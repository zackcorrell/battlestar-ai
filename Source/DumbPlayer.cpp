/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "DumbPlayer.h"

DumbPlayer::DumbPlayer(int BoardWidth, int BoardHeight)
	: Player("DumbPlayer Hand-Coded", BoardWidth, BoardHeight)
{
	// Allocate "hit" board (No need to init, that is done in Reset())
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
		Board[i] = false;
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
	x = y = 0;
	state = StateMiss;
}

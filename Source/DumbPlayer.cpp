/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "DumbPlayer.h"

DumbPlayer::DumbPlayer(int Board1Width, int Board1Height)
	: Player("DumbPlayer Hand-Coded", Board1Width, Board1Height)
{
	// Allocate "hit" board (No need to init, that is done in Reset())
	Board1 = new bool[Board1Width * Board1Height];
}

DumbPlayer::~DumbPlayer()
{
	// Release "hit" board
	delete [] Board1;
}

void DumbPlayer::Reset()
{
	// Reset "hit" board
	for(int i = 0; i < Board1Width * Board1Height; i++)
		Board1[i] = false;
}

void DumbPlayer::Shoot(int *x, int *y)
{
	while(true)
	{
		*x = rand() % Board1Width;
		*y = rand() % Board1Height;

		// If we have not yet shot this position, shoot it
		if(Board1[*y * Board1Width + *x] == false)
			break;
	}

	Board1[*y * Board1Width + *x] = true;
}

void DumbPlayer::ShootResult(int x, int y, ShotState state)
{
	// Nothing to do...
	x = y = 0;
	state = StateMiss;
}

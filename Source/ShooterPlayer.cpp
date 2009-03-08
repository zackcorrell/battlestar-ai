/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "ShooterPlayer.h"

ShooterPlayer::ShooterPlayer(int BoardWidth, int BoardHeight)
	: Player("ShooterPlayer Hand-Coded", BoardWidth, BoardHeight)
{
	// Allocate "hit" board (No need to init, that is done in Reset())
	Board = new bool[BoardWidth * BoardHeight];

	// Default the last x and y shot
	HitState = 0;
}

ShooterPlayer::~ShooterPlayer()
{
	// Release "hit" board
	delete [] Board;
}

void ShooterPlayer::Reset()
{
	// Reset "hit" board
	for(int i = 0; i < BoardWidth * BoardHeight; i++)
		Board[i] = false;
}

void ShooterPlayer::Shoot(int *x, int *y)
{
	// If we are attempting to target...
	if(HitState == 0)
	{
		// Keep trying to get a valid (x, y)
		while(true)
		{
			// Choose a random y
			*y = rand() % BoardHeight;

			// Select a corrected x such that: x is even when y is even and x is odd when y is odd
			if(*y % 2 == 0)
			{
				// Find an even x
				while(true)
				{
					*x = rand() % BoardWidth;
					if(*x % 2 == 0)
						break;
				}
			}
			else
			{
				// Find an odd x
				while(true)
				{
					*x = rand() % BoardWidth;
					if(*x % 2 == 1)
						break;
				}
			}

			// If we have not yet shot this position, shoot it
			if(Board[*y * BoardWidth + *x] == false)
				break;
		}
	}
	// If we are searching for the direction...
	else if(HitState == 1)
	{
		// Default x and y
		*x = *y = -1;

		// Save the x and y
		while(*x < 0 || *x >= BoardWidth || *y < 0 || *y >= BoardHeight)
		{
			*x = HitSource[0];
			*y = HitSource[1];

			// Shoot in the target direction
			switch(HitDir)
			{

			// Grow ship towards north
			case North: *y -= 1; break;

			// Grow ship towards north
			case East: *x += 1; break;

			// Grow ship towards north
			case South: *y += 1; break;

			// Grow ship towards north
			case West: *x -= 1; break;

			default: break;
			}

			// Target next direction
			HitDir++;

			// We don't want to shoot the same spot..
			if(Board[*y * BoardWidth + *x] == true)
				*x = *y = -1; // Try again

			// If we have done a full cycle and can't find another hit, go back to state 0 - searching
			if(HitDir > 4)
			{
				// Attempt a normal shot
				HitState = 0;
				Shoot(x, y);
			}
		}

	}

	// Hit board
	Board[*y * BoardWidth + *x] = true;
}

void ShooterPlayer::ShootResult(int x, int y, ShotState state)
{
	// If we are searching, and we just got a hit
	if(HitState == 0 && state == StateHit)
	{
		// Save target
		HitSource[0] = x;
		HitSource[1] = y;

		// Default direction searching
		HitDir = North;
		HitState = 1;
	}
}

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "SinkPlayer.h"

SinkPlayer::SinkPlayer(int Board1Width, int Board1Height)
	: Player("SinkPlayer Hand-Coded", Board1Width, Board1Height)
{
	// Allocate "hit" board (No need to init, that is done in Reset())
	Board1 = new bool[Board1Width * Board1Height];
}

SinkPlayer::~SinkPlayer()
{
	// Release "hit" board
	delete [] Board1;
}

void SinkPlayer::Reset()
{
	// Reset "hit" board
	for(int i = 0; i < Board1Width * Board1Height; i++)
		Board1[i] = false;

	// Set state to searching
	State = Searching;
	flipped = false;
}

void SinkPlayer::Shoot(int *x, int *y)
{
	// If we are searching for a ship, just shoot any spot randomly
	if(State == Searching)
	{
		while(true)
		{
			targetx = rand() % Board1Width;
			targety = rand() % Board1Height;

			// If we have not yet shot this position, shoot it
			if(Board1[targety * Board1Width + targetx] == false)
				break;
		}
	}

	// Else if we have found a ship, but are targeting it, 
	else if(State == Targeting)
	{
		// keep trying to find in-bounded points
		while(true)
		{
			// jgb5034 points
			targetx = sourcex;
			targety = sourcey;

			// Modify target position based on direction we are searching
			if(SearchDirection == North)
				targety--;
			else if(SearchDirection == East)
				targetx++;
			else if(SearchDirection == South)
				targety++;
			else // West
				targetx--;

			// If we are out of bounds, or we have already shot this position...
			if(targetx < 0 || targetx >= Board1Width || targety < 0 || targety >= Board1Height || Board1[targety * Board1Width + targetx] == true)
			{
				// Switch to the next direction
				if(SearchDirection == North)
					SearchDirection = East;
				else if(SearchDirection == East)
					SearchDirection = South;
				else if(SearchDirection == South)
					SearchDirection = West;
				else // Give up, we lost our target
				{
					// Choose a new point
					State = Searching;
					flipped = false;
					Shoot(&targetx, &targety);
					break;
				}
			}
			// Else the position is valid!
			else
				break;
		}

	}

	// Else we have targeted the ship, and now are trying to sink it
	else if(State == Locked)
	{
		// Try to find a valid point
		while(true)
		{
			// Lets just shoot at the next position
			if(SearchDirection == North)
				targety--;
			else if(SearchDirection == East)
				targetx++;
			else if(SearchDirection == South)
				targety++;
			else // West
				targetx--;

			// If it's out of bounds, let's reset the position and flip points, else, break
			if(targetx < 0 || targetx >= Board1Width || targety < 0 || targety >= Board1Height || Board1[targety * Board1Width + targetx] == true)
			{
				// If we are done sinking the ship...
				if(flipped)
				{
					// Set random search state..
					State = Searching;
					flipped = false;
					Shoot(&targetx, &targety);
					break;
				}

				// Set new target
				targetx = sourcex;
				targety = sourcey;

				// Flip dir
				if(SearchDirection == North)
					SearchDirection = South;
				else if(SearchDirection == East)
					SearchDirection = West;
				else if(SearchDirection == South)
					SearchDirection = North;
				else // West
					SearchDirection = East;

				// Set flip flag to true
				flipped = true;
			}
			else
				break;
		}
	}

	// Set points
	*x = targetx;
	*y = targety;

	// Done with targeting...
	Board1[*y * Board1Width + *x] = true; // Save spot shot at
}

void SinkPlayer::ShootResult(int x, int y, ShotState state)
{
	// If we are searching for a ship
	if(State == Searching)
	{
		// If we hit something, we should go to the targeting state
		if(state == StateHit)
		{
			// Save source target
			State = Targeting;
			sourcex = x;
			sourcey = y;

			// jgb5034 direction to North
			SearchDirection = North;
		}
	}
	// If we are targetining..
	else if(State == Targeting)
	{
		// If we missed on this current direction, switch it to the next
		if(state == StateMiss)
		{
			// Switch to the next direction
			if(SearchDirection == North)
				SearchDirection = East;
			else if(SearchDirection == East)
				SearchDirection = South;
			else if(SearchDirection == South)
				SearchDirection = West;
			else // Give up, we lost our target
				State = Searching;
		}
		// We got a hit in the direction we are looking at!
		else
			State = Locked;
	}
	// If we are locked
	else if(State == Locked)
	{
		// If we missed a shot while locked, we need to flip
		if(state == StateMiss && !flipped)
		{
			// Set flip to true
			flipped = true;

			// jgb5034 positions
			targetx = sourcex;
			targety = sourcey;

			// Flip direction
			if(SearchDirection == North)
				SearchDirection = South;
			else if(SearchDirection == East)
				SearchDirection = West;
			else if(SearchDirection == South)
				SearchDirection = North;
			else // West
				SearchDirection = East;
		}
		// If we flipped, and we missed our shot, then we have sunk the ship
		else if(state == StateMiss && flipped)
		{
			State = Searching;
			flipped = false;
		}
	}
}

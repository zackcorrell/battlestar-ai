/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GAPlayer.h"

GAPlayer::GAPlayer(char *EnemyName, int BoardWidth, int BoardHeight)
	: Player("GAPlayer AI", BoardWidth, BoardHeight)
{
	// Instance a placement board
	ShotBoard = new bool[BoardWidth * BoardHeight];
	for(int i = 0; i < BoardWidth * BoardHeight; i++)
		ShotBoard[i] = false;

	// Instance the three components
	Placement = new GAPlacement(EnemyName, BoardWidth, BoardHeight);

	// Save enemy name
	Shooting = new GAShoot(EnemyName);

	// Sinking logic
	Sinking = new GASinking(BoardWidth, BoardHeight, EnemyName);
	Sinking->Update(); // Let us create our gene pool

	// Default shot states
	TargetX = TargetY = 0;
	TargetHit = false;

	// Load up a first shot
	Shooting->
	
}

GAPlayer::~GAPlayer()
{
	// Delete (To force out some writes)
	delete Placement;
	delete Shooting;
	delete Sinking;
}

void GAPlayer::Reset()
{
	// Release
}

void GAPlayer::Setup(Ship *Ships, int ShipCount)
{
	// Ask out placement algorithm for a list of ships to place
	Placement->Setup(Ships, ShipCount);
}

void GAPlayer::Shoot(int *x, int *y)
{
	/*
	// Keep looping until we would like to place a shot
	while(true)
	{
		// Run through the program until an event
		GARunState State = Gene->Run(&TargetX, &tempy, HasHit);

		// Ask for a shot, place it into the next run call
		if( State == GetShot )
		{
			// Non-repeating value
			while(true)
			{
				// Get a valid position
			}
		}

		// Place a shot onto the board
		else if( State == SetShot )
		{
			// Wrap out x and y points and check for negatives
			TargetX %= 10;
			TargetY %= 10;

			// Place shot
			ShotState BoardState = SampleBoard.GetState(TargetX, TargetY);

			// If we have nothing, return a miss
			if(BoardState == StateShip)
			{
				SampleBoard.SetState(tempx, tempy, StateHit);
				SampleBoard.HitShip(tempx, tempy);
				HasHit = true;

				// We take another shot
				//ShotCount++;
			}
			else if(BoardState == StateMiss)
			{
				// Already shot here, and nothing
				HasHit = false;
			}
			else if(BoardState == StateHit)
			{
				// If we have already hit a ship here, lets walk through
				// to the next valid position (if any exists)

				// Save direction
				Direction dir = Gene->TargetDir;
				int x = Gene->TargetPos[0];
				int y = Gene->TargetPos[1];

				// Keep moving in that direction until we read a non-shot zone
				while(x >= 0 && y >= 0 && x < 10 && y < 10)
				{
					// If this area is non-shot or a ship, then break
					if(SampleBoard.GetState(x, y) == StateEmpty || SampleBoard.GetState(x, y) == StateShip)
						break;

					// Move
					if(dir == North)
						y--;
					else if(dir == East)
						x++;
					else if(dir == South)
						y++;
					else
						x--;
				}

				// If the position is still valid, actually shoot it
				if(x >= 0 && y >= 0 && x < 10 && y < 10)
				{
					// Post back to gene
					Gene->TargetPos[0] = x;
					Gene->TargetPos[1] = y;

					// Post back to board
					SampleBoard.SetState(x, y, StateHit);
					SampleBoard.HitShip(x, y);
					HasHit = true;

					// We take another shot
					//ShotCount++;
				}
				// Else, invalid, just let it die
				else
					HasHit = false;
			}
			else
			{
				// Normal miss condition
				SampleBoard.SetState(tempx, tempy, StateMiss);
				HasHit = false;
			}
		}
	*/

	// Actually shoot at position
	SetShot(*x, *y);
}

void GAPlayer::ShootResult(int x, int y, ShotState state)
{
	// 
}

void GAPlayer::EnemyResult(int x, int y, ShotState state)
{
	// Tell our placement algorithm how our enemy shot
	Placement->EnemyShootsAt(x, y);
}

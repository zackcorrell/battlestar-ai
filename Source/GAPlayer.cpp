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

	// Instance the placement
	Placement = new GAPlacement(EnemyName, BoardWidth, BoardHeight);

	// Instance shooting GA
	Shooting = new GAShoot(EnemyName);

	// Instance sinking GA
	Sinking = new GASinking(BoardWidth, BoardHeight, EnemyName);

	// Default shot states
	TargetX = TargetY = 0;
	TargetHit = false;
	PostBack = false;

	// Load up a first shot
	Shooting->getTarget(&TargetX, &TargetY);
}

GAPlayer::~GAPlayer()
{
	// Delete (To force out some writes)
	delete Placement;
	delete Shooting;

	// Update to test out and save out new genes
	Sinking->Update();
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
	// Keep looping until we would like to place a shot
	while(true)
	{
		// Run through the program until an event
		GARunState State = Sinking->Run(&TargetX, &TargetY, TargetHit);

		// If something freaks out..
		if( State == GeneFailure )
		{
			// Reset internals and use this standard gene
			delete Sinking;
			Sinking = new GASinking(10, 10, "Default");
		}

		// Ask for a shot, place it into the next run call
		else if( State == GetShot )
		{
			// Non-repeating value
			while(true)
			{
				// Get a valid position
				Shooting->getTarget(&TargetX, &TargetY);

				// Safety check
				TargetX %= 10;
				TargetY %= 10;

				// If we have yet to shoot here, break
				if( ShotBoard[ TargetY * 10 + TargetX ] == false )
					break;
			}
		}

		// Place a shot onto the board
		else if( State == SetShot )
		{
			// Wrap out x and y points and check for negatives
			TargetX %= 10;
			TargetY %= 10;

			// If we have yet to post data
			if(!PostBack)
			{
				// Place shot (by returning from this function)
				PostBack = true;
				break;
			}
			// We have gotten our data back
			else
			{
				// No post-back yet
				PostBack = false;

				// If we have already hit a position
				if( ShotBoard[TargetY * 10 + TargetX] == true && TargetHit == false )
				{
					
				}
			}
		}

	} // <- End of loop

	// Actually shoot at position
	*x = TargetX;
	*y = TargetY;
	Shooting->SetShot(TargetX, TargetY);
	ShotBoard[TargetY * 10 + TargetX] = true;
}

void GAPlayer::ShootResult(int x, int y, ShotState state)
{
	// Save the hit into the shooting and sinking algorithm
	if(state == StateHit)
	{
		TargetHit = true;
		//Shooting->SaveHit(x, y);
	}
	else
		TargetHit = false;
}

void GAPlayer::EnemyResult(int x, int y, ShotState state)
{
	// Tell our placement algorithm how our enemy shot
	Placement->EnemyShootsAt(x, y);
}

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GAPlayer.h"

GAPlayer::GAPlayer(char *EnemyName, int Board1Width, int Board1Height)
	: Player("GAPlayer AI", Board1Width, Board1Height)
{
	// Instance a placement board
	ShotBoard1 = new bool[Board1Width * Board1Height];
	for(int i = 0; i < Board1Width * Board1Height; i++)
		ShotBoard1[i] = false;
	strcpy(this->EnemyName, EnemyName);

	// Instance the placement
	Placement = new GAPlacement(EnemyName, Board1Width, Board1Height);

	// Instance shooting GA
	Shooting = new GAShoot(EnemyName);

	// Instance sinking GA
	Sinking = new GASinking(Board1Width, Board1Height, "Default");

	// Default shot states
	TargetX = TargetY = 0;
	TargetHit = false;
}

GAPlayer::~GAPlayer()
{
	// Delete (To force out some writes)
	delete Placement;
	delete Shooting;

	// Update to test out and save out new genes
	Sinking->Update();
	delete Sinking;

	// Release shot board
	delete[] ShotBoard1;
}

void GAPlayer::Reset()
{
	// Delete (To force out some writes)
	delete Placement;
	delete Shooting;

	// Update to test out and save out new genes
	Sinking->Update();
	delete Sinking;

	// Release shot board
	delete[] ShotBoard1;



	// Instance a placement board
	ShotBoard1 = new bool[Board1Width * Board1Height];
	for(int i = 0; i < Board1Width * Board1Height; i++)
		ShotBoard1[i] = false;

	// Instance the placement
	Placement = new GAPlacement(EnemyName, Board1Width, Board1Height);

	// Instance shooting GA
	Shooting = new GAShoot(EnemyName);

	// Instance sinking GA
	Sinking = new GASinking(Board1Width, Board1Height, "Default");

	// Default shot states
	TargetX = TargetY = 0;
	TargetHit = false;
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
			continue; // Pop back to the top
		}

		// Ask for a shot, place it into the next run call
		else if( State == GetShot )
		{
			// Get a valid position
			Shooting->getTarget(&TargetX, &TargetY);
		}

		// Place a shot onto the board
		else if( State == SetShot )
		{
			// Wrap out x and y points and check for negatives
			TargetX %= 10;
			TargetY %= 10;

			// If we have already hit a position
			if( ShotBoard1[TargetY * 10 + TargetX] == true && TargetHit == false )
			{
				// If we have already hit a ship here, lets walk through
				// to the next valid position (if any exists)

				// Save direction
				Direction dir = Sinking->GetBest()->TargetDir;
				int x = Sinking->GetBest()->TargetPos[0];
				int y = Sinking->GetBest()->TargetPos[1];

				// Keep moving in that direction until we read a non-shot zone
				while(x >= 0 && y >= 0 && x < 10 && y < 10)
				{
					// If this area is non-shot or a ship, then break
					if(ShotBoard1[TargetY * 10 + TargetX] == false)
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
					Sinking->GetBest()->TargetPos[0] = x;
					Sinking->GetBest()->TargetPos[1] = y;
					TargetX = x;
					TargetY = y;
				}
			}

			// Break out to set shot position
			break;
		}

	} // <- End of loop

	// Actually shoot at position
	*x = TargetX % 10;
	*y = TargetY % 10;
	Shooting->setShot(*x, *y);
	ShotBoard1[(*y) * 10 + (*x)] = true;
}

void GAPlayer::ShootResult(int x, int y, ShotState state)
{
	// Save the hit into the shooting and sinking algorithm
	if(state == StateHit)
	{
		TargetHit = true;
		Shooting->saveHit(x, y);
	}
	else
		TargetHit = false;
}

void GAPlayer::EnemyResult(int x, int y, ShotState state)
{
	// Tell our placement algorithm how our enemy shot
	Placement->EnemyShootsAt(x, y);

	// Tell our shooting algorithm our sucess
	Shooting->saveHit(x, y);
}

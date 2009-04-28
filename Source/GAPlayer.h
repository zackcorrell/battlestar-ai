/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: GAPlayer.h
 Desc: The interface between the Placement, Shooting, and Sinking
       AI components.
 
***************************************************************/

// Inclusion guard
#ifndef __GAPLAYER_H_
#define __GAPLAYER_H_

#include "GAPlacement.h"   // Ship placement
#include "GAShoot.h"       // Shooting logic
#include "GASinking.h" // Sinking logic

// Player class
class GAPlayer : public Player
{
public:

	// Required to implement
	GAPlayer(char *EnemyName, int BoardWidth, int BoardHeight);

	~GAPlayer();

	// Required to implement
	void Reset();

	// Intelligent ship placement
	void Setup(Ship *Ships, int ShipCount);

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

	// Required to implement
	void EnemyResult(int x, int y, ShotState state);

private:

	// Ship placement
	GAPlacement *Placement;

	// Shooting logic
	GAShoot *Shoot;

	// Sinking logic
	GASinking *Sinking;

	// Shot placement (x, y)
	int TargetX, TargetY;

	// True if successful shot
	bool TargetHit;

	// Board for previous shots
	bool *ShotBoard;

};

// End of inclusion guard
#endif

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: SmartRandom.h
 Desc: A smart-random (checkreboard) shooter, but once a ship has
       been hit, it will attempt to sink it. Based on a simple
	   three-state state machine.
 
***************************************************************/

// Inclusion guard
#ifndef __SMARTRANDOM_H_
#define __SMARTRANDOM_H_

// Includes
#include "Player.h"
#include "Board.h"

class SmartRandom : public Player
{
public:

	// Required to implement
	SmartRandom(int BoardWidth, int BoardHeight);

	~SmartRandom();

	// Required to implement
	void Reset();

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

	// Returns true if the board is already funn with a checkerboard pattern
	bool CheckerFull();

	// The current state of the targeting
	TargetingState State;

	// The starting and target x and y durring a "locked" target for sinking
	int sourcex, sourcey;
	int targetx, targety;
	bool flipped;

	// Direction we are searching
	Direction SearchDirection;

	// Board to prevent shooting at the same position
	bool *Board;

};

// End of inclusion guard
#endif

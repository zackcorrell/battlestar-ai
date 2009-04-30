/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: SinkPlayer.h
 Desc: A random shooter, but once a ship has been hit, it will
       attempt to sink it. Based on a simple linear state machine.
 
***************************************************************/

// Inclusion guard
#ifndef __SINKPLAYER_H_
#define __SINKPLAYER_H_

// Includes
#include "Player.h"
#include "Board1.h"

class SinkPlayer : public Player
{
public:

	// Required to implement
	SinkPlayer(int Board1Width, int Board1Height);

	~SinkPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

	// The current state of the targeting
	TargetingState State;

	// The starting and target x and y durring a "locked" target for sinking
	int sourcex, sourcey;
	int targetx, targety;
	bool flipped;

	// Direction we are searching
	Direction SearchDirection;

	// Board1 to prevent shooting at the same position
	bool *Board1;

};

// End of inclusion guard
#endif

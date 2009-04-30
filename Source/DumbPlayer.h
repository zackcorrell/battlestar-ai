/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: DumbPlayer.h
 Desc: A dumb, random based, player implementation/
 
***************************************************************/

// Inclusion guard
#ifndef __DUMBPLAYER_H_
#define __DUMBPLAYER_H_

// Includes
#include "Player.h"
#include "Board1.h"

class DumbPlayer : public Player
{
public:

	// Required to implement
	DumbPlayer(int Board1Width, int Board1Height);

	~DumbPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

	// Board1 to prevent shooting at the same position
	bool *Board1;


};

// End of inclusion guard
#endif

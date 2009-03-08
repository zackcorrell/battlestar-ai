/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: GAPlayer.h
 Desc: The interface between the GenesManager (a GA/GP solution
       to the game of battleship) to the battleship player
	   interface for the game simulator.
 
***************************************************************/

// Inclusion guard
#ifndef __GAPLAYER_H_
#define __GAPLAYER_H_

// Includes
#include "Player.h"
#include "Board.h"

// Player class
class GAPlayer : public Player
{
public:

	// Required to implement
	GAPlayer(int BoardWidth, int BoardHeight);

	~GAPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

};

// End of inclusion guard
#endif

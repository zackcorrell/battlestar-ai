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
#include <cstdlib>
#include "Player.h"
#include "Board.h"

class DumbPlayer : public Player
{
public:

	// Required to implement
	DumbPlayer(int BoardWidth, int BoardHeight);

	~DumbPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Setup(queue<Ship> *Ships);

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

	bool *Board;

};

// End of inclusion guard
#endif

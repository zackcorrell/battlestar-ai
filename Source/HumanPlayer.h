/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: DumbPlayer.h
 Desc: An interface for a human player; Taking "shoot" commands
       via the terminal.
 
***************************************************************/

// Inclusion guard
#ifndef __HUMANPLAYER_H_
#define __HUMANPLAYER_H_

// Includes
#include "Player.h"
#include "Board.h"

class HumanPlayer : public Player
{
public:

	// Required to implement
	HumanPlayer(int BoardWidth, int BoardHeight);

	~HumanPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Setup(queue<Ship> *Ships);

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

};

// End of inclusion guard
#endif

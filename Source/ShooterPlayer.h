/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: ShooterPlayer.h
 Desc: A dumb, random based, player implementation. When it does
       hit a ship, it will continue trying to sink it. Random
	   means "random ship placement" and "random ship shooting".
	   Code is kind of messy :-/
 
***************************************************************/

// Inclusion guard
#ifndef __SHOOTERPLAYER_H_
#define __SHOOTERPLAYER_H_

// Includes
#include "Player.h"
#include "Board.h"

class ShooterPlayer : public Player
{
public:

	// Required to implement
	ShooterPlayer(int BoardWidth, int BoardHeight);

	~ShooterPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Setup(queue<Ship> *Ships);

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

	// Board to prevent shooting at the same position
	bool *Board;

	// The list of the last successful shots
	int HitState;				// State of targeting: 0 is searching, 1 is going through all N,E,S,W
	int HitSource[2];			// The initial hit
	int HitDir;					// The direction we are searching 0 = N, 1 = E, etc...

};

// End of inclusion guard
#endif

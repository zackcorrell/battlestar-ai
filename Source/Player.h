/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Player.h
 Desc: A pure virtual class that describes the basic functions
       needed to implement for a player (AI or user based). This
	   file also includes all ship descriptions and board event
	   enumerations. This class is called by the Game manager.
	   First Setup() is called to setup the board. After there
	   is a loop that asks each player to Shoot(...) and returns
	   the result in Shot(...). It is up to the implementation
	   to deal with internal data support. Reset() *should* be
	   called to deal with resetting the internals of the class.
 
***************************************************************/

// Inclusion guard
#ifndef __PLAYER_H_
#define __PLAYER_H_

// Includes
#include "Util.h"
#include "Ships.h"

class Player
{
public:

	// Constructor takes and saves a name as well as board size
	Player(char* Name, int BoardWidth, int BoardHeight);

	// Destruct or
	~Player();

	// Returns a pointer to the name
	char* GetName();

	// Need to implement: Reset for a new game
	virtual void Reset() = NULL;

	// Need to implement: First called when a new game is created, returns a queue of ships and position pairs
	virtual void Setup(queue<Ship> *Ships) = NULL;

	// Need to implement: Shoot a target an x and y position and shoot
	virtual void Shoot(int *x, int *y) = NULL;

	// Result of shot; The result of the shot is returned. Called right after a Shoot is called
	virtual void ShootResult(int x, int y, ShotState state) = NULL;

protected:

	// Board size
	int BoardWidth, BoardHeight;

private:

	// Name buffer
	char* PlayerName;

};

// End of inclusion guard
#endif

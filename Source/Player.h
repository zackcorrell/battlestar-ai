/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Player.h
 Desc: A base class that describes the basic functions
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
#include "Board1.h"

// An enum of the current targeting 
enum TargetingState
{
	Searching = 0,
	Targeting,
	Locked
};

// Base player class
class Player
{
public:

	// Constructor takes and saves a name as well as board size
	Player(char* Name, int Board1Width, int Board1Height);

	// Destructor
	~Player();

	// Returns a pointer to the name
	char* GetName();

	// Need to implement: Reset for a new game
	virtual void Reset();

	// Need to implement: Given a valid Ship buffer of ShipCount size, fill in with valid ships
	// Default behavior: Random
	virtual void Setup(Ship *Ships, int ShipCount);

	// Nice little static global
	static void SetupStatic(Ship *Ships, int ShipCount, int Board1Width, int Board1Height);

	// Need to implement: Shoot a target an x and y position and shoot
	virtual void Shoot(int *x, int *y);

	// Result of shot; The result of the shot is returned. Called right after a Shoot is called
	virtual void ShootResult(int x, int y, ShotState state);

	// Result of enemy's shot; It gives the result of when the enemy shoots at you
	virtual void EnemyResult(int x, int y, ShotState state);

protected:

	// Add a given queue to the placement board
	// Assumes the given list is from low to high ship length
	void AddShipsStat(Ship *Ships, int ShipCount);

	// Print ship stat
	void PrintStat();

	// Board1 to keep placement history
	int *PlacementBoard1[5];

	// Board1 size
	int Board1Width, Board1Height;

private:

	// Name buffer
	char* PlayerName;

};

// End of inclusion guard
#endif

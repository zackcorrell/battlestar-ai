/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Board.h
 Desc: A standard board of Battleship. Usefull for the Game class,
       but not that usefull for use in Player instances.
 
***************************************************************/

// Inclusion guard
#ifndef __BOARD_H_
#define __BOARD_H_

#include "Util.h"
#include "Ships.h"

class Board
{
public:

	// Constructor
	Board(queue<Ship> *Ships, int BoardWidth, int BoardHeight);

	// Destructor
	~Board();

	// Get a board state
	ShotState GetState(int x, int y);

	// Set a board state
	void SetState(int x, int y, ShotState State);

	// Returns true if this board has a winning state
	bool ValidateWin();

	// Print data to screen
	void Print();

	// Helpfull static function to determine ship-ship collisions
	// Returns true if the ships list and newship (if given) don't collidare and are in the board size
	// Send NULL to *NewShip if you just want to validate just the queue set
	// If the given buffer is not null, this function will write to that memory
	static bool ValidateShip(queue<Ship> *ShipList, Ship* NewShip, int Width, int Height, ShotState* GivenBuffer = NULL);

private:

	// Board data
	int BoardWidth, BoardHeight;
	ShotState *BoardData;
};

// End of inclusion guard
#endif

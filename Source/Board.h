/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Board.h
 Desc: An interface to a standard board of Battleship.
 
***************************************************************/

// Inclusion guard
#ifndef __BOARD_H_
#define __BOARD_H_

#include <queue>
#include <stdio.h>
#include "Ships.h"

using namespace std;

class Board
{
public:

	// Constructor
	Board(queue<Ship> *Ships);

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

private:

	// Board data
	static const int BoardWidth = 10;
	static const int BoardHeight = 10;
	ShotState BoardData[BoardWidth][BoardHeight];
};

// End of inclusion guard
#endif

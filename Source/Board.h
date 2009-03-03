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
	Board(int BoardWidth, int BoardHeight);

	// Destructor
	~Board();

	// Add ships onto board
	void AddShips(Ship *ShipsList, int ShipCount);

	// Get a board state
	ShotState GetState(int x, int y);

	// Set a board state
	void SetState(int x, int y, ShotState State);

	// Hit a ship (Will update the ShipsList)
	void HitShip(int x, int y);

	// Returns the number of sunk ships
	int GetSunkCount();

	// Print data to screen
	void Print();

	// Helpfull static function to determine ship-ship collisions
	// Params: *TempShip is an array of ShipCount size, width and height are the board's width and height
	// Returns true if the given ship is valid within this board
	static bool ValidateShips(Ship *ShipsList, int ShipCount, int Width, int Height);

private:

	// Board data
	int BoardWidth, BoardHeight;
	ShotState *BoardData;

	// Ship list
	Ship ShipsList[5];
};

// End of inclusion guard
#endif

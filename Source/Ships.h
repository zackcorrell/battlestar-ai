/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Ships.h
 Desc: Defines all ship data. Also defined a shot state.
 
***************************************************************/

// Inclusion guard
#ifndef __SHIPS_H_
#define __SHIPS_H_

// Define the ship types
typedef int ShipType;
const ShipType AircraftCarrier =	5;
const ShipType Battleship =			4;
const ShipType Cruiser =			3;
const ShipType Submarine =			3;
const ShipType Destroyer =			2;

// Define directions
enum Direction { North, East, South, West };

// Define a ship structure
struct Ship
{
	// Constructor (Defaults to invalid data, so make sure you pass some params)
	Ship(ShipType type = Destroyer, int x = 0, int y = 0, Direction direction = North)
	{
		// Save ship type
		Type = type;

		// Initialize ship position
		for(int i = 0; i < (int)Type; i++)
		{
			// North
			if(direction == North)
			{ this->x[i] = x; this->y[i] = y - i; }

			// East
			else if(direction == East)
			{ this->x[i] = x + i; this->y[i] = y; }

			// South
			else if(direction == South)
			{ this->x[i] = x; this->y[i] = y + i; }

			// West
			else if(direction == West)
			{ this->x[i] = x - i; this->y[i] = y; }
		}

		// Default hit state to false
		for(int i = 0; i < (int)Type; i++)
			Hit[i] = false;
	}

	// Returns true if the ship has sunk
	bool IsSunk()
	{
		// For each hit position, return false if any part isn't sunk yet
		for(int i = 0; i < (int)Type; i++)
		{
			if(Hit[i] == false)
				return false;
		}

		// All pieces sunk
		return true;
	}

	// Internal public data
	ShipType Type;			// The ship type
	int x[5], y[5];			// Ship positions (occupancy grid of (x,y) over length Type)
	bool Hit[5];			// If true, that position has been hit
};

// Shot / board element state
enum ShotState
{
	// Before events:
	StateEmpty,				// No shot state
	StateShip,				// There is a ship, but still hidden, at this location

	// After events:
	StateMiss,				// There is just water in this location
	StateHit,				// There is a ship, and it has been hit, at this location
};

// End of inclusion guard
#endif

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
	ShipType ship;			// The ship type
	int x, y;				// Ship position
	Direction direction;	// Ship direction
};

// Shot / board element state
enum ShotState {
	// Before events:
	StateEmpty,				// No shot state
	StateShip,				// There is a ship, but still hidden, at this location
	// After events:
	StateMiss,				// There is just water in this location
	StateHit,				// There is a ship, and it has been hit, at this location
};

// End of inclusion guard
#endif

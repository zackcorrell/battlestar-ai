/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: GAPlacement.h
 Desc: A placement algorithm based on the monte-carlo method.
 
***************************************************************/

// Inclusion guard
#ifndef __GAPLACEMENT_H_
#define __GAPLACEMENT_H_

// Includes
#include "Util.h"
#include "Ships.h"
#include "Board1.h"

// The value of a single hit; a board is initialized as this size
#define HIT_UNIT 10.0

// Placement logic
class GAPlacement
{
public:

	// Loads file, if possible
	GAPlacement(char *EnemyName, int Board1Width, int Board1Height);

	// Write out to file
	~GAPlacement();

	// Place enemy shot onto loaded board
	void EnemyShootsAt(int x, int y);

	// Return shop placement (Based on the monte-carlo method)
	void Setup(Ship *Ships, int ShipCount);

private:

	// Places a shot only if possible, adds value to element
	void PlaceShot(int x, int y, double value);

	// Return placement shot density
	double GetShotDensity(int x, int y);

	// Density board
	double *Board1Data;		// Enemy shot placement; 1.0 per shot (Shot density map)
	int Width, Height;

	// Filename used with the current opponent
	char FileName[128];
};

// End of inclusion guard
#endif

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: GASinking.h
 Desc: The sinking AI which is based on a genetic program.
 
***************************************************************/

// Inclusion guard
#ifndef __GASINKING_H_
#define __GASINKING_H_

// Includes
#include "Util.h"
#include "Ships.h"
#include "Board.h"
#include "GASinkingGene.h"

// Maximum gene pool size
#define GA_MAX_POOL 20

// Sinking management
class GASinking
{
public:

	// Build up gene pool
	GASinking(int BoardWidth, int BoardHeight, char *OpponentName = NULL);

	// Release all data and save best gene to drive
	~GASinking();

	// Save enemy board placement
	void SaveEnemyBoard(Ship *ShipsList, int ShipCount);

	// ...
	void Update();

private:

};

// End of inclusion guard
#endif

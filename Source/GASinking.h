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
#define GA_MAX_POOL 20 // Multiple of 2

// Sinking management
class GASinking
{
public:

	// Build up gene pool
	GASinking(int BoardWidth, int BoardHeight, char *OpponentName);

	// Release all data and save best gene to drive
	~GASinking();

	// Save enemy board placement (Used for gene fitness management)
	void SaveEnemyBoard(Ship *ShipsList, int ShipCount);

	// Update the entire gene pool by applying our gene-fitness and breeding functions
	// Prepare our main gene for the next round
	void Update();

	// Run through the current gene
	// Logic: Call this function and check the returned GARunState,
	// and if it is a request, fill out the given params correctly
	// and if it is a post-shot status update, fill out the given params correctly
	GARunState Run(int *DataX, int *DataY, bool Hit);

	// Get a pointer to the best gene
	GASinkingGene *GetBest();

private:

	// Gene pool
	GASinkingGene *GenePool[GA_MAX_POOL];

	// Board size
	int BoardWidth, BoardHeight;

	// Enemy name
	char OpponentName[128];

};

// End of inclusion guard
#endif

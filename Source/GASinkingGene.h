/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: GASinkingGene.h
 Desc: The sinking GP gene and related supporting data/functions.
 
***************************************************************/

// Inclusion guard
#ifndef __GASINKINGGENE_H_
#define __GASINKINGGENE_H_

// Includes
#include "Util.h"
#include "Player.h" // Included for "TargetingState"
#include "Board.h" // For simulations

// Maximum gene pool size
#define GA_MAX_POOL 20

// Maximum instructions in a section of code
#define GA_MAX_INSTRUCTIONS 20

// Total number of instructions
#define GA_TOTAL_INSTRUCTIONS 16

// The amount of enemy boards to save
#define GA_BOARD_SAVE_COUNT 10

// The amount of instructions we run before we consider this a "lame" gene
#define GA_FAILURE_COUNT 100

// Gene state (For state machine design)
typedef TargetingState GAState;

// Gene instruction enumeration
enum GAInstruction
{
	Target = 0,	// Place a valid shot into TargetPos
	Shoot,		// Shoot at said position
	MoveFwd,	// Move forward in the current direction
	RandDir,	// Random direction
	VertDir,	// Shoot at a vertical direction
	HorzDir,	// Shoot at a horizontal direction
	SavePos,	// Save a position
	LoadPos,	// Load a position
	SetTrue,	// Set tempflag to true
	SetFalse,	// Set tempflag to false
	IfHit,		// If targethit to true
	IfMiss,		// If targethit to false
	IfTrue,		// If temphit to true
	IfFalse,	// If temphit to false
	Jump,		// Jumps to the next state
	Nop,		// No operation
};

// GA Run state; A method of handeling internal intterupts to wait for external data to be recieved..
enum GARunState
{
	GetShot,	// Ask for a shot; Takes from x and y params on next call
	SetShot,	// Place a shot; Posts x and y via params, for use now
	GeneFailure,// Internal error; Gene is lame
};

// Gene register machine with instructions
class GASinkingGene
{

public:

	// Constructor
	GASinkingGene();

	// Move all nop-instructions down
	void Clean();

	// Run the current gene; Returns on interrupt and posts/recieves data via params
	GARunState Run(int *DataX, int *DataY, bool Hit);

	// Fitness value of the given gene
	static int FitnessValue(GASinkingGene *Gene);

	// Breed two genes together and produce and post into the given gene data
	static void Breed(GASinkingGene *GeneA, GASinkingGene *GeneB);

	// Run through a given game, returning the number of shots
	static int Simulate(GASinkingGene *Gene, int Width, int Height, Ship *ShipsList, int ShipCount);

private:

	// Registers
	int TargetPos[2];		// Target position (x, y)
	int TempPos[2];			// Temporary position (x, y)
	Direction TargetDir;	// Target direction (N, E, S, W)
	bool TargetHit;			// Hit return state (Turns true on sucessful shot)
	bool TempHit;			// Boolean flag

	// Internal Registers
	int ProgramCounter;		// The index of the current instruction
	GAState State;			// Current state of the program
	bool DirUsed[4];		// Directions already used..

	// Grow the counter correctly
	void GrowCounter();

	// Reset registers
	void ResetRegisters();

public:

	// Program instructions
	GAInstruction Instructions[3][GA_MAX_INSTRUCTIONS]; // For all three states
};

// End of inclusion guard
#endif

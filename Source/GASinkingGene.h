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

// The amount of simulations to cary out in a fitness function for the GA sinking gene
#define GA_SIMULATION_COUNT 100

// The amount of instructions we run before we consider this a "lame" gene
#define GA_FAILURE_COUNT 100

// Gene state (For state machine design)
typedef TargetingState GAState;

// Gene instruction enumeration
enum GAInstruction
{
	Target = 0,	// 0  Place a valid shot into TargetPos
	Shoot,		// 1  Shoot at said position
	MoveFwd,	// 2  Move forward in the current direction
	RandDir,	// 3  Random direction
	VertDir,	// 4  Shoot at a vertical direction
	HorzDir,	// 5  Shoot at a horizontal direction
	SavePos,	// 6  Save a position
	LoadPos,	// 7  Load a position
	SetTrue,	// 8  Set tempflag to true
	SetFalse,	// 9  Set tempflag to false
	IfHit,		// 10 If targethit to true
	IfMiss,		// 11 If targethit to false
	IfTrue,		// 12 If temphit to true
	IfFalse,	// 13 If temphit to false
	Jump,		// 14 Jumps to the next state
	Nop,		// 16 No operation
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

	// Fitness value of the given gene (Takes a copy so the given isn't affected)
	static int FitnessValue(GASinkingGene Gene);

	// Run through a given game, returning the number of shots made (Does affect the given gene)
	static int Simulate(GASinkingGene *Gene);

	// Breed two genes together and produce and post into the given gene data
	static void Breed(GASinkingGene *GeneA, GASinkingGene *GeneB);

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

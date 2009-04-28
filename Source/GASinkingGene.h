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
#define GA_TOTAL_INSTRUCTIONS 17

// The amount of enemy boards to save
#define GA_BOARD_SAVE_COUNT 10

// The amount of simulations to cary out in a fitness function for the GA sinking gene
#define GA_SIMULATION_COUNT 1000

// The amount of sum game count
#define GA_GAME_SIMULATION_COUNT 1000

// The amount of instructions we run before we consider this a "lame" gene
#define GA_FAILURE_COUNT 100

// The mutation rate (from 0 - 100)
#define GA_MUTATION_RATE 10

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
	OppDir,		// 6  Flip direction
	SavePos,	// 7  Save a position
	LoadPos,	// 8  Load a position
	SetTrue,	// 9  Set tempflag to true
	SetFalse,	// 10  Set tempflag to false
	IfHit,		// 11 If targethit to true
	IfMiss,		// 12 If targethit to false
	IfTrue,		// 13 If temphit to true
	IfFalse,	// 14 If temphit to false
	Jump,		// 15 Jumps to the next state
	Nop,		// 16 No operation
};

// String list that's nice to use for outputting messages more clear
static char GAInstructionStr[GA_TOTAL_INSTRUCTIONS][32] =
{
	"Target",
	"Shoot",
	"MoveFwd",
	"RandDir",
	"VertDir",
	"HorzDir",
	"OppDir",
	"SavePos",
	"LoadPos",
	"SetTrue",
	"SetFalse",
	"IfHit",
	"IfMiss",
	"IfTrue",
	"IfFalse",
	"Jump",
	"Nop",
};

// GA Run state; A method of handeling internal intterupts to wait for external data to be recieved..
enum GARunState
{
	GetShot,	// Ask for a shot; Takes from x and y params on next call
	SetShot,	// Place a shot; Posts x and y via params, for use now
	GeneFailure,// Internal error; Gene is lame
	Nothing,	// Do nothing
};

static char GARunStateStr[4][32] =
{
	"GetShot",
	"SetShot",
	"GeneFailure",
	"Nothing",
};

// Gene register machine with instructions
class GASinkingGene
{

public:

	// Constructor
	GASinkingGene();

	// Destructor, write back out to memory
	~GASinkingGene();

	// Load from memory
	void Load(char *EnemyName);

	// Save this gene into memory
	void Save(char *EnemyName);

	// Move all nop-instructions down
	void Clean();

	// Run the current gene; Returns on interrupt and posts/recieves data via params
	GARunState Run(int *DataX, int *DataY, bool Hit);

	// Run through a single instruction
	GARunState Step(GAInstruction op, int *DataX, int *DataY, bool Hit);

	// Fitness value of the given gene (Takes a copy so the given isn't affected)
	static int FitnessValue(GASinkingGene Gene, Ship *Ships, int ShipCount);

	// Breed two genes together and produce and post into the given gene data
	static void Breed(GASinkingGene *GeneA, GASinkingGene *GeneB);

	// Reset registers
	void ResetRegisters();

private:

	// Run through a given game, returning the number of shots made (Does affect the given gene)
	static int Simulate(GASinkingGene *Gene, Ship *Ships, int ShipCount);

	// Grow the counter correctly
	void GrowCounter();

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

	// Program instructions
	GAInstruction Instructions[3][GA_MAX_INSTRUCTIONS]; // For all three states
};

// End of inclusion guard
#endif

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: GAPlayer.h
 Desc: The interface between the GenesManager (a GA/GP solution
       to the game of battleship) to the battleship player
	   interface for the game simulator.
 
***************************************************************/

// Inclusion guard
#ifndef __GAPLAYER_H_
#define __GAPLAYER_H_

// Includes
#include "Player.h"
#include "Board.h"

// Gene register machine
struct GARegisters
{
	int TargetPos[2];		// Target position
	int TempPos[2];			// Temporary position
	Direction  TargetDir;	// Target direction
	bool TargetHit;			// Hit return state
	bool TempHit;			// Boolean flag
};

// Max gene count
#define GA_INSTRUCTION_COUNT 15

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
	Nop,		// No operation
};

// GA Gene structure
struct GAGene
{
	// Register machine
	GARegisters Registers;

	// 50 instructions
	GAInstruction Instructions[50];

	// The size of the three sections of code
	int InstructionSizes[3];
};

// Player class
class GAPlayer : public Player
{
public:

	// Required to implement
	GAPlayer(int BoardWidth, int BoardHeight);

	~GAPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

	// Gene pool (Max is 20)
	GAGene GenePool[20];

};

// End of inclusion guard
#endif

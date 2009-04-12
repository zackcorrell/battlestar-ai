/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GAPlayer.h"

GAPlayer::GAPlayer(int BoardWidth, int BoardHeight)
	: Player("GAPlayer AI", BoardWidth, BoardHeight)
{
	// Since this is a new opponent,
	// initialize the gene pool to be empty
	for(int i = 0; i < 20; i++)
	{
		// Initialize the registers
		GenePool[i].Registers.TargetPos[0] = 0;
		GenePool[i].Registers.TargetPos[1] = 0;
		GenePool[i].Registers.TempPos[0] = 0;
		GenePool[i].Registers.TempPos[1] = 0;
		GenePool[i].Registers.TempPos[0] = 0;
		GenePool[i].Registers.TargetDir = North;
		GenePool[i].Registers.TargetHit = false;
		GenePool[i].Registers.TargetHit = false;

		// Choose random instructions 
		for(int j = 0; j < 50; j++)
		{
			GenePool[i].Instructions[j] = GAInstruction(rand() % GA_INSTRUCTION_COUNT);
		}

		// Set the size to zero
		for(int j = 0; j < 3; j++)
		{
			if(j == 0)
				GenePool[i].InstructionSizes[j] = 10;
			else
				GenePool[i].InstructionSizes[j] = 20;
		}

		// Move all nops to the bottom of each subection
		for(int j = 0; j < 3; j++)
		{
			// For each length of section 10, 20, 20
			int length = 20;
			if(i == 0)
				length = 10;

			// For the length, try to move nops down
			for(int k = 0; k < length; k++)
			{
				// Move from that 
				// NEED TO FINISH UP!
			}
		}
	}

}

GAPlayer::~GAPlayer()
{
	// Nothing to do...
}

void GAPlayer::Reset()
{
	// ...
}

void GAPlayer::Shoot(int *x, int *y)
{
	// Nothing to do...
}

void GAPlayer::ShootResult(int x, int y, ShotState state)
{
	// Nothing to do...
}

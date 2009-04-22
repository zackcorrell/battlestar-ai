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
	// Gene sinking debuging stuff..
	int counter = 0;
	for(int j = 0; j < INT_MAX; j++)
	{
		GASinkingGene temp;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < GA_MAX_INSTRUCTIONS; j++)
				temp.Instructions[i][j] = (GAInstruction)(rand() % GA_TOTAL_INSTRUCTIONS);
		}
		temp.Clean();
		if(GASinkingGene::FitnessValue(temp) == 0)
			counter++;

		printf("%d\t%d\n", j, counter);
	}
}

GAPlayer::~GAPlayer()
{
	// ...
}

void GAPlayer::Reset()
{
	// ...
}

void GAPlayer::Setup(Ship *Ships, int ShipCount)
{
	// ...
}

void GAPlayer::Shoot(int *x, int *y)
{
	// ...
}

void GAPlayer::ShootResult(int x, int y, ShotState state)
{
	// ...
}

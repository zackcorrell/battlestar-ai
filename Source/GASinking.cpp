/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GASinking.h"

GASinking::GASinking(int BoardWidth, int BoardHeight, char *OpponentName)
{
	// Save size
	this->BoardWidth = BoardWidth;
	this->BoardHeight = BoardHeight;

	// Copy over opponent name
	strcpy(this->OpponentName, OpponentName);

	// Instance each gene with the opponent name
	for(int i = 0; i < GA_MAX_POOL; i++)
		GenePool[i].Load(OpponentName);
}

GASinking::~GASinking()
{
	// Save the best gene
	GenePool[0].Save(OpponentName);
}

void GASinking::Update()
{
	// Have the top two saved onto all others
	for(int i = 2; i < GA_MAX_POOL; i += 2)
	{
		// Copy from the top two to these index
		memcpy((void*)(GenePool + i), (void*)(GenePool + 0), sizeof(GASinkingGene));
		memcpy((void*)(GenePool + i + 1), (void*)(GenePool + 1), sizeof(GASinkingGene));
	}

	// Start breeding
	for(int i = 2; i < GA_MAX_POOL; i += 2)
		GASinkingGene::Breed(GenePool + i, GenePool + i + 1);

	// Order these genes based on fitness
	int Fitness[GA_MAX_POOL];
	for(int i = 0; i < GA_MAX_POOL; i++)
		Fitness[i] = GASinkingGene::FitnessValue(GenePool[i]);

	// Find the best and place it in the first and seccond slots correctly
	int BestFitness = INT_MAX;
	int BestIndex = 0;

	for(int j = 0; j < 2; j++)
	{
		// Find the best
		for(int i = j; i < GA_MAX_POOL; i++)
		{
			if(BestFitness > Fitness[i])
			{
				BestFitness = Fitness[i];
				BestIndex = i;
				
			}
		}

		// Once we have the best move it to the top
		memcpy((void*)(GenePool + j), (void*)(GenePool + BestIndex), sizeof(GASinkingGene));
	}
}

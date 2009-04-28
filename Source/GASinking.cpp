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

	// Instance each gene
	for(int i = 0; i < GA_MAX_POOL; i++)
		GenePool[i] = new GASinkingGene();

	// Load the base or the opponent name data file
	for(int i = 0; i < GA_MAX_POOL; i++)
		GenePool[i]->Load(OpponentName);
}

GASinking::~GASinking()
{
	// Release all genes
	for(int i = 0; i < GA_MAX_POOL; i++)
		delete GenePool[i];
}

void GASinking::SaveEnemyBoard(Ship *ShipsList, int ShipCount)
{
	// Attempt to write out to a file formated as: abc123.dat4
	char FileName[128];
	strcpy(FileName, OpponentName);
	strcat(FileName, ".dat4");

	// Write to file
	ofstream File(FileName);
	if(File.fail())
		return;

	for(int i = 0; i < ShipCount; i++)
	{
		File << int(ShipsList[i].Type) << " ";
		File << int(ShipsList[i].direction) << " ";
		File << ShipsList[i].x[0] << " " << ShipsList[i].y[0] << endl;
	}

	File.close();
}

void GASinking::Update()
{
	// Load shiplist from disk
	char FileName[128];
	strcpy(FileName, OpponentName);
	strcat(FileName, ".dat4");

	// Write to file
	ifstream File(FileName);
	Ship Ships[5];

	if(File.fail())
	{
		// Choose static ships
		Player::SetupStatic(Ships, 5, 10, 10);
	}
	else
	{
		// Ships list
		Ship Ships[5];
		int Type, direction, x, y;

		// Read in 5 ships..
		for(int i = 0; i < 5; i++)
		{
			File >> Type >> direction >> x >> y;
			Ships[i].SetData((ShipType)Type, x, y, (Direction)direction);
		}

		// Close file
		File.close();
	}

	// Save the top two, release the rest, and place the rest as copies of the top two
	for(int i = 2; i < GA_MAX_POOL; i += 2)
	{
		// Release this pair
		delete GenePool[i + 0];
		delete GenePool[i + 1];

		// Copy the first two into this pisition
		memcpy((void*)(GenePool[i + 0]), (void*)(GenePool[0]), sizeof(GASinkingGene));
		memcpy((void*)(GenePool[i + 1]), (void*)(GenePool[1]), sizeof(GASinkingGene));

		// Breed these two genes
		GASinkingGene::Breed(GenePool[i + 0],GenePool[i + 1]);
	}

	// Order these genes based on fitness
	int Fitness[GA_MAX_POOL];
	for(int i = 0; i < GA_MAX_POOL; i++)
		Fitness[i] = GASinkingGene::FitnessValue(*GenePool[i], Ships, 5);

	// Find the best and place it in the first and seccond slots correctly
	int BestFitness = INT_MAX;
	int BestIndex = 0;

	for(int j = 0; j < 2; j++)
	{
		// Find the best
		for(int i = j; i < GA_MAX_POOL; i++)
		{
			// Select the best
			if(BestFitness > Fitness[i])
			{
				BestFitness = Fitness[i];
				BestIndex = i;
			}
		}

		// Once we have the best move it to the top
		memcpy((void*)(GenePool[j]), (void*)(GenePool[BestIndex]), sizeof(GASinkingGene));
	}
}

GARunState GASinking::Run(int *DataX, int *DataY, bool Hit)
{
	// Use the top, best, gene
	return GenePool[0]->Run(DataX, DataY, Hit);
}

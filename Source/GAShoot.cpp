/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
***************************************************************/

#include "GAShoot.h"	

GAShoot::GAShoot(double* target) : genePool(target) {}
GAShoot::GAShoot(char* EnemyName) : genePool()
{
	// Save enemy name
	strcpy(this->EnemyName, EnemyName);

	// Test if there is already a log for this enemy
	char Temp[128];
	strcpy(Temp, EnemyName);
	strcat(Temp, ".dat2");
	ofstream File(Temp);
	if(File.fail())
		genePool.load("Default.dat2");
	else
		genePool.load(Temp);
}

GAShoot::~GASoot()
{
	char Temp[128];
	strcpy(Temp, EnemyName);
	strcat(Temp, ".dat2");
	save(Temp);
}

void GAShoot::getTarget(int *x, int *y)
{
	genePool.getTarget(x, y, &board);
}

void GAShoot::SetShot(int x, int y)
{
	board.set(x, y, 1);
}

//provides runGenerations
void GAShoot::runGeneration()
{
	genePool.advance();
}
void GAShoot::runGenerations(int n)
{
	for(int i = 0; i < n; i++)
		genePool.advance();
}

//provides save/load
void GAShoot::save(char* filename)
{
	genePool.save(filename);
}
void GAShoot::load(char* filename)
{
	genePool.load(filename);
}

double GAShoot::bestFitness()
{
	return genePool.bestFitness();
}
double* GAShoot::bestDist()
{
	return genePool.bestDist();
}

Gene GAShoot::getPerfect()
{
	return genePool.getPerfect();
}
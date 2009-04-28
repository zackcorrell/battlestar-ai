/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
***************************************************************/

#include "GAShoot.h"	

GAShoot::GAShoot(double* target) : genePool(target) {}
GAShoot::GAShoot(char* filename) : genePool()
{
	genePool.load(filename);
}

void GAShoot::getTarget(int *x, int *y, Board2* board)
{
	genePool.getTarget(x, y, board);
	
	//todo: implement
	//*x = 0;
	//*y = 0;
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
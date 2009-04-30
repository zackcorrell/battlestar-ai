/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
***************************************************************/

#include "GAShoot.h"	

GAShoot::GAShoot(double* target) : genePool(target), board()
{
	strcpy(EnemyName, "Default");
}
GAShoot::GAShoot(char* EnemyName) : genePool(), board()
{
	// Save enemy name
	strcpy(this->EnemyName, EnemyName);

	// Test if there is already a log for this enemy
	char Temp[128];
	strcpy(Temp, EnemyName);
	strcat(Temp, ".dat2");
	FILE* fp = fopen(Temp, "r");
	if(fp == NULL)
	{
		genePool.load("Default.dat2");
	}
	else
	{
		fclose(fp);
		genePool.load(Temp);
	}

	runGenerations(25);
}

GAShoot::~GAShoot()
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

void GAShoot::setShot(int x, int y)
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
Gene GAShoot::getBest()
{
	return genePool.best();
}

void GAShoot::saveHit(int x, int y)
{
	genePool.saveHit(x, y);
}

void GAShoot::printBoard()
{
	board.print();
}
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
	/*// Save enemy name
	strcpy(this->EnemyName, EnemyName);

	// Test if there is already a log for this enemy
	char Temp[128];
	strcpy(Temp, EnemyName);
	strcat(Temp, ".dat2");
	ofstream File(Temp);
	if(File.fail())
		genePool.load("Default.dat2");
	else
		genePool.load(Temp);*/

	////Begin last-ditch code
	double linearizedCount[100];
	for(int i = 0; i < 100; linearizedCount[i++] = 0);

	Ship Ships[5];
	for(int i = 0; i < 100000; i++)
	{
		Player::SetupStatic(Ships, 5, 10, 10);
		Board b(10, 10);
		b.AddShips(Ships, 5);

		for(int j =  0; j < 100; j++)
		{
			if(b.GetState(j % 10, j / 10) == StateShip)
				linearizedCount[j] += 1;
		}
	}
	
	double step = 100 / (2 * PI);
	for(int i = 0; i < 100; i++)
	{
		linearizedCount[i] = sin(i/step) + cos(i/step) + 20;
	}

	for(int i = 0; i < 100; linearizedCount[i++] /= 10000);


	double target[100];
	memcpy(target, linearizedCount, 100 * sizeof(double));
	runGenerations(25);

	genePool = ShootGenePool(target);
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
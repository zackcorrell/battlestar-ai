/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
 File: GAShoot.h
 Desc: The interface class for the Shooting GA.
 
***************************************************************/

#ifndef GA_SHOOT_H
#define GA_SHOOT_H

#include "ShootGenePool.h"
#include "board2.h" //todo:remove

class GAShoot
{
	ShootGenePool genePool;

	// Enemy name
	char EnemyName[128];

	// Enemy shot placement
	Board2 board;

public:

	GAShoot(double* target);
	GAShoot(char* EnemyName);
	~GAShoot();

	//Get a random square based on the data
	void getTarget(int *x, int *y);

	// Say that this was a shot-at position
	void setShot(int x, int y);

	//Run generations of the GA
	void runGeneration(); //Run one generation
	void runGenerations(int n);

	//Save and load data
	void save(char* filename);
	void load(char* filename);

	//Print Best Fitness
	double bestFitness();
	double* bestDist();

	Gene getPerfect();
	Gene getBest();

	void saveHit(int x, int y);

	void printBoard();
};

#endif

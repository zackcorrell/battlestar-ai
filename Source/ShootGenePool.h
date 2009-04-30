/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
 File: ShootGenePool.h
 Desc: Implements the Shooting GA.
 
***************************************************************/

#ifndef SHOOT_GENE_POOL_H
#define SHOOT_GENE_POOL_H

#include "ShootGene.h"
#include <cstdio>
#include "board2.h" //todo:remove

#define INCREMENT 1;

class ShootGenePool
{
	Gene pool[100];
	double target[100];
	double targetAvg;

public:
	ShootGenePool() {}
	ShootGenePool(double* target)
	{
		memcpy(this->target, target, 100 * sizeof(double));

		targetAvg = 0.0;
		for(int i = 0; i < 100; i++)
			targetAvg += target[i];
		targetAvg /= 100.0;
		
		for(int i = 0; i < 100; i++)
			pool[i] = Gene(/*randFloat() * */targetAvg);
	}

	void advance();
	Gene best();
	void save(char* filename);
	void load(char* filename);
	
	void getTarget(int* x, int* y, Board2* board);

	double bestFitness();
	double* bestDist();

	Gene getPerfect();

	void saveHit(int x, int y);

private:
	void sort();
};

#endif
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

class GAShoot
{
	shootGenePool genePool;

public:

	GAShoot();
	GAShoot(char* filename);

	//provides getrandom (int* int*)
	void getTarget(int *x, int *y);

	//provides runGenerations
	void runGenerations();
	void runGenerations(int n);

	//provides save/load
	void save(char* filename);
	void load(char* filename);
};

#endif
#ifndef GA_SHOOT_H
#define GA_SHOOT_H

#include "ShootGenePool.h"

//interfacing class for shooting

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
#ifndef SHOOT_GENE_POOL_H
#define SHOOT_GENE_POOL_H

#include "gene.h"

class ShootGenePool
{
	Gene pool[100];
	double target[100];

public:
	ShootGenePool(double* target)
	{
		memcpy(this->target, target, 100 * sizeof(double));

		double avg = 0;
		for(int i = 0; i < 100; i++)
			avg += target[i];
		avg /= 100;

		for(int i = 0; i < 100; i++)
			pool[i] = Gene(avg);
		//TODO
	}

	void advance();
	Gene best();

private:
	Gene* getTopTen();
	void sort();
};

#endif
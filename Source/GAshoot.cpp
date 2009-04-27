#include "GAshoot.h"
#include <assert.h>

void sort(Gene* pool);

void ShootGenePool::advance()
{
	Gene nextGen[100];

	memcpy(nextGen, getTopTen(), 10 * sizeof(Gene));

	//for(int i = 0; i < 10; i++)
	//	printf("%f\n", nextGen[i].fitness(target));

	int nextIndex = 10;

	for(int mutate = 0; mutate < 2; mutate++)
		for(int i = 0; i < 10; i++)
			for(int j = i+1; j < 10; j++)
				nextGen[nextIndex++] = Gene::cross(&nextGen[i], &nextGen[j], mutate);

	assert(nextGen[0].fitness(target) == best().fitness(target));

	memcpy(pool, nextGen, 100 * sizeof(Gene));
}

Gene ShootGenePool::best()
{
	double bestFitness = -1;
	int best = 0;

	for(int i = 0; i < 100; i++)
	{
		if(pool[i].fitness(target) > bestFitness)
		{
			bestFitness = pool[i].fitness(target);
			best = i;
		}
	}

	return pool[best];
}

Gene* ShootGenePool::getTopTen()
{
	Gene ten[10];

	sort();

	for(int i = 0; i < 10; ten[i++] = pool[i]);
	
	return ten;
}

void ShootGenePool::sort()
{
	for(int i = 0; i < 10; i++)
	{
		double bestFitness = -1;
		int best = i;
		for(int j = i; j < 100; j++)
		{
			if(pool[j].fitness(target) > bestFitness)
			{
				bestFitness = pool[j].fitness(target);
				best = j;
			}
		}
		Gene temp = pool[i];
		pool[i] = pool[best];
		pool[best] = temp;
	}
}
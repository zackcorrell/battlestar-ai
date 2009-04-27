/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
***************************************************************/

#include "ShootGenePool.h"
#include <assert.h>

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

void ShootGenePool::save(char* filename)
{
	FILE* file = fopen(filename, "w");

	for(int i = 0; i < 100; fprintf(file, "%s",  pool[i++].saveString()));

	fclose(file);
}

void ShootGenePool::load(char* filename)
{
	FILE* file = fopen(filename, "r");

	char buf[128];
	int waveCount = 0;
	int currentGene = 0;
	Harmonic tempWaves[WAVECOUNT];

	while(!feof(file))
	{		
		fgets(buf, 128, file);
		if(strcmp(buf, "\n") == 0)
		{
			pool[currentGene++] = Gene(tempWaves);
			waveCount = 0;
		}
		else
		{
			if(waveCount < WAVECOUNT)
			{
				int alpha, beta, mu, omega;
				sscanf(buf, "%f %d %f %d", &alpha, &mu, &beta, &omega);
				tempWaves[waveCount++] = Harmonic(alpha, mu, beta, omega);
			}
		}
	}

	fclose(file);
}
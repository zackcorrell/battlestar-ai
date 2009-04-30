/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
***************************************************************/

#include "ShootGenePool.h"
#include <assert.h>
#include <iostream>
using namespace std;

void ShootGenePool::advance()
{
	Gene nextGen[100];
	sort();

	memcpy(nextGen, pool, 10 * sizeof(Gene));

	int nextIndex = 10;

	for(int mutate = 0; mutate < 2; mutate++)
		for(int i = 0; i < 10; i++)
			for(int j = i+1; j < 10; j++)
				nextGen[nextIndex++] = Gene::cross(&nextGen[i], &nextGen[j], mutate);

	// Verify that the best gene from the last pool is at least the best gene of the current pool
	assert(nextGen[0].fitness(target) == best().fitness(target));

	memcpy(pool, nextGen, 100 * sizeof(Gene));
	Printf("Shooting: Value of best gene for this advance(): %f\n", best().fitness(target));
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

void ShootGenePool::sort()
{
	for(int i = 0; i < 10; i++)
	{
		double bestFitness = -99999.0;
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

	fprintf(file, "%.4f\n\n", targetAvg);

	for(int i = 0; i < 100; fprintf(file, "%.4f\n", target[i++]));
	fprintf(file, "\n");

	for(int i = 0; i < 100; i++)
	{
		char* str = pool[i].saveString();
		fputs(str, file);//fprintf(file, "%s\n",  pool[i].saveString());
		delete[] str;
	}

	fclose(file);
}

void ShootGenePool::load(char* filename)
{
	ifstream in;
	in.open(filename);
	if(in.fail())
	{
		printf("Could not open ShootGenePool file.\n");
		exit(-1);
	}

	in >> targetAvg;
	
	for(int i = 0; i < 100; i++)
		in >> target[i];

	for(int g = 0; g < 100; g++)
	{
		double mag;
		in >> mag;

		Harmonic tempWaves[WAVECOUNT];
		for(int i = 0; i < WAVECOUNT; i++)
		{
			float a, b; int m, o;
			in >> a; in.get();
			in >> m; in.get();
			in >> b; in.get();
			in >> o;
			tempWaves[i] = Harmonic(a, m, b, o);
		}

		pool[g] = Gene(mag, tempWaves);
	}

	in.close();
	sort();
}

void ShootGenePool::getTarget(int* x, int* y, Board2* board)
{
	double* dist = best().getDist();

	for(int i = 0; i < 100; i++)
	{
		if(board->at(i % 10, i / 10) == 1)
			dist[i] = 0; //set shot places to zero
	}
	double total = 0;
	for(int i = 0; i < 100; total += dist[i++]); //calculate total
	for(int i = 0; i < 100; dist[i++] /= total); //scale by total
	for(int i = 1; i < 100; dist[i] += dist[(i++)-1]); //turn into increasing array
	double rand = randFloat();
	*x = 9, *y = 9;
	for(int i = 0; i < 99; i++) //was /*dist[i] < rand &&*/ <- i think that's wrong
	{
		if(dist[i] > rand)
		{
			*x = i % 10;
			*y = i / 10;

			break;
		}
	}
	
	//Begin fucking filter
	if((*x % 2 == 0 && *y % 2 == 0) || (*x % 2 == 1 && *y % 2 == 1))
		getTarget(x, y, board);

	board->set(*x, *y, 1);
	delete[] dist;

	//todo implement fucking filter
}

double ShootGenePool::bestFitness()
{
	return best().fitness(target);
}

double* ShootGenePool::bestDist()
{
	return best().getDist();
}

Gene ShootGenePool::getPerfect()
{
	double real[100];
	double imaginary[100];

	memcpy(real, target, 100 * sizeof(double));
	for(int i = 0; i < 100; imaginary[i++] = 0);

	DFT(1, 100, real, imaginary);

	double copy[100];
	double high = 0; int highindex = 0;
	int highsine[WAVECOUNT];
	int highcosine[WAVECOUNT];

	memcpy(copy, real, 100 * sizeof(double));
	for(int i = 0; i < WAVECOUNT; i++)
	{
		for(int j = 1; j < 50; j++)
		{
			if(abs(copy[j]) > high)
			{
				high = abs(copy[j]);
				highindex = j;
			}
		}
		highcosine[i] = highindex;
		copy[highindex] = 0;
		high = 0, highindex = 0;
	}

	memcpy(copy, imaginary, 100 * sizeof(double));
	for(int i = 0; i < WAVECOUNT; i++)
	{
		for(int j = 1; j < 50; j++)
		{
			if(abs(copy[j]) > high)
			{
				high = abs(copy[j]);
				highindex = j;
			}
		}
		highsine[i] = highindex;
		copy[highindex] = 0;
		high = 0, highindex = 0;
	}

	Harmonic tempWaves[WAVECOUNT];
	for(int i = 0; i < WAVECOUNT; i++)
		tempWaves[i] = Harmonic(-2*imaginary[highsine[i]], highsine[i], 2*real[highcosine[i]], highcosine[i]);
	Gene fourfit(targetAvg, tempWaves);
	printf("\nPerfect: %f\n", fourfit.fitness(target));

	return fourfit;
}

void ShootGenePool::saveHit(int x, int y)
{
	target[x+y*10] += INCREMENT;
}
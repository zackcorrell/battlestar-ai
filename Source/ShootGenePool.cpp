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

	memcpy(nextGen, getTopTen(), 10 * sizeof(Gene));

	int nextIndex = 10;

	for(int mutate = 0; mutate < 2; mutate++)
		for(int i = 0; i < 10; i++)
			for(int j = i+1; j < 10; j++)
				nextGen[nextIndex++] = Gene::cross(&nextGen[i], &nextGen[j], mutate);

	assert(nextGen[0].fitness(target) == best().fitness(target));

	//for(int i = 0; i < 100; i++)
	//	printf("%f\n", nextGen[i].fitness(target));
	//printf("\n");

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
		double bestFitness = -9999999999;
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
		fputs(pool[i].saveString(), file);//fprintf(file, "%s\n",  pool[i].saveString());

	fclose(file);
}

void ShootGenePool::load(char* filename)
{
	ifstream in;
	in.open(filename);
	char buf[256];
	//while(1)
	//	in.getline(buf, 256);

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
}
/*

	FILE* file = fopen(filename, "r");

	char buf[128];
	int waveCount = 0;
	int currentGene = 0;
	Harmonic tempWaves[WAVECOUNT];
	double magnitude;

	fgets(buf, 128, file);
	sscanf(buf, "%f\n", &targetAvg); //get target avg

	for(int i = 0; i < 100; fscanf(file, "%f\n", target + i++));

	while(!feof(file))
	{		
		fgets(buf, 128, file);
		if(strcmp(buf, "\n") == 0)
		{
			pool[currentGene++] = Gene(tempWaves);
			waveCount = -1;
		}
		else
		{
			if(waveCount = -1)
			{
				sscanf(buf, "%f", &magnitude);
				waveCount++;
			}
			if(waveCount < WAVECOUNT)
			{
				int alpha, beta, mu, omega;
				sscanf(buf, "%f %d %f %d", &alpha, &mu, &beta, &omega);
				tempWaves[waveCount++] = Harmonic(alpha, mu, beta, omega);
			}
		}
	}

	fclose(file);
}*/

void ShootGenePool::getTarget(int* x, int* y, Board2* board)
{
	double* dist = best().getDist();
	for(int i = 0; i < 100; i++)
	{
		if(board->at(i / 10, i % 10) == 1)
			dist[i] = 0; //set shot places to zero
	}
	double total = 0;
	for(int i = 0; i < 100; total += dist[i++]); //calculate total
	for(int i = 0; i < 100; dist[i++] /= total); //scale by total
	for(int i = 1; i < 100; dist[i] += dist[(i++)-1]); //turn into increasing array
	double rand = randFloat();
	*x = 9, *y = 9;
	for(int i = 0; /*dist[i] < rand &&*/ i < 99; i++)
	{
		if(dist[i] > rand)
		{
			*x = i / 10;
			*y = i % 10;

			break;
		}
	}
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
	target[x*10+y] += INCREMENT;
}
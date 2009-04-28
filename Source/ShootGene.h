/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
 File: ShootGene.h
 Desc: Gene class used by ShootGenePool.
 
***************************************************************/

#ifndef GENE_H
#define GENE_H

#include <cstdio>
#include <cstring>
#include "Util.h"
#include "ShootHarmonic.h"
#include "ShootFourier.h"

#define MAX_OF_SCALED_SIN_PLUS_COS 10000 //0.235586 //computed earlier
#define MUTATION_RATE 0.1

class Gene
{
	double magnitude;
	Harmonic waves[WAVECOUNT];

public:
	Gene() //makes random gene
	{
		for(int i = 0; i < WAVECOUNT; i++)
			waves[i] = Harmonic(MAX_OF_SCALED_SIN_PLUS_COS);
	}

	Gene(double magnitude) //makes random gene
	{
		this->magnitude = magnitude;
		for(int i = 0; i < WAVECOUNT; i++)
			waves[i] = Harmonic(MAX_OF_SCALED_SIN_PLUS_COS);
	}

	Gene(Harmonic* waves) //gene with premade harmonics
	{
		memcpy(this->waves, waves, sizeof(Harmonic) * WAVECOUNT);
	}

	Gene(double magnitude, Harmonic* waves) //gene with premade harmonics
	{
		this->magnitude = magnitude;
		memcpy(this->waves, waves, sizeof(Harmonic) * WAVECOUNT);
	}

	double* getDist();
	double fitness(double* dist);
	char* toString();

	static Gene cross(Gene* father, Gene* mother, bool mutate);

	char* saveString();
}; 

#endif
/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
 File: ShootHarmonic.h
 Desc: Harmonic class (sin + cos) used in ShootGene.
 
***************************************************************/

#ifndef HARMONIC_H
#define HARMONIC_H

#include <cstdlib>
#include <limits.h>
#include <cmath>
#include "Util.h"

#define STEP (100.0 / (2.0 * PI))

//a harmonic is a wave of the form alpha * sin(mu * x) + beta * cos(omega * x)
class Harmonic
{
public: //fixme
	double alpha, beta;
	int mu, omega;

public:
	Harmonic()
	{
		alpha = beta = mu = omega = 0;
	}

	Harmonic(double amplitude)
	{
		alpha = amplitude - 2 * randFloat() * amplitude;
		beta = amplitude - 2 * randFloat() * amplitude;
		mu = (rand() % 48) + 1;
		omega = (rand() % 48) + 1;
	}

	Harmonic(double alpha, int mu, double beta, int omega)
	{
		this->alpha = alpha;
		this->mu = mu;
		this->beta = beta;
		this->omega = omega;
	}

	double* getDist();
};

#endif
		
#ifndef HARMONIC_H
#define HARMONIC_H

#include <cstdlib>
#include <limits.h>
#include <cmath>
#include "Util.h"

#define STEP (100 / (2.0 * PI))

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
		
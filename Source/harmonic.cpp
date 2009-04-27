#include "harmonic.h"

double* Harmonic::getDist()
{
	double* dist = new double[100];
	for(int i = 0; i < 100; i++)
		dist[i] = alpha * sin(mu * (i/STEP)) + beta * cos(omega * (i/STEP));
	return dist;
}
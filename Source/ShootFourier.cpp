/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
***************************************************************/

#include "ShootFourier.h"

bool DFT(int direction, int m, double* x1, double* y1)
{
	long i, k;
	double arg;
	double cosarg, sinarg;
	double *x2, *y2;

	x2 = (double*)malloc(m * sizeof(double));
	y2 = (double*)malloc(m * sizeof(double));
	if(x2 == NULL || y2 == NULL)
		return false;

	for(i = 0; i < m; i++) //for all m
	{
		x2[i] = 0;
		y2[i] = 0;
		arg = -direction * 2.0 * PI * (double)i / (double)m; //arg is direction(passed in) * 2pi * iter/total
		for(k = 0; k < m; k++) //for all m
		{
			sinarg = sin(k * arg);        
			cosarg = cos(k * arg);         
			x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
			y2[i] += (x1[k] * sinarg + y1[k] * cosarg);
		}
	}

	/* Copy the data back */
	if (direction == 1) {
		for (i = 0; i < m; i++) {
			x1[i] = x2[i] / (double)m;
			y1[i] = y2[i] / (double)m;
		}
	} else {
		for (i = 0; i < m; i++) {
			x1[i] = x2[i];
			y1[i] = y2[i];
		}
	}

	free(x2);
	free(y2);
	return true;
}

int* selectTop(double* arr) //returns array of size WAVECOUNT with indices of top WAVECOUNT waves
{
	int* top = new int[WAVECOUNT];

	double copy[100];
	double high = 0; int highindex = 0;

	memcpy(copy, arr, 100 * sizeof(double));
	for(int i = 0; i < WAVECOUNT; i++)
	{
		for(int j = 0; j < 50; j++)
		{
			if(abs(copy[j]) > high)
			{
				high = abs(copy[j]);
				highindex = j;
			}
		}
		top[i] = highindex;
		copy[highindex] = 0;
		high = 0, highindex = 0;
	}

	return top;
}
/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Zach Gotsch <zkg5001@psu.edu>
 
 File: ShootFourier.h
 Desc: Implements Fourier method for gene reproduction.
 
***************************************************************/

#ifndef FOURIER_H
#define FOURIER_H

#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Util.h"

bool DFT(int direction, int m, double* x1, double* y1);
int* selectTop(double* arr);

#endif
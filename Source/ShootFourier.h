#ifndef FOURIER_H
#define FOURIER_H

#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Util.h"

bool DFT(int direction, int m, double* x1, double* y1);
int* selectTop(double* arr);

#endif
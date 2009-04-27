#ifndef GLOBALS_H
#define GLOBALS_H

#include <ctime>
#include <cstdlib>
//#include <limits.h>

#define WAVECOUNT 10
#define PI (3.141592654)

static inline double randFloat()
{
	return ((double)rand() / RAND_MAX);
}

#endif
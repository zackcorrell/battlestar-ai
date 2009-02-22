/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Util.h
 Desc: Contains several supporting functions for the program.
       Currently replaces "printf" with an inline function
	   that supports printf and fprintf / logging.
 
***************************************************************/

// Inclusion guard
#ifndef __UTIL_H_
#define __UTIL_H_

// Includes
#include <stdio.h>
#include <cstdlib>
#include <cstdarg>
#include <queue>
#include <time.h>
#include "Main.h"

using namespace std;

// Overload the print function to print appropriately
// If logging is on, print to log file, else if silence is on, don't print to standard io
int Printf(const char *format,...);

// End of inclusion
#endif

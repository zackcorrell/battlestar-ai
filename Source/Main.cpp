/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Main.cpp
 Desc: Main application entry point.
 
***************************************************************/

#include <stdio.h>
#include "Ships.h"
int main()
{
	// Build the board and print the data
	Board SampleBoard(10, 10, NULL);
	SampleBoard.Print();

	return 0;
}

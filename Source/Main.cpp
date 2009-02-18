/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Main.cpp
 Desc: Main application entry point.
 
***************************************************************/

#include <stdio.h>
#include <queue>
#include "Ships.h"
#include "Board.h"

int main()
{
	// Place a few ships

	Board SampleBoard(NULL);
	SampleBoard.Print();

	// Test board code
	printf("Hello, World!\n");
	return 0;
}

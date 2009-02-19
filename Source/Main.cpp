/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Main.cpp
 Desc: Main application entry point.
 
***************************************************************/

#include <stdio.h>
#include "DumbPlayer.h"
#include "Game.h"
#include "Windows.h" // WINDOWS SPECIFIC
#include "Main.h"

// Define some global variables (As seen in main.h, used for configuration)
bool Silence;

int main()
{
	/* TODO:
		Create logging system (verbose mode output)
		Have a quite flag -q or -s
	*/

	// Set silence to true
	Silence = false;
	
	// Seed the random
	srand((int)GetTickCount()); // WINDOWS SPECIFIC

	// Build the board and print the data
	DumbPlayer Player1(10, 10);
	DumbPlayer Player2(10, 10);

	// Setup a game (10x10 board, 10,000 rounds)
	Game SampleGame(&Player1, &Player2, 10, 10, 1);

	// Start game
	int p1, p2;
	SampleGame.RunAll(&p1, &p2);

	return 0;
}

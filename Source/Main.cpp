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

// Define globals from Main.h
bool Silence;
bool Logging;
FILE* LoggingFile;

// Main application entry point
int main(int argc, char *argv[])
{
	/*** Start of initialization of global variables ***/

	Silence = false;
	Logging = false;

	/*** End of initialization of global variables ***/

	// Open the logging file if enabled
	if(Logging == true)
	{
		// Open output file
		LoggingFile = fopen("Output.log", "w");
	}

	// Seed the random
	srand((int)GetTickCount()); // WINDOWS SPECIFIC

	/*** Start of main simulation ***/

	// Build the board and print the data
	DumbPlayer Player1(10, 10);
	DumbPlayer Player2(10, 10);

	// Setup a game (10x10 board, 10,000 rounds)
	Game SampleGame(&Player1, &Player2, 10, 10, 1);

	// Start game
	int p1, p2;
	SampleGame.RunAll(&p1, &p2);

	/*** End of main simulation ***/

	// Close file if opened
	if(Logging == true)
		fclose(LoggingFile);

	return 0;
}

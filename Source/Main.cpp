/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Main.cpp
 Desc: Main application entry point. Now supports UNIX and Win32
 
***************************************************************/

#include "Util.h"
#include "DumbPlayer.h"
#include "Game.h"

// Define globals from Main.h
bool Silence;
bool Logging;
FILE* LoggingFile;

// Main application entry point
int main(int argc, char *argv[])
{
	/*** Start of initialization of global variables ***/

	Silence = true;
	Logging = true;

	/*** End of initialization of global variables ***/

	// Open the logging file if enabled
	if(Logging == true)
	{
		// Open output file
		LoggingFile = fopen("Output.log", "w");
		if(LoggingFile == NULL)
		{
			printf("Failed to open 'Output.log'\n");
			return -1;
		}

		// Place header
		fprintf(LoggingFile, "Starting log file...\n====================\n\n");
	}

	// Seed the rand
	srand((int)clock());

	/*** Start of main simulation ***/

	// Build the board and print the data
	DumbPlayer Player1(10, 10);
	DumbPlayer Player2(10, 10);

	// Setup a game (10x10 board, 100 rounds)
	Game SampleGame(&Player1, &Player2, 10, 10, 100);

	// Start game
	int p1, p2;
	SampleGame.RunAll(&p1, &p2);

	/*** End of main simulation ***/

	// Close file if opened
	if(Logging == true)
	{
		// Place header
		fprintf(LoggingFile, "\nEnding log file\n====================\n");
		fclose(LoggingFile);
	}

	return 0;
}

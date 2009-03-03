/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Main.cpp
 Desc: Main application entry point. Now supports UNIX and Win32
 
***************************************************************/

#include "Util.h"
#include "DumbPlayer.h" // Randomization
#include "SinkPlayer.h" // Randomization with sinking-intelligence
#include "ShooterPlayer.h" // Intelligent shooting without sinking-intelligence
#include "GAPlayer.h" // Genetic algorithm approach
#include "Game.h"

// Define globals from Main.h
bool Silence;
bool Logging;
FILE* LoggingFile;

// Main application entry point (Arguments not needed)
int main( /* int argc, char *argv[] */ )
{
	/*** Start of initialization of global variables ***/

	Silence = true;
	Logging = true;

	const int BOARD_SIZE = 10; // Size of the board to play
	const int GAME_COUNT = 10; // Number of games to play

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
	SinkPlayer *Player1 = new SinkPlayer(BOARD_SIZE, BOARD_SIZE);
	ShooterPlayer *Player2 = new ShooterPlayer(BOARD_SIZE, BOARD_SIZE);

	// Setup a game (10x10 board, 1,000 rounds)
	Game SampleGame((Player*)Player1, (Player*)Player2, BOARD_SIZE, BOARD_SIZE, GAME_COUNT);

	// Start game
	int p1, p2;
	SampleGame.RunAll(&p1, &p2);

	// End game, release player
	delete Player1;
	delete Player2;

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

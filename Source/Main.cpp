/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Main.cpp
 Desc: Main application entry point. Now supports UNIX and Win32
 
***************************************************************/

/***   CONFIGURATION   ***/ /**********************************/

// Player types (Name of class from header included below)
#define PLAYER_1_TYPE GAPlayer
#define PLAYER_2_TYPE GAPlayer

// Board type
#define BOARD_SIZE 10
#define GAME_COUNT 1000

// Global flags
#define IS_SILENCE_ON true
#define IS_VERBOSE_ON false
#define IS_LOGGING_ON true

/*** END CONFIGURATION ***/ /**********************************/

// Game and util includes
#include "Game.h"
#include "Util.h"

// Player includes
#include "DumbPlayer.h"  // Randomization
#include "SinkPlayer.h"  // Randomization with sinking-intelligence
#include "ShooterPlayer.h"  // Intelligent shooting without sinking-intelligence
#include "SmartRandom.h"  // Intelligent shooting with sinking-intelligence
#include "GAPlayer.h"  // Genetic algorithm approach

// Define globals from Main.h
bool Silence;
bool Verbose;
bool Logging;
FILE* LoggingFile;

// Main application entry point (Arguments not needed)
int main( /* int argc, char *argv[] */ )
{
	/*** Start of initialization of global variables ***/

	Silence = IS_SILENCE_ON;
	Logging = IS_LOGGING_ON;

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
	PLAYER_1_TYPE *Player1 = new PLAYER_1_TYPE(BOARD_SIZE, BOARD_SIZE);
	PLAYER_2_TYPE *Player2 = new PLAYER_2_TYPE(BOARD_SIZE, BOARD_SIZE);

	// Setup a game
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

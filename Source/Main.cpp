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
#define PLAYER_1_TYPE DumbPlayer
#define PLAYER_2_TYPE GAPlayer

// Board type
#define BOARD_SIZE 10
#define GAME_COUNT 1000

// Global flags
#define IS_SILENCE_ON false
#define IS_VERBOSE_ON false
#define IS_LOGGING_ON true

/*** END CONFIGURATION ***/ /**********************************/

// Game and util includes
#include "Game.h"
#include "Util.h"

#include "Board2.h"

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

//// Main application entry point (Arguments not needed)
//int main( /* int argc, char *argv[] */ )
//{
//	/*** Start of initialization of global variables ***/
//
//	Silence = IS_SILENCE_ON;
//	Logging = IS_LOGGING_ON;
//
//	/*** End of initialization of global variables ***/
//
//	// Open the logging file if enabled
//	if(Logging == true)
//	{
//		// Open output file
//		LoggingFile = fopen("Output.log", "w");
//		if(LoggingFile == NULL)
//		{
//			printf("Failed to open 'Output.log'\n");
//			return -1;
//		}
//
//		// Place header
//		fprintf(LoggingFile, "Starting log file...\n====================\n\n");
//	}
//
//	// Seed the rand
//	srand((unsigned int)clock());
//
//	/*** Start of main simulation ***/
//
//	// Build the board and print the data
//	PLAYER_1_TYPE *Player1 = new PLAYER_1_TYPE(BOARD_SIZE, BOARD_SIZE);
//	PLAYER_2_TYPE *Player2 = new PLAYER_2_TYPE(BOARD_SIZE, BOARD_SIZE);
//
//	// Setup a game
//	Game SampleGame((Player*)Player1, (Player*)Player2, BOARD_SIZE, BOARD_SIZE, GAME_COUNT);
//
//	// Start game
//	int p1, p2;
//	SampleGame.RunAll(&p1, &p2);
//
//	// End game, release player
//	delete Player1;
//	delete Player2;
//
//	/*** End of main simulation ***/
//
//	// Close file if opened
//	if(Logging == true)
//	{
//		// Place header
//		fprintf(LoggingFile, "\nEnding log file\n====================\n");
//		fclose(LoggingFile);
//	}
//
//	return 0;
//}

int main()
{
	Board2 board;

	srand(time(NULL));

	double linearizedCount[100];
	for(int i = 0; i < 100; linearizedCount[i++] = 0);

	Ship Ships[5];
	for(int i = 0; i < 100000; i++)
	{
		Player::SetupStatic(Ships, 5, 10, 10);
		Board b(10, 10);
		b.AddShips(Ships, 5);

		for(int j =  0; j < 100; j++)
		{
			if(b.GetState(j % 10, j / 10) == StateShip)
				linearizedCount[j] += 1;
		}
	}
	
	/*double step = 100 / (2 * PI);
	for(int i = 0; i < 100; i++)
	{
		linearizedCount[i] = sin(i/step) + cos(i/step) + 20;
	}*/

	GAShoot shoot(linearizedCount);

	for(int i = 0; i < 50; i++)
	{
		shoot.runGeneration();
		printf("Generation %d: %f\n", i+1, shoot.bestFitness());
	}

	double* dist = shoot.bestDist();
	double distMax = 0, countMax = 0;
	for(int i = 0; i < 100; i++)
	{
		if(dist[i] > distMax)
			distMax = dist[i];
		if(linearizedCount[i] > countMax)
			countMax = linearizedCount[i];
	}
	for(int i = 0; i < 100; dist[i] /= distMax, linearizedCount[i++] /= countMax); 

	FILE* out = fopen("out.csv", "w");
	for(int i = 0; i < 100; i++)
		fprintf(out, "%f, %f\n", linearizedCount[i], dist[i]);
	fclose(out);
	delete[] dist;

	//shoot.save("out.dat");
	int x, y;

	for(int i = 0; i < 100; i++)
	{
		shoot.getTarget(&x, &y, &board);
		board.print();
		printf("(%d, %d)\n", x, y);
	}

	return 0;
}
/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Game.h"

Game::Game(Player* PlayerA, Player* PlayerB, int Games)
{
	// Validate
	if(PlayerA == NULL || PlayerB == NULL)
	{
		printf("PlayerA or PlayerB have been given NULL values.\n");
		exit(-1);
	}

	// Save game count
	GameCount = Games;

	// Save the player pointers
	Players[0] = PlayerA;
	Players[1] = PlayerB;
}

int Game::Run()
{
	// Start a game with two boards
	Board* Boards[2];

	// Reset each player and setup the boards
	for(int i = 0; i < 2; i++)
	{
		Players[i]->Reset();
		Boards[i] = new Board(&Players[i]->Setup());
	}

	// Keep looping until we have a winner
	while(true)
	{
		// If there is a winner, return the winner's id
		for(int i = 0; i < 2; i++)
		{
			if(Boards[i]->ValidateWin())
				return i;
		}

		// Let both players play
		for(int i = 0; i < 2; i++)
		{
			// Player i shoots
			int x, y;
			Players[i]->Shoot(&x, &y);

			// Retrieve result and apply logic
			

			// Player i gets result
			Players[i]->ShootResult(x, y, 0);
		}
	}

	// Release boards
	for(int i = 0; i < 2; i++)
		delete Boards[i];

	// Warning prevention
	return 0;
}

void Game::RunAll(int *Player0Score, int *Player1Score)
{
	// For each game, save scores
	int Scores[2] = {0, 0};
	for(int i = 0; i < GameCount; i++)
	{
		// Save score
		Scores[Run()]++;
	}

	// Post back scores
	*Player0Score = Scores[0];
	*Player1Score = Scores[1];
}

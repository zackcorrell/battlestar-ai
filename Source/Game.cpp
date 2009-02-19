/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Game.h"

Game::Game(Player* PlayerA, Player* PlayerB, int BoardWidth, int BoardHeight, int Games)
{
	// Validate
	if(PlayerA == NULL || PlayerB == NULL)
	{
		printf("PlayerA or PlayerB have been given NULL values.\n");
		exit(-1);
	}

	// Save size
	this->BoardWidth = BoardWidth;
	this->BoardHeight = BoardHeight;

	// Save game count
	GameCount = Games;
	TotalGames = 0;

	// Save the player pointers
	Players[0] = PlayerA;
	Players[1] = PlayerB;
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

	// Print out final scores
	int winner;
	if(Scores[0] > Scores[1])
		winner = 0;
	else if(Scores[1] > Scores[0])
		winner = 1;
	else
		winner = -1; // Tie

	// If tie,
	if(winner == -1)
		printf(">> There has been a tie.\n");
	else
		printf(">> Game winner, of %d rounds, is: (%d)[%s].\n", TotalGames, winner, Players[winner]->GetName());

	// Final scores
	printf(">> Final scores: (0)%d vs (1)%d.\n", Scores[0], Scores[1]);

	// Post back scores
	*Player0Score = Scores[0];
	*Player1Score = Scores[1];
}

int Game::Run()
{
	// Print starting game
	if(!Silence)
		printf(">> Starting round %d between (0)[%s], and (1)[%s].\n", TotalGames, Players[0]->GetName(), Players[1]->GetName());

	// Start a game with two boards
	Board* Boards[2];

	// Reset each player and setup the boards
	for(int i = 0; i < 2; i++)
	{
		// Create a ship queue
		queue<Ship> ShipLists;

		// Call reset and then setup
		Players[i]->Reset();
		Players[i]->Setup(&ShipLists);

		// Setup the game board
		Boards[i] = new Board(&ShipLists, BoardWidth, BoardHeight);
	}

	// Keep looping until we have a winner
	int winner = -1;
	while(true && winner == -1)
	{
		// Let both players play
		for(int i = 0; i < 2 && winner == -1; i++)
		{
			// Player i shoots
			int x, y;
			Players[i]->Shoot(&x, &y);

			// Retrieve result of the enemy's board (Internally applies needed rules)
			ShotState State = Boards[ (i + 1) % 2 ]->GetState(x, y);

			// If we have nothing, return a miss
			if(State == StateEmpty)
			{
				Boards[ (i + 1) % 2 ]->SetState(x, y, StateMiss);
				State = StateMiss;
			}
			else if(State == StateShip)
			{
				Boards[ (i + 1) % 2 ]->SetState(x, y, StateHit);
				State = StateHit;
			}

			// Player i gets result
			Players[i]->ShootResult(x, y, State);

			// Print out player i's board
			if(!Silence)
			{
				printf(">> (%d)[%s]'s board:\n", i, Players[i]->GetName());
				Boards[i]->Print();
			}
		}

		// If there is a winner, return the winner's id
		for(int i = 0; i < 2 && winner == -1; i++)
		{
			// If a player board has no ships left, it's the opponent that wins
			if(Boards[i]->ValidateWin())
				winner = (i + 1) % 2;
		}
	}

	// Release boards
	for(int i = 0; i < 2; i++)
		delete Boards[i];

	// Grow game count
	TotalGames++;

	// Print winner
	if(!Silence)
		printf(">> Round %d winner is: (%d)[%s]\n", TotalGames, winner, Players[winner]->GetName());

	// Warning prevention
	return winner;
}

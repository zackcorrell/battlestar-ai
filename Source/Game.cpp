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
		Printf("PlayerA or PlayerB have been given NULL values.\n");
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

Game::~Game()
{
	// Nothing to release
}

void Game::RunAll(int *Player0Score, int *Player1Score)
{
	// For each game, save scores
	int Scores[2] = {0, 0};
	for(int i = 0; i < GameCount; i++)
	{
		// Save score (This could be one line, but hey, I like clarity!)
		int RoundWinner = Run();
		Scores[RoundWinner]++;
	}

	// Print out final scores
	int GameWinner;
	if(Scores[0] > Scores[1])
		GameWinner = 0;
	else if(Scores[1] > Scores[0])
		GameWinner = 1;
	else
		GameWinner = -1; // Tie

	// Turn out output just for the bellow info
	bool SavedState = Silence;
	Silence = false;

	// If tie,
	if(GameWinner == -1)
		Printf(">> There has been a tie.\n");
	else
		Printf(">> Game winner, of %d rounds, is: (%d)[%s].\n", TotalGames, GameWinner, Players[GameWinner]->GetName());

	// Final scores
	Printf(">> Final scores: (0)%d vs (1)%d.\n", Scores[0], Scores[1]);

	Silence = SavedState;

	// Post back scores
	*Player0Score = Scores[0];
	*Player1Score = Scores[1];
}

int Game::Run()
{
	// Print starting game
	Printf(">> Starting round %d between (0)[%s], and (1)[%s].\n", TotalGames, Players[0]->GetName(), Players[1]->GetName());

	// Start a game with two boards and a run count
	Board* Boards[2];

	// Reset each player and setup the boards
	for(int i = 0; i < 2; i++)
	{
		// Create a ship queue
		Ship ShipList[5];

		// Call reset and then setup for 5 ships
		Players[i]->Reset();
		Players[i]->Setup(ShipList, 5);

		// Setup the game board
		Boards[i] = new Board(BoardWidth, BoardHeight);
		Boards[i]->AddShips(ShipList, 5);
	}

	// Keep tracking the winner and the number of turns per this game
	int winner = -1;
	int Turn = 0; // A turn is defined by each player playing

	// While the winner is unknown
	while(winner == -1)
	{
		// Say which turn we are in
		Printf(">> Turn %d:\n", Turn++);

		// Let both players play unless we have a winner
		for(int i = 0; i < 2 && winner == -1; i++)
		{
			// Print out player i's board
			// Only print if verbose
			if(Verbose)
			{
				Printf(">> (%d)[%s]'s board:\n", i, Players[i]->GetName());
				Boards[i]->Print();
			}

			// Let the current player shoot the amount of times they have in ships
			int ShipCount = 5 - Boards[i]->GetSunkCount();
			for(int j = 0; j < ShipCount; j++)
			{
				// Player i shoots the ammount of ships they have
				int x, y;
				Players[i]->Shoot(&x, &y);

				// Retrieve state of the enemy's board
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

					// Tell the board we hit one of it's ships (So they can sink)
					Boards[ (i + 1) % 2 ]->HitShip(x, y);
				}

				// Player i gets result
				Players[i]->ShootResult(x, y, State);

				// Player i + 1 also gets the result
				Players[ (i + 1) % 2]->EnemyResult(x, y, State);

				// If the opposite's board has no ships left, it's this player (i) that wins
				if(Boards[(i + 1) % 2]->GetSunkCount() == 5)
				{
					// Post winner
					winner = i;
					break;
				}
			}
			// End of shooting
		}
		// End two player's playing
	}

	// Lets print off the final boards
	Printf(">> There has been a winner! Printing last boards...\n\n");
	for(int i = 0; i < 2; i++)
	{
		Printf(">> (%d)[%s]'s board:\n", i, Players[i]->GetName());
		Boards[i]->Print();
	}

	// Release boards
	for(int i = 0; i < 2; i++)
		delete Boards[i];

	// Print winner
	Printf(">> Round %d winner is: (%d)[%s]\n", TotalGames, winner, Players[winner]->GetName());

	// Grow game count
	TotalGames++;

	// Warning prevention
	return winner;
}

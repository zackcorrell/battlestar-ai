/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: Game.h
 Desc: The game manager that takes two player instances and
       plays them through a single game.
 
***************************************************************/

// Inclusion guard
#ifndef __GAME_H_
#define __GAME_H_

#include "Player.h"
#include "Board1.h"
#include "Util.h"

class Game
{
public:

	// Constructor; takes two opponents and a game count.
	Game(Player* PlayerA, Player* PlayerB, int Board1Width, int Board1Height, int Games = 1);

	// Destructor
	~Game();

	// Run all games
	void RunAll(int *Player0Score, int *Player1Score);

private:

	// Run a single itteration of a game, return 0 if player 0 won, and 1 if player 1 won
	int Run();

	// Both players 0 and 1
	Player* Players[2];

	// Total games played, target total game count
	int TotalGames, GameCount;

	// Board1 size
	int Board1Width, Board1Height;

};

// End of inclusion guard
#endif

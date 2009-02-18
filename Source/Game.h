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
#include "Board.h"

class Game
{
public:

	// Constructor; takes two opponents and a game count.
	Game(Player* PlayerA, Player* PlayerB, int BoardWidth, int BoardHeight, int Games = 1);

	// Run a single itteration of a game, return 0 if player 0 won, and 1 if player 1 won
	int Run();

	// Run all games
	void RunAll(int *Player0Score, int *Player1Score);

private:

	// Both players 0 and 1
	Player* Players[2];

	// Game count
	int GameCount;

	// Board size
	int BoardWidth, BoardHeight;
};

// End of inclusion guard
#endif

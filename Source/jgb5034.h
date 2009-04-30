// ========================================
// INCLUDED

#include "GAPlayer.h"

#ifndef __JGB5034_H_
#define __JGB5034_H_

class JGB5034
{

public:
	string myName, opponent;
	Board *board;
	GAPlayer *Player;
	_move move;

	JGB5034(Board *b, string me, string op)
	{
		myName = me;	// leave
		board = b;		// leave
		opponent = op;	// leave

		char Name[128];
		strcpy(Name, op.c_str());
		Player = new GAPlayer(Name, 10, 10);
	}

	void InitializeBoard()
	{
		Ship Ships[5];
		Player->Setup(Ships, 5);

		for(int i = 0; i < 5; i++)
		{
			int x = Ships[i].x[0];
			int y = Ships[i].y[0];

			char Dir;
			if(Ships[i].direction == North)
				Dir = 'N';
			else if(Ships[i].direction == East)
				Dir = 'E';
			else if(Ships[i].direction == South)
				Dir = 'S';
			else if(Ships[i].direction == West)
				Dir = 'W';

			char Type;
			if(Ships[i].Type == AircraftCarrier)
				Type = 'A';
			else if(Ships[i].Type == Battleship)
				Type = 'B';
			else if(Ships[i].Type == Cruiser)
				Type = 'D';
			else if(Ships[i].Type == Submarine)
				Type = 'S';
			else if(Ships[i].Type == Destroyer)
				Type = 'P';

			board->placeBoat(x, y, Dir, 'A');
		}
	}

	_move getMove()
	{
		Player->Shoot(&move.x, &move.y);
		return move;
	}

	void takeHit(_move move)
	{
		// do whatever you want to here
		// called whenever a shot is fired at you
		// so you can track what is going on
		Player->EnemyResult(move.x, move.y, StateHit);
	}

	void resultFromLastShot(string result)
	{
		ShotState State;
		if(result.find("Hit") != string::npos)
			State = StateHit;
		else
			State = StateMiss;
		Player->ShootResult(move.x, move.y, State);
	}


};
// END OF INCLUDED

#endif

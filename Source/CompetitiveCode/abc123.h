// ========================================
// INCLUDED

class ABC123
{

public:
	string myName, opponent;
	Board *board;

	ABC123(Board *b, string me, string op)
	{
		myName = me;	// leave
		board = b;		// leave
		opponent = op;	// leave
	}

	void InitializeBoard()
	{
		// do whatever you want to here, as long 
		// as you use the "placeBoat" function to
		// place your boats!
		board->placeBoat(0, 0, 'S', 'A');
		board->placeBoat(9, 9, 'N', 'B');
		board->placeBoat(5, 5, 'W', 'D');
		board->placeBoat(5, 0, 'E', 'S');
		board->placeBoat(7, 2, 'W', 'P');
	}

	_move getMove()
	{
		_move move;

		// I expect that this will be a lot more
		// dynamic than what I have here!
		move.x = rand() % WIDTH;
		move.y = rand() % LENGTH;

		return move;
	}

	void takeHit(_move move)
	{
		// do whatever you want to here
		// called whenever a shot is fired at you
		// so you can track what is going on
	}

	void resultFromLastShot(string result)
	{
		// do whatever you want
		// with the result of the last shot
	}


};
// END OF INCLUDED


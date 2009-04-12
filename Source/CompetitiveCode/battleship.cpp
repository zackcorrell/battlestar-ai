#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int LENGTH = 10, WIDTH = 10;

struct _move
{
	int x;
	int y;
};

class Board
{
public:
	char us[LENGTH][WIDTH];
	bool aSet, bSet, dSet, sSet, pSet;
	string myName;

	Board (string name)
	{
		myName = name;
		cout << "Creating the board..." << endl;
		for (int x = 0; x < LENGTH; x++)
		{
			for (int y = 0; y < WIDTH; y++)
			{
				us[y][x] = '_';
			}
		}
		aSet = bSet = dSet = sSet = pSet = false;
	}
	void error(string message)
	{
		cout << endl << "****************" << endl;
		cout << "ERROR for player " << myName << endl;
		cout << message << endl;
		cout << "****************" << endl << endl;
		exit(0);
	}

	void placeBoat(int sx, int sy, char direction, char val)
	{
		int spaces, startx, starty, endx, endy;

		switch (val)
		{
			case 'A':
				if (aSet)
					error("Aircraft carrier already set!");
				aSet = true;
				spaces = 5;
				break;
			case 'B':
				if (bSet)
					error("Battleship already set!");
				bSet = true;
				spaces = 4;
				break;
			case 'D':
				if (dSet)
					error("Destroyer already set!");
				dSet = true;
				spaces = 3;
				break;
			case 'S':
				if (sSet)
					error("Submarine already set!");
				sSet = true;
				spaces = 3;
				break;
			case 'P':
				if (pSet)
					error("Patrol boat carrier already set!");
				pSet = true;
				spaces = 2;
				break;
			default:
				cout << "Invalid boat type" << endl;
				exit(0);
		}

		switch (direction)
		{
			case 'N':
				startx = endx = sx;
				starty = sy-spaces+1;
				endy = sy;
				break;
			case 'S':
				startx = endx = sx;
				starty = sy;
				endy = sy+spaces-1;
				break;
			case 'E':
				startx = sx;
				endx = sx + spaces -1;
				starty = endy = sy;
				break;
			case 'W':
				startx = sx - spaces +1;
				endx = sx;
				starty = endy = sy;
				break;
			default:
				error("Invalid direction to set boat");
		}

		cout << "Setting boat from " << startx << "," << starty << " to ";
		cout << endx << "," << endy << endl;

		for (int y = starty; y <= endy; y++)
			for (int x = startx; x <= endx; x++)
				setValue(x, y, val);

	}

	void setValue(int x, int y, char val)
	{
		if ((x < 0) || (x >= LENGTH))
			error("x coordinate out of range.");
		if ((y < 0) || (y >= WIDTH))
			error("y coordinate out of range.");
		if (us[y][x] != '_')
			error("Position already filled!");
		else
			us[y][x] = val;
	}

	void displayBoard ()
	{
		cout << endl << "========================================" << endl;
		cout << myName;
		cout << endl << "========================================" << endl;
		for (int y = 0; y < WIDTH; y++)
		{
			for (int x = 0; x < LENGTH; x++)
			{
				cout << us[y][x] << " | ";
			}
			cout << endl;
		}
		cout << endl;
	}

};

// ========================================
#include "scs12.h"
#include "abc123.h"

// ========================================

class Status
{
public:

	int hitsOnA, hitsOnB, hitsOnD, hitsOnS, hitsOnP;
	int boats;


	Status()
	{
		hitsOnA = hitsOnB = hitsOnD = hitsOnS = hitsOnP = 0;
		boats = 5;
	};

	int processHit(char value, string& result)
	{
		result = "No result";
		switch(value)
		{
			case 'X':
				result = "Already shot there!";
				break;
			case '_':
				result = "Miss";
				break;
			case 'A':
				result = "Hit aircraft carrier!";
				hitsOnA++;
				if (hitsOnA >= 5)
				{
					result += "--Aircraft carrier sunk!";
					boats--;
				}
				break;
			case 'B':
				result = "Hit battleship!";
				hitsOnB++;
				if (hitsOnB >= 4)
				{
					result += "--Battleship sunk!";
					boats--;
				}
				break;
			case 'D':
				result = "Hit destroyer!";
				hitsOnD++;
				if (hitsOnD >= 3)
				{
					result += "--Destroyer sunk!";
					boats--;
				}
				break;
			case 'S':
				result = "Hit submarine!";
				hitsOnS++;
				if (hitsOnS >= 3)
				{
					result += "--Submarine sunk!";
					boats--;
				}
				break;
			case 'P':
				result = "Hit patrol boat!";
				hitsOnP++;
				if (hitsOnP >= 2)
				{
					result += "Patrol boat sunk!";
					boats--;
				}
				break;
		}
		cout << result << endl;
		return boats;
	} // end of processHit

}; // end of Status class

int main()
{
	Board b1("SCS12"), b2("ABC123");
	Status s1, s2;
	string result;

	int counter = 0;

	srand ( time(NULL) );

	SCS12 p1(&b1, "SCS12", "ABC123");	// created by script before running program
										// second parameter is your name
										// third parameter is opponent name
	cout << "Player 1 is " << p1.myName << endl;
	p1.InitializeBoard();

	ABC123 p2(&b2, "ABC123", "SCS12");	// created by script before running program
										// second parameter is your name
										// third parameter is opponent name
	cout << "Player 2 is " << p2.myName << endl;
	p2.InitializeBoard();

	p1.board->displayBoard();
	p2.board->displayBoard();
	while ((s1.boats > 0) && (s2.boats > 0))
	{
		_move move;

		for (int x = 0; x < s1.boats; x++)
		{
			move = p1.getMove();
			cout << p1.myName << " fires at " << move.x << ", " << move.y << " -- ";
			s2.processHit(p2.board->us[move.y][move.x], result);
			p2.board->us[move.y][move.x] = 'X';
			p2.takeHit(move);
			p1.resultFromLastShot(result);
		}
		p2.board->displayBoard();
		//{char scs[5]; gets(scs);} // pause

		for (int x = 0; x < s2.boats; x++)
		{
			move = p2.getMove();
			cout << p2.myName << " fires at " << move.x << ", " << move.y << " -- ";
			s1.processHit(p1.board->us[move.y][move.x], result);
			p1.board->us[move.y][move.x] = 'X';
			p1.takeHit(move);
			p2.resultFromLastShot(result);
		}
		p1.board->displayBoard();
		//{char scs[5]; gets(scs);} // pause


		// useful for debugging
		//if ((counter % 100) == 0)
		//	{char scs[5]; gets(scs);} // pause

		// in case your strategy is really pathetic!
		if (counter++ > 1000)
		{
			cout << "Timed out after 1000 turns" << endl;
			break;
		}
	}

	if (s1.boats < 1)
		cout << "Player " << p1.myName << " loses!" << endl;
	else if (s2.boats < 1)
		cout << "Player " << p2.myName << " loses!" << endl;
	else
		cout << "Draw!" << endl;
}

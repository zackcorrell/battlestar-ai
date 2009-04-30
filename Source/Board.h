#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef __BOARD_H_
#define __BOARD_H_

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

	void displayBoard1 ()
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

#endif

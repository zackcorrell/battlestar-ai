/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Board1.h"

Board1::Board1(int Board1Width, int Board1Height)
{
	// Allocate board space
	Board1Data = new ShotState[Board1Width * Board1Height];
	if(Board1Data == NULL)
	{
		Printf("The board count not be allocated.\n");
		exit(-1);
	}

	// Save size
	this->Board1Width = Board1Width;
	this->Board1Height = Board1Height;

	// Initialize the board
	for(int i = 0; i < Board1Width * Board1Height; i++)
		Board1Data[i] = StateEmpty;
}

Board1::~Board1()
{
	// Release board
	delete[] Board1Data;
}

void Board1::AddShips(Ship *ShipsList, int ShipCount)
{
	// Validate ShipsList
	if(ShipsList == NULL)
	{
		Printf("Invalid ShipsList pointer given in AddShips(...).\n");
		exit(-1);
	}

	// Validate ship placement
	if(ValidateShips(ShipsList, ShipCount, Board1Width, Board1Height) == false)
	{
		Printf("Invalid ShipsList list.\n");
		exit(-1);
	}

	// For each ship
	for(int i = 0; i < ShipCount; i++)
	{
		// Get the current ship
		Ship TempShip = ShipsList[i];

		// Place ship into list
		this->ShipsList[i] = TempShip;

		// Place onto board
		// For each ship's element
		for(int j = 0; j < (int)ShipsList[i].Type; j++)
		{
			// Get position
			int x = ShipsList[i].x[j];
			int y = ShipsList[i].y[j];

			// Place ship
			Board1Data[y * Board1Width + x] = StateShip;
		}
	}
}

ShotState Board1::GetState(int x, int y)
{
	// Validate position
	if(x < 0 || x >= Board1Width || y < 0 || y >= Board1Height)
	{
		Printf("The given target for GetState(...) is out of bounds.\n");
		exit(-1);
	}

	// Get current state
	return Board1Data[y * Board1Width + x];
}

void Board1::SetState(int x, int y, ShotState State)
{
	// Validate position
	if(x < 0 || x >= Board1Width || y < 0 || y >= Board1Height)
	{
		Printf("The given target for SetState(...) is out of bounds.\n");
		exit(-1);
	}

	// Save the state
	Board1Data[y * Board1Width + x] = State;
}

void Board1::HitShip(int x, int y)
{
	// For each ship
	for(int i = 0; i < 5; i++) // 5 == ship count
	{
		// For each ship's length
		for(int j = 0; j < (int)ShipsList[i].Type; j++)
		{
			// Get position
			int shipx = ShipsList[i].x[j];
			int shipy = ShipsList[i].y[j];

			// If the ship has been hit, set it's sink flag to true at that index
			if(shipx == x && shipy == y)
			{
				ShipsList[i].Hit[j] = true;
				return;
			}
		}
	}

	// Nothing found, just return
}

int Board1::GetSunkCount()
{
	// Sunk count
	int Sunk = 0;

	// For each ship
	for(int i = 0; i < 5; i++)
	{
		if(ShipsList[i].IsSunk())
			Sunk++;
	}

	// Return sunk count
	return Sunk;
}

void Board1::Print()
{
	// Print top line
	Printf("   [0][1][2][3][4][5][6][7][8][9]\n");

	// Print table
	for(int y = 0; y < Board1Height; y++)
	{
		// Print side line
		Printf("[%c]", 'A' + y);
		for(int x = 0; x < Board1Width; x++)
		{
			char output;
			switch(Board1Data[y * Board1Width + x])
			{
				case StateShip:	output = '#'; break;
				case StateMiss:	output = 'o'; break;
				case StateHit:	output = 'x'; break;
				default:		output = ' '; break;
			}

			// Output current element
			Printf("(%c)", output);
		}
		Printf("\n");
	}

	// print legent
	Printf("Legend: ' ' is water; 'o' is a miss\n");
	Printf("        'x' is a hit; '#' is a ship\n\n");
}

bool Board1::ValidateShips(Ship *ShipsList, int ShipCount, int Width, int Height)
{
	// Return invalid if the given pointer is null
	if(ShipsList == NULL)
		return false;

	// Allocate board size
	ShotState *Board1 = new ShotState[Width * Height];

	// Initialize the board
	for(int i = 0; i < Width * Height; i++)
		Board1[i] = StateEmpty;

	// The return data
	bool IsValid = true;

	// For each ship
	for(int i = 0; i < ShipCount && IsValid; i++)
	{
		// For each ship's length
		for(int j = 0; j < (int)ShipsList[i].Type; j++)
		{
			// Get position
			int x = ShipsList[i].x[j];
			int y = ShipsList[i].y[j];

			// If out of bounds or a ship already exists here...
			if(x < 0 || x >= Width || y < 0 || y >= Height || Board1[y * Width + x] == StateShip)
			{
				IsValid = false;
				break;
			}

			// Place ship
			Board1[y * Width + x] = StateShip;
		}
	}

	// Release board
	delete [] Board1;

	// Return validation data
	return IsValid;
}

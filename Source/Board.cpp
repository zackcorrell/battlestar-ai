/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Board.h"

Board::Board(int BoardWidth, int BoardHeight)
{
	// Allocate board space
	BoardData = new ShotState[BoardWidth * BoardHeight];
	if(BoardData == NULL)
	{
		Printf("The board count not be allocated.\n");
		exit(-1);
	}

	// Save size
	this->BoardWidth = BoardWidth;
	this->BoardHeight = BoardHeight;

	// Initialize the board
	for(int i = 0; i < BoardWidth * BoardHeight; i++)
		BoardData[i] = StateEmpty;
}

Board::~Board()
{
	// Release board
	delete[] BoardData;
}

void Board::AddShips(Ship *ShipsList, int ShipCount)
{
	// Validate ShipsList
	if(ShipsList == NULL)
	{
		Printf("Invalid ShipsList pointer given in AddShips(...).\n");
		exit(-1);
	}

	// Validate ship placement
	if(ValidateShips(ShipsList, ShipCount, BoardWidth, BoardHeight) == false)
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
			BoardData[y * BoardWidth + x] = StateShip;
		}
	}
}

ShotState Board::GetState(int x, int y)
{
	// Validate position
	if(x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
	{
		Printf("The given target for GetState(...) is out of bounds.\n");
		exit(-1);
	}

	// Get current state
	return BoardData[y * BoardWidth + x];
}

void Board::SetState(int x, int y, ShotState State)
{
	// Validate position
	if(x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
	{
		Printf("The given target for SetState(...) is out of bounds.\n");
		exit(-1);
	}

	// Save the state
	BoardData[y * BoardWidth + x] = State;
}

void Board::HitShip(int x, int y)
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

int Board::GetSunkCount()
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

void Board::Print()
{
	// Print top line
	Printf("   [0][1][2][3][4][5][6][7][8][9]\n");

	// Print table
	for(int y = 0; y < BoardHeight; y++)
	{
		// Print side line
		Printf("[%c]", 'A' + y);
		for(int x = 0; x < BoardWidth; x++)
		{
			char output;
			switch(BoardData[y * BoardWidth + x])
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

bool Board::ValidateShips(Ship *ShipsList, int ShipCount, int Width, int Height)
{
	// Return invalid if the given pointer is null
	if(ShipsList == NULL)
		return false;

	// Allocate board size
	ShotState *Board = new ShotState[Width * Height];

	// Initialize the board
	for(int i = 0; i < Width * Height; i++)
		Board[i] = StateEmpty;

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
			if(x < 0 || x >= Width || y < 0 || y >= Height || Board[y * Width + x] == StateShip)
			{
				IsValid = false;
				break;
			}

			// Place ship
			Board[y * Width + x] = StateShip;
		}
	}

	// Release board
	delete [] Board;

	// Return validation data
	return IsValid;
}

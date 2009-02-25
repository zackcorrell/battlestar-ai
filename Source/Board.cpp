/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Board.h"

Board::Board(queue<Ship> *Ships, int BoardWidth, int BoardHeight)
{
	// Allocate board space
	BoardData = new ShotState[BoardWidth * BoardHeight];
	if(Ships == NULL || BoardData == NULL)
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

	// Validate ship placement and place to board data
	if(ValidateShip(Ships, NULL, BoardWidth, BoardHeight, BoardData) == false)
	{
		Printf("The given ship has invalid placement.\n");
		exit(-1);
	}
}

Board::~Board()
{
	// Release board
	delete[] BoardData;
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

bool Board::AllSunk()
{
	// Does there exist any square that is a "Ship"
	bool AllSunk = true;
	for(int i = 0; i < BoardWidth * BoardHeight && AllSunk; i++)
	{
		// There is still a ship piece on board
		if(BoardData[i] == StateShip)
			AllSunk = false;
	}

	// Return valid
	return AllSunk;
}

void Board::Print()
{
	// Print top line
	Printf("   [0][1][2][3][4][5][6][7][8][9]\n");

	// Print table
	for(int y = 0; y < BoardHeight; y++)
	{
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

bool Board::ValidateShip(queue<Ship> *ShipList, Ship *NewShip, int Width, int Height, ShotState* GivenBuffer)
{
	// Validate data
	if(ShipList == NULL)
		return false;

	// Copy over the ships queue
	queue<Ship> Ships = *ShipList;

	// Allocate a new board (only if needed)
	ShotState* BoardData;
	if(GivenBuffer == NULL)
		BoardData = new ShotState[Width * Height];
	else
		BoardData = GivenBuffer;

	// Initialize board
	for(int i = 0; i < Width * Height; i++)
		BoardData[i] = StateEmpty;

	// For each ship
	bool stop = false;
	while(!stop)
	{
		// Target ship to write
		Ship myShip;

		// Get ship data
		if(!Ships.empty())
		{
			// Pop off queue
			myShip = Ships.front();
			Ships.pop();
		}
		else
		{
			// Now that all ships are placed, test this last ship
			if(NewShip == NULL)
			{
				if(GivenBuffer == NULL)
					delete [] BoardData;
				return true; // Valid
			}

			// Copy over given ship for last ship check
			myShip = *NewShip;
			stop = true;
		}

		// Place ship
		for(int i = 0; i < (int)myShip.ship; i++)
		{
			// Get base position
			int x = myShip.x, y = myShip.y;

			// Offset appropriately
			switch(myShip.direction)
			{

			// Grow ship towards north
			case North: y -= i; break;

			// Grow ship towards north
			case East: x += i; break;

			// Grow ship towards north
			case South: y += i; break;

			// Grow ship towards north
			case West: x -= i; break;

			default: break;
			}

			// Out of bounds or on an existance ship (collision)
			if(x < 0 || x >= Width || y < 0 || y >= Height || BoardData[y * Width + x] == StateShip)
			{
				if(GivenBuffer == NULL)
					delete [] BoardData;
				return false;
			}

			// Place ship piece
			BoardData[y * Width + x] = StateShip;
		}
	}

	// Release the board and return validation
	if(GivenBuffer == NULL)
		delete [] BoardData;
	return true;
}

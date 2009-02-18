/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "Board.h"

Board::Board(int BoardWidth, int BoardHeight, queue<Ship> *Ships)
{
	// Save size
	this->BoardWidth = BoardWidth;
	this->BoardHeight = BoardHeight;

	// Allocate board space
	BoardData = new ShotState[BoardWidth * BoardHeight];
	if(BoardData == NULL)
	{
		printf("The board count not be allocated.\n");
		exit(-1);
	}

	// Initialize the board
	for(int x = 0; x < BoardWidth; x++)
	{
		for(int y = 0; y < BoardHeight; y++)
		{
			BoardData[y * BoardWidth + x] = StateEmpty;
		}
	}

	// For each ship (Pass if given Ships queue is null)
	while(Ships != NULL && !Ships->empty())
	{
		// Get ship data
		Ship myShip = Ships->front();

		// Place ship
		for(int i = 0; i < (int)myShip.ship; i++)
		{
			// Get base position
			int x = myShip.x, y = myShip.y;

			// Offset appropriately
			switch(myShip.direction)
			{

			// Grow ship towards north
			case North:
				y -= i;
				break;

			// Grow ship towards north
			case East:
				x += i;
				break;

			// Grow ship towards north
			case South:
				y += i;
				break;

			// Grow ship towards north
			case West:
				x -= i;
				break;

			default: break;
			}

			// Out of bounds or on an existance ship (collision)
			if(x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight || BoardData[y * BoardWidth + x] == StateShip)
			{
				printf("The given ship has invalid placement.\n");
				exit(-1);
			}

			// Place ship piece
			BoardData[y * BoardWidth + x] = StateShip;
		}

		// Pop ship off the queue
		Ships->pop();
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
		printf("The given ship has invalid placement.\n");
		exit(-1);
	}

	// Get current state
	ShotState State = BoardData[y * BoardWidth + x];

	// If we have nothing, return a miss
	if(State == StateEmpty)
	{
		BoardData[y * BoardWidth + x] = StateMiss;
		return StateMiss;
	}
	else if(State == StateShip)
	{
		BoardData[y * BoardWidth + x] = StateHit;
		return StateHit;
	}
}

void Board::SetState(int x, int y, ShotState State)
{
	// Validate position
	if(x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
	{
		printf("The given ship has invalid placement.\n");
		exit(-1);
	}

	BoardData[y * BoardWidth + x] = State;
}

bool Board::ValidateWin()
{
	// Does there exist any square that is a "Ship"
	bool Valid = true;
	for(int x = 0; x < BoardWidth && Valid; x++)
	{
		for(int y = 0; y < BoardHeight && Valid; y++)
		{
			// There is still a ship piece on board
			if(BoardData[y * BoardWidth + x] == StateShip)
				Valid = false;
		}
	}

	return Valid;
}

void Board::Print()
{
	// Print top line
	printf("   [0][1][2][3][4][5][6][7][8][9]\n");

	// Print table
	for(int x = 0; x < BoardWidth; x++)
	{
		printf("[%c]", 'A' + x);
		for(int y = 0; y < BoardHeight; y++)
		{
			char output;
			switch(BoardData[y * BoardWidth + x])
			{
			case StateMiss:	output = 'o'; break;
			case StateHit:	output = 'x'; break;
			case StateSink:	output = '#'; break;
			default:		output = ' '; break;
			}

			// Output current element
			printf("(%c)", output);
		}
		printf("\n");
	}
	
	// print legent
	printf("Legend: ' ' is water; 'o' is a miss\n");
	printf("        'x' is a hit; '#' is a sink\n\n");
}

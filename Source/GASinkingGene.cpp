/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GASinkingGene.h"

GASinkingGene::GASinkingGene()
{
	// Reset registers
	ResetRegisters();

	// Initialize all program space to nops
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < GA_MAX_INSTRUCTIONS; j++)
			Instructions[i][j] = Nop;
}

void GASinkingGene::Clean()
{
	// For each instruction state
	for(int i = 0; i < 3; i++)
	{
		// From left to right
		for(int j = 0; j < GA_MAX_INSTRUCTIONS; j++)
		{
			// If nop, shift everything from the right to this position
			if(Instructions[i][j] == Nop)
			{
				// Shift
				for(int k = j; k < (GA_MAX_INSTRUCTIONS - 1); k++)
					Instructions[i][k] = Instructions[i][k + 1];

				// Cap end with new Nop
				Instructions[i][GA_MAX_INSTRUCTIONS - 1] = Nop;

				// If from here to the end of the array is just nop, break out..
				for(int k = j; k < GA_MAX_INSTRUCTIONS; k++)
				{
					if(Instructions[i][k] != Nop)
					{
						j--;
						break;
					}
				}
			}
			// Done with if nop seek loop..
		}
	}
}

int GASinkingGene::FitnessValue(GASinkingGene *Gene)
{
	// Make sure there is at least one jump per state
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j <= GA_MAX_INSTRUCTIONS; j++)
		{
			// End of code, didn't break yet, so this is a very bad gene..
			if(j == GA_MAX_INSTRUCTIONS)
				return INT_MAX;

			// We have at least one jump, great!
			if(Gene->Instructions[i][j] == Jump)
				break;
		}
	}

	// Run through gene and make sure we don't have a failure under some random cases
	for(int i = 0; i < 10; i++)
	{
		// Reset internal registers and program counter
		Gene->ResetRegisters();

		// Random x and y positions
		int tempx = rand() % 10, tempy = rand() % 10;

		// Random test run; if we have an internal faulure just quit
		if(Gene->Run(&tempx, &tempy, (bool)(rand() % 2)) == GeneFailure)
			return INT_MAX;
	}

	// Run through a number of sample games...
	int Total = 0;

	// Save the number of total instructions ran through
	for(int i = 0; i < 10; i++)
	{
		// JEREMY WAS HERE
	}

	// Return fitness value
	return Total;
}

GARunState GASinkingGene::Run(int *DataX, int *DataY, bool Hit)
{
	// If we do get a correct hit
	if(Hit)
		TargetHit = true;
	else
		TargetHit = false;

	// Keep looping only up to GA_FAILURE_COUNT
	for(int counter = 0; counter <= GA_FAILURE_COUNT; counter++)
	{
		// Are we at the end of our counter for cosidering this is a "lame" gene?
		if(counter == GA_FAILURE_COUNT)
			return GeneFailure;

		// Get the current instruction
		GAInstruction Op = Instructions[(int)State][ProgramCounter];

		// Temporary variables used inside switch and post-back events
		int dir;
		static bool PostBack = false;

		// Switch through the map
		switch(Op)
		{

		// Place a valid shot into 
		case Target:
			// Get shot
			if(PostBack == false)
			{
				PostBack = true;
				return GetShot;
			}

			// Retrieve shot from post
			else
			{
				TargetPos[0] = *DataX; // x
				TargetPos[1] = *DataY; // y
				PostBack = false;
			}
		break;

		// Shoot target position
		case Shoot:
			// Post shot
			*DataX = TargetPos[0];
			*DataY = TargetPos[1];

			// Grow counter and say we've placed a shot
			GrowCounter();
			return SetShot;
		break;

		// Move target position forward
		case MoveFwd:
			if(TargetDir == North)
			{
				if(TargetPos[1] > 0)
					TargetPos[1]--;
			}
			else if(TargetDir == East)
			{
				if(TargetPos[0] < 9)
					TargetPos[1]++;
			}
			else if(TargetDir == South)
			{
				if(TargetPos[1] < 9)
					TargetPos[1]++;
			}
			else
			{
				if(TargetPos[0] < 9)
					TargetPos[0]++;
			}
		break;

		// Set a random direction not yet chosen
		case RandDir:

			// If we have tried all, just reset
			if(DirUsed[0] && DirUsed[1] && DirUsed[2] && DirUsed[3])
				DirUsed[0] = DirUsed[1] = DirUsed[2] = DirUsed[3] = false;

			// Choose a direction that hasn't been used yet
			dir = 0;
			while(true)
			{
				// Dir not used yet
				dir = rand() % 4;
				if(DirUsed[dir] == false)
					break;
			}

			// Post direction
			TargetDir = (Direction)dir;
		break;

		// Choose a vertical direction, as best as possible
		case VertDir:

			// If we have tried all, just reset
			if(DirUsed[0] && DirUsed[1] && DirUsed[2] && DirUsed[3])
				DirUsed[0] = DirUsed[1] = DirUsed[2] = DirUsed[3] = false;

			// Direction of choice
			dir = 0;

			// If we have tried top and bottom already
			if(DirUsed[0] && DirUsed[2])
			{
				// Search left and right
				while(true)
				{
					// Dir not used yet
					dir = rand() % 2;
					dir++; // Shift to east
					if(dir == 2)
						dir = 3; // Force to west
					if(DirUsed[dir] == false)
						break;
				}
			}
			// Choose only up or down
			else
			{
				// Search top and bottom
				while(true)
				{
					// Dir not used yet
					dir = rand() % 2;
					if(dir == 1) // Force to south
						dir = 2;
					if(DirUsed[dir] == false)
						break;
				}
			}

			// Post direction
			TargetDir = (Direction)dir;
		break;

		// Choose a horizontal direction, as best as possible
		case HorzDir:

			// If we have tried all, just reset
			if(DirUsed[0] && DirUsed[1] && DirUsed[2] && DirUsed[3])
				DirUsed[0] = DirUsed[1] = DirUsed[2] = DirUsed[3] = false;

			// Direction of choice
			dir = 0;

			// If we have tried left and right already
			if(DirUsed[1] && DirUsed[3])
			{
				// Search top and bottom
				while(true)
				{
					// Dir not used yet
					dir = rand() % 2;
					if(dir == 1)
						dir = 2;
					if(DirUsed[dir] == false)
						break;
				}
			}
			// Choose only left or right
			else
			{
				// Search left and right
				while(true)
				{
					// Dir not used yet
					dir = rand() % 2;
					dir++;
					if(dir == 2) // Force to south
						dir = 3;
					if(DirUsed[dir] == false)
						break;
				}
			}

			// Post direction
			TargetDir = (Direction)dir;
		break;

		// Save position
		case SavePos:
			// Move from target pos to temp pos
			TempPos[0] = TargetPos[0];
			TempPos[1] = TargetPos[1];
		break;

		// Load position
		case LoadPos:
			// Move from target pos to temp pos
			TargetPos[0] = TempPos[0];
			TargetPos[1] = TempPos[1];
		break;

		// Set temp flag to true
		case SetTrue:
			TempHit = true;
		break;

		// Set temp flag to true
		case SetFalse:
			TempHit = false;
		break;

		// If TargetHit register is true
		// Run next line
		// Else
		case IfHit:
			// If we don't hit something,
			// run past all if cases...
			if(!TargetHit)
			{
				// Read off all conditional statements
				while(true)
				{
					GAInstruction temp = Instructions[(int)State][ProgramCounter];
					if(temp != IfHit && temp != IfMiss && temp != IfTrue && temp != IfFalse)
						break;
					GrowCounter();
				}
			}
		break;

		// If TargetHit register is false
		// Run next line
		// Else
		case IfMiss:
			// If we did hit something,
			// run past all if cases...
			if(TargetHit)
			{
				// Read off all conditional statements
				while(true)
				{
					GAInstruction temp = Instructions[(int)State][ProgramCounter];
					if(temp != IfHit && temp != IfMiss && temp != IfTrue && temp != IfFalse)
						break;
					GrowCounter();
				}
			}
		break;

		// If TargetHit register is true
		// Run next line
		// Else
		case IfTrue:
			// If false
			if(!TempHit)
			{
				// Read off all conditional statements
				while(true)
				{
					GAInstruction temp = Instructions[(int)State][ProgramCounter];
					if(temp != IfHit && temp != IfMiss && temp != IfTrue && temp != IfFalse)
						break;
					GrowCounter();
				}
			}
		break;

		// If TargetHit register is true
		// Run next line
		// Else
		case IfFalse:
			// If true
			if(TempHit)
			{
				// Read off all conditional statements
				while(true)
				{
					GAInstruction temp = Instructions[(int)State][ProgramCounter];
					if(temp != IfHit && temp != IfMiss && temp != IfTrue && temp != IfFalse)
						break;
					GrowCounter();
				}
			}
		break;

		// Jump to the next machine state
		case Jump:

			// Reset program counter
			ProgramCounter = -1; // Since we are going to add one anyways again..

			// Jump to the next area
			if(State == Searching)
				State = Targeting;
			else if(State == Targeting)
				State = Locked;
			else
				State = Searching;

		break;

		// If no-operation or illegal-operation
		// Don't do anything...
		case Nop:
		default:;

		}

		// Grow counter correctly
		GrowCounter();
	}
}

void GASinkingGene::Breed(GASinkingGene *GeneA, GASinkingGene *GeneB)
{
	// For each chunk of code, choose a random size from 1 to half it's size
	int ChunkSize[3] = 
	{
		1 + rand() % GA_MAX_INSTRUCTIONS,
		1 + rand() % GA_MAX_INSTRUCTIONS,
		1 + rand() % GA_MAX_INSTRUCTIONS,
	};

	// For each chunk of code, choose a random position that is valid
	int ChunkPos[3][2];
	for(int i = 0; i < 2; i++)
	{
		ChunkPos[0][i] = rand() % (GA_MAX_INSTRUCTIONS - ChunkSize[0] + 1);
		ChunkPos[1][i] = rand() % (GA_MAX_INSTRUCTIONS - ChunkSize[1] + 1);
		ChunkPos[2][i] = rand() % (GA_MAX_INSTRUCTIONS - ChunkSize[2] + 1);
	}

	// For each chunk of code
	for(int i = 0; i < 3; i++)
	{
		// For each instruction in the chunk
		for(int j = 0; j < ChunkSize[i]; j++)
		{
			// Swap instruction
			GAInstruction temp = GeneA->Instructions[i][ChunkPos[i][0] + j];
			GeneA->Instructions[i][ChunkPos[i][0] + j] = GeneB->Instructions[i][ChunkPos[i][1] + j];
			GeneB->Instructions[i][ChunkPos[i][1] + j] = temp;
		}
	}

	// Apply a 10% chance of mutation of a single instruction randomly chosen per section
	for(int i = 0; i < 3; i++)
	{
		if( (rand() % 100) < 10 )
		{
			int PosA = rand() % GA_MAX_INSTRUCTIONS + i * GA_MAX_INSTRUCTIONS;
			GAInstruction OpA = (GAInstruction)(rand() % GA_TOTAL_INSTRUCTIONS);
			GeneA->Instructions[i][PosA] = OpA;

			int PosB = rand() % GA_MAX_INSTRUCTIONS + i * GA_MAX_INSTRUCTIONS;
			GAInstruction OpB = (GAInstruction)(rand() % GA_TOTAL_INSTRUCTIONS);
			GeneB->Instructions[i][PosB] = OpB;
		}
	}

	// Clean out the given genes..
	GeneA->Clean();
	GeneB->Clean();
}

int GASinkingGene::Simulate(GASinkingGene *Gene, int Width, int Height, Ship *ShipsList, int ShipCount)
{
	// Create a new board
	Board SampleBoard(Width, Height);

	// Place ships
	SampleBoard.AddShips(ShipsList, ShipCount);

	// Simulation variables
	int Total = 0;
	int x, y;
	int IndexX = 0, IndexY = 0;
	bool ShotSuccessful = false;

	// Keep playing until the board is complete
	while(SampleBoard.GetSunkCount() == ShipCount)
	{
		// Run through the program until an event
		GARunState State = Gene->Run(&x, &y, false);

		// Ask for a shot, place it into the next run call
		if(State == GetShot)
		{
			// We take another shot
			Total++;

			// Place shot into x and y
			x = IndexX;
			y = IndexY;

			// Only place in an unshot zone
			while(true)
			{
				// Grow for next round
				IndexX++;
				if(IndexX >= Width)
				{
					IndexX = 0;
					IndexY++;
				}

				// If y is out of bounds, then we went too far and this gene is bad
				if(IndexY >= Height)
					return INT_MAX;

				// If it's valid, break
				if(SampleBoard.GetState(x, y) == StateEmpty)
					break;
			}
		}
		// Place a shot onto the board
		else if(State == SetShot)
		{
			// If out of bounds, just say the shot failed
			if(x < 0 || x >= Width || y < 0 || y >= Height)
				ShotSuccessful = false;

			// Apply the given (x,y) shots
			else
			{
				// Retrieve state of the enemy's board
				ShotState State = SampleBoard.GetState(x, y);

				// If we have nothing, return a miss
				if(State == StateEmpty)
				{
					// Set state to missed
					SampleBoard.SetState(x, y, StateMiss);
					ShotSuccessful = false;
				}
				// If we hit a ship
				else if(State == StateShip)
				{
					// Set state to shot as well as 
					SampleBoard.SetState(x, y, StateHit);
					SampleBoard.HitShip(x, y);
					ShotSuccessful = true;
				}
			}
		}
		// Gene failure
		else
			return INT_MAX;
	}

	// Return total counts
	return Total;
}

void GASinkingGene::GrowCounter()
{
	// Move the instruction counter to the correct address
	ProgramCounter = (ProgramCounter + 1) % GA_MAX_INSTRUCTIONS;
}

void GASinkingGene::ResetRegisters()
{
	// Set positions to nothing for now
	TargetPos[0] = TargetPos[1] = 0;
	TempPos[0] = TempPos[1] = 0;

	// Set direction to north
	TargetDir = North;

	// Set both default states to false
	TargetHit = TempHit = false;

	// Program counter set to first instruction
	State = Searching;
	ProgramCounter = 0;

	// Default used dirs to be false
	for(int i = 0; i < 4; i++)
		DirUsed[i] = false;
}

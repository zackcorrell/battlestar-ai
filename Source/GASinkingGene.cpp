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

int GASinkingGene::FitnessValue(GASinkingGene Gene)
{
	// Run through a number of sample games...
	int Total = 0;

	// Run through gene and make sure we don't have a failure under some random cases
	for(int i = 0; i < GA_SIMULATION_COUNT; i++)
	{
		// Run a simulation
		int SimValue = Simulate( &Gene );

		// If sim value is int_max, thus must be bad, so just return the bad value
		if( SimValue == INT_MAX )
			return INT_MAX;
		// Else, sim whent well, lets take the shot count
		else
			Total += SimValue;
	}

	// Return fitness value
	return Total;
}

int GASinkingGene::Simulate(GASinkingGene *Gene)
{
	// Reset internal registers and program counter
	Gene->ResetRegisters();

	// Create a board game with random ship placement
	Board SampleBoard(10, 10);

	// Place ships randomly, SHOULD LOAD FROM HISTORY OF OPPONENT
	Ship Ships[5];
	Player::SetupStatic(Ships, 5, 10, 10);
	SampleBoard.AddShips(Ships, 5);

	// Simulation variables
	int Total = 0;
	int tempx = 0, tempy = 0;
	bool HasHit = false;

	// Keep playing until all 5 ships are sunk OR we went over the simulation count
	for(int sim = 0; sim <= GA_SIMULATION_COUNT; sim++)
	{
		// If sim count hit the counter bounds, break out for the error return
		if( sim == GA_SIMULATION_COUNT )
			return INT_MAX;

		// Check if we sunk all ships
		if( SampleBoard.GetSunkCount() >= 5 )
			return Total;

		// Run through the program until an event
		GARunState State = Gene->Run(&tempx, &tempy, HasHit);

		// If state failed
		if( State == GeneFailure )
			return INT_MAX;

		// Ask for a shot, place it into the next run call
		else if( State == GetShot )
		{
			// Non-repeating value
			while(true)
			{
				tempx = rand() % 10;
				tempy = rand() % 10;
				if(tempx < 0)
					tempx *= -1;
				if(tempy < 0)
					tempy *= -1;

				// If we have not yet shot this position, shoot it
				if(SampleBoard.GetState(tempx, tempy) == StateEmpty || SampleBoard.GetState(tempx, tempy) == StateShip)
					break;
			}
		}

		// Place a shot onto the board
		else if( State == SetShot )
		{
			// We take another shot
			Total++;

			// Wrap out x and y points and check for negatives
			tempx %= 10;
			tempy %= 10;
			if(tempx < 0)
				tempx *= -1;
			if(tempy < 0)
				tempy *= -1;

			// Place shot
			ShotState BoardState = SampleBoard.GetState(tempx, tempy);

			// If we have nothing, return a miss
			if(BoardState == StateEmpty)
			{
				SampleBoard.SetState(tempx, tempy, StateMiss);
				HasHit = false;
			}
			else if(BoardState == StateShip)
			{
				SampleBoard.SetState(tempx, tempy, StateHit);
				HasHit = true;
				SampleBoard.HitShip(tempx, tempy);
			}
		}

		// End of while loop
	}

	// Return error
	return INT_MAX;
}

GARunState GASinkingGene::Run(int *DataX, int *DataY, bool Hit)
{
	// If we do get a correct hit
	TargetHit = Hit;

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

			// Grow counter (so we don't run through the same code)
			// and say we've placed a shot
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
			DirUsed[dir] = true; // We are now using this direction
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
			DirUsed[dir] = true; // We are now using this direction
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
			DirUsed[dir] = true; // We are now using this direction
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

	// Return error since we went over our max instruction count run
	return GeneFailure;
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

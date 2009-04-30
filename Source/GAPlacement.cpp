/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GAPlacement.h"

GAPlacement::GAPlacement(char *EnemyName, int Board1Width, int Board1Height)
{
	// Valudate the enemy name
	if(EnemyName == NULL)
		EnemyName = "Default";

	// Save width and height
	Width = Board1Width;
	Height = Board1Height;

	// Form the file name
	sprintf(FileName, "%s.dat1", EnemyName);

	// Attempt to load file
	ifstream File(FileName);

	// Allocate the needed map
	Board1Data = new double[Width * Height];

	// File failed, load default data
	if(File.fail())
	{
		ifstream Default("Default.dat1");

		// Set all data to weights of HIT_UNIT
		for(int i = 0; i < Width * Height; i++)
		{
			Default >> Board1Data[i];
			Board1Data[i] += HIT_UNIT;
		}
		Default.close();
	}

	// File loaded, load data from file
	else
	{
		// Are we reading the same ammount of data?
		for(int i = 0; i < Width * Height; i++)
			File >> Board1Data[i];
	}
}

GAPlacement::~GAPlacement()
{
	// Write out to disk
	ofstream File(FileName);

	// Write out the matrix data
	for(int i = 0; i < Width * Height; i++)
		File << setprecision(8) << Board1Data[i] << " ";

	// Release data
	delete [] Board1Data;
}

void GAPlacement::EnemyShootsAt(int x, int y)
{
	// Place position densities
	PlaceShot(x, y, HIT_UNIT);

	// Place f(0.25) in the corners surrounding these bounds
	PlaceShot(x - 1, y - 1, HIT_UNIT / 4.0);
	PlaceShot(x - 1, y + 1, HIT_UNIT / 4.0);
	PlaceShot(x + 1, y - 1, HIT_UNIT / 4.0);
	PlaceShot(x + 1, y + 1, HIT_UNIT / 4.0);

	// Place in n,e,s,w for f(0.1)
	PlaceShot(x - 1, y, HIT_UNIT / 10.0);
	PlaceShot(x + 1, y, HIT_UNIT / 10.0);
	PlaceShot(x, y - 1, HIT_UNIT / 10.0);
	PlaceShot(x, y + 1, HIT_UNIT / 10.0);
}

void GAPlacement::Setup(Ship *Ships, int ShipCount)
{
	// Create two buffers, one for the linearization and one for the random selection
	double *Linearization = new double[Width * Height];

	// Find total sum of current shots
	double TotalSum = 0.0;
	for(int i = 0; i < Width * Height; i++)
		TotalSum += 1.0 / Board1Data[i];

	// Apply linearlization
	for(int i = 0; i < Width * Height; i++)
		Linearization[i] = (1.0 / Board1Data[i]) / TotalSum;

	// Build the Random select table
	// Element(i) = Element(0) + Element(1) + ... + Element(i - 1) + Element(i)
	for(int i = 1; i < Width * Height; i++)
		Linearization[i] += Linearization[i - 1];

	// For each ship
	for(int i = 1; i <= ShipCount; i++)
	{
		// Choose the appropriate type
		int length = i;
		if(i == 1)
			length = 2;
		else if(i == 2)
			length = 3;

		// Choose a location based on the linearlization
		double Target = GetRand( 1.0 ); // Normalized

		// Find the relative index
		int found = -1;
		for(int j = 0; j < Width * Height; j++)
		{
			// If the current element is greater that target, return the index of the previous
			if( Linearization[ j ] > Target )
			{
				found = j;
				break;
			}
		}

		// Choose a random starting position
		int x = found % Width;
		int y = found / Height;

		// Find the direction that is closts to the wall
		/*
		   THIS IS AN INVALID METHOD:
		   We will find spots of size 1 that are very low-density shooting,
		   but do not evaluate the suroundings where high-density shootings
		   might exist... The revised code solves this issue..
		*/
		/*
		int Distance[4] =
		{
			y,				// North
			Width - x - 1,	// East
			Height - y - 1,	// South
			x,				// West
		};
		*/
		///*
		int Distance[4] =
		{
			int(GetShotDensity(x, y-0) + GetShotDensity(x, y-1) + GetShotDensity(x, y-2)),	// North
			int(GetShotDensity(x+0, y) + GetShotDensity(x+1, y) + GetShotDensity(x+2, y)),	// East
			int(GetShotDensity(x, y+0) + GetShotDensity(x, y+1) + GetShotDensity(x, y+2)),	// South
			int(GetShotDensity(x-0, y) + GetShotDensity(x-1, y) + GetShotDensity(x-2, y)),	// West
		};
		//*/

		// Set the directions
		Direction Dir[4];
		int DirCounter = 0;
		int DirIndex = 0;

		// Push shortest directions first into list
		for(int j = 0; j < 4; j++)
		{
			// Save lowest value
			if( Distance[ j ] < Distance[ DirIndex ] )
				DirIndex = j;

			// If we are at the end of the list, just save index
			if( j == 3 )
			{
				// Set direction and reset search
				Dir[ DirCounter++ ] = (Direction)DirIndex;
				Distance[ DirIndex ] = INT_MAX;
				j = -1;

				// If we are at the end of the list, reset
				if( DirCounter >= 4 )
					break;
			}
		}

		// Try out all four directions..
		bool ValidShip = false;
		for(int j = 0; j < 4; j++)
		{
			// Create the ship and place into memory
			Ship ship((ShipType)length, x, y, Dir[j]); // Original code points ships intelligently
			Ships[ i - 1 ] = ship;

			// Validate if this new ship is any good, and if so, break out
			if( Board1::ValidateShips(Ships, i, Width, Height) == true )
			{
				ValidShip = true;
				break;
			}
		}

		// If we haven't found a valid ship, lets search again
		if(ValidShip == false)
			i--; // Itterate again
	}

	// Release map
	delete [] Linearization;
}

void GAPlacement::PlaceShot(int x, int y, double value)
{
	// Check if out of bounds
	if(x < 0 || x >= Width || y < 0 || y >= Height)
		return;
	Board1Data[ y * Width + x ] += value;
}

double GAPlacement::GetShotDensity(int x, int y)
{
	// Check if out of bounds
	if(x < 0 || x >= Width || y < 0 || y >= Height)
		return 0.0;
	return Board1Data[ y * Width + x ];
}

/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
***************************************************************/

#include "GAPlayer.h"

GAPlayer::GAPlayer(int BoardWidth, int BoardHeight)
	: Player("GAPlayer AI", BoardWidth, BoardHeight)
{

        // Placement algorithm testing
        GAPlacement Placement("Test123", 10, 10);

        // Density map
        int Map[100];
        for(int i = 0; i < 100; Map[i++] = 0);

        // Apply 1,000,000 runs
        for(int run = 0; run < 100000; run++)
        {
                // Get 5 ships
                Ship Ships[5];
                Placement.Setup(Ships, 5);

                // Place each ship onto map
                for(int i = 0; i < 5; i++)
                {
                        // Get the current ship
                        Ship TempShip = Ships[i];

                        // For the ship length
                        for(int j = 0; j < (int)TempShip.Type; j++)
                        {
                                // Get position
                                int x = TempShip.x[j], y = TempShip.y[j];

                                // Grow stat
                                Map[y * BoardWidth + x]++;
                        }
                }

                // Apply a shot into the middle
                static int x = 0;
                static int y = 0;
                Placement.EnemyShootsAt(x+=2 % BoardWidth, y+=2 % BoardHeight);
				if(x % BoardWidth == 0)
					x++;
				else if(x % (BoardWidth - 1) == 0)
					x++;

                // Grow stat
                //Map[(y % BoardHeight) * BoardWidth + (x% BoardWidth)]++;
		}

        // Print out data
        ofstream File("Data.csv");
        for(int y = 0; y < BoardHeight; y++)
        {
                for(int x = 0; x < BoardWidth; x++)
                {
                        File << Map[y * BoardWidth + x] << ",";
                }

                File << endl;
        }
        File.close();


	// Gene sinking debuging stuff..
	/*
	int counter = 0;
	for(int j = 0; j < INT_MAX; j++)
	{
		GASinkingGene temp;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < GA_MAX_INSTRUCTIONS; j++)
				temp.Instructions[i][j] = (GAInstruction)(rand() % GA_TOTAL_INSTRUCTIONS);
		}
		temp.Clean();
		if(GASinkingGene::FitnessValue(temp) == 0)
			counter++;

		printf("%d\t%d\n", j, counter);
	}
	*/
}

GAPlayer::~GAPlayer()
{
	// ...
}

void GAPlayer::Reset()
{
	// ...
}

void GAPlayer::Setup(Ship *Ships, int ShipCount)
{
	// ...
}

void GAPlayer::Shoot(int *x, int *y)
{
	// ...
}

void GAPlayer::ShootResult(int x, int y, ShotState state)
{
	// ...
}

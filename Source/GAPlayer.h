/***************************************************************
 
 Battlestar-AI Battleship AI
 Pennsylvania State University - CMPSC 442
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@psu.edu
 
 File: GAPlayer.h
 Desc: A Genetic Algorithm approach to a battleship player.
 
***************************************************************/

// Inclusion guard
#ifndef __GAPLAYER_H_
#define __GAPLAYER_H_

// Includes
#include "Player.h"
#include "Board.h"

// The representation of a gene
struct GAGene
{
	// Takes the grid size
	GAGene(int Width, int Height)
	{
		// Allocate memory

		// Initialize with random (valid) data
	}

	// Release data
	~GAGene()
	{
		// Release memory
	}

	// Mutate correctly (swap) based on a percentage of 0 to 1
	void Mutate(double Probability)
	{
		// Swap n number of data pairs and x and y coordinates
	}

	// Merge two genes together
	static GAGene Merge(GAGene Genes[2])
	{
		// Create a new gene
		GAGene Child(Genes[0].Width, Genes[0].Height);

		// Merge both data
	}

	// Gene data
	int *Data;			// A list of orders, from low to high, to shoot at first (based on x and y coordinates)
	int Width, Height;	// The size of the gene (map)
};

// Player class
class GAPlayer : public Player
{
public:

	// Required to implement
	GAPlayer(int BoardWidth, int BoardHeight);

	~GAPlayer();

	// Required to implement
	void Reset();

	// Required to implement
	void Shoot(int *x, int *y);

	// Required to implement
	void ShootResult(int x, int y, ShotState state);

private:

	// A list of all past games for use in our fitness function
	queue<Board*> BoardQueue;

};

// End of inclusion guard
#endif

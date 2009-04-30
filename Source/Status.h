#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef __STATUS_H_
#define __STATUS_H_

class Status
{
public:

	int hitsOnA, hitsOnB, hitsOnD, hitsOnS, hitsOnP;
	int boats;


	Status()
	{
		hitsOnA = hitsOnB = hitsOnD = hitsOnS = hitsOnP = 0;
		boats = 5;
	};

	int processHit(char value, string& result)
	{
		result = "No result";
		switch(value)
		{
			case 'X':
				result = "Already shot there!";
				break;
			case '_':
				result = "Miss";
				break;
			case 'A':
				result = "Hit aircraft carrier!";
				hitsOnA++;
				if (hitsOnA >= 5)
				{
					result += "--Aircraft carrier sunk!";
					boats--;
				}
				break;
			case 'B':
				result = "Hit battleship!";
				hitsOnB++;
				if (hitsOnB >= 4)
				{
					result += "--Battleship sunk!";
					boats--;
				}
				break;
			case 'D':
				result = "Hit destroyer!";
				hitsOnD++;
				if (hitsOnD >= 3)
				{
					result += "--Destroyer sunk!";
					boats--;
				}
				break;
			case 'S':
				result = "Hit submarine!";
				hitsOnS++;
				if (hitsOnS >= 3)
				{
					result += "--Submarine sunk!";
					boats--;
				}
				break;
			case 'P':
				result = "Hit patrol boat!";
				hitsOnP++;
				if (hitsOnP >= 2)
				{
					result += "Patrol boat sunk!";
					boats--;
				}
				break;
		}
		cout << result << endl;
		return boats;
	} // end of processHit

}; // end of Status class

#endif

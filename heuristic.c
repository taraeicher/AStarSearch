#include "node.h"
#include "heuristic.h"
#include "share.h"
#include <stdlib.h>

//Return the sum of manhattan distances for each point in the grid.

unsigned int heur(State current, State goal)
{
	unsigned int retVal = 0;	//return value
	
	//Add the manhattan distance for each pair of coordinates.
	
	unsigned short i;
	for(i = 0; i < 3; i++)
	{
		unsigned short j;
		for(j = 0; j < 3; j++)
		{
			CoordinatePair currentCoords;
			currentCoords.x = i;
			currentCoords.y = j;
			
			//Ignore the blank space.
			
			if(current.grid[i][j] != '\0')
				retVal += manhattanDistance(currentCoords, findValueInGrid(goal, current.grid[i][j]));
		}
	}
	return retVal;
}

//Return the manhattan distance for two coordinate pairs.

unsigned short manhattanDistance(CoordinatePair current, CoordinatePair goal)
{
	return (abs(current.x - goal.x) + abs(current.y - goal.y));
} 
#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "node.h"
#include "share.h"

//Return the sum of manhattan distances for each point in the grid.

unsigned int heur(State current, State goal);

//Return the manhattan distance for two coordinate pairs.

unsigned short manhattanDistance(CoordinatePair current, CoordinatePair goal);

#endif
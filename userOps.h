#ifndef USER_OPS_H
#define USER_OPS_H

#include "node.h"

//Get the start state from the user.

State getStartState();

//Get goal state from user.

State getGoalState();

//Print introductory message.

void welcome();

//Print the path from the start to the goal.

void printPath(Node* goal);

//Print each value in the grid for a given state.

void printGrid(State state);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "share.h"
#include "node.h"
#include "userOps.h"

//Get the start state from the user.

State getStartState()
{
	State userProvidedState;	//state to get from user
	boolean enteredVals[9];	//"bit vector" for entered values
	
	printf("First, I will need your starting state. Please enter digits between 1 and 8 only, from left to right, top to bottom.\n");
	printf("For the blank space, simply press ENTER.\n");

	//Get the value for each position.

	unsigned short i;
	for(i = 1; i <= 3; i++)
	{
		unsigned short j = 1;
		while(j <= 3)
		{
			printf("Enter the value for (%d,%d): ", i, j);
			unsigned short value = getc(stdin);
			getc(stdin);	//Get NULL character.
			
			//Check that value is a digit.
			
			if(value >= 49 && value <= 56)
			{
				if(enteredVals[value - 49] == False)
				{
					enteredVals[value - 49] = True;
					userProvidedState.grid[i][j] = value;
					j++;
				}
			}
		}
	}
	return userProvidedState;
	printf("Thanks!\n");
	
}

//Get goal state from user.

State getGoalState()
{
	State userProvidedState;	//state to get from user
	boolean enteredVals[9] = {False};	//"bit vector" for entered values
	
	printf("Now, I will need your goal state. Please enter digits between 1 and 8 only, from left to right, top to bottom.\n");
	printf("For the blank space, simply press ENTER.\n");

	//Get the value for each position.

	unsigned short i;
	for(i = 1; i <= 3; i++)
	{
		unsigned short j = 1;
		while(j <= 3)
		{
			printf("Enter the value for (%d,%d): ", i, j);
			unsigned short value = getc(stdin);
			getc(stdin);	//Get NULL character.
			
			//Check that value is a digit.
			
			if(value >= 49 && value <= 56)
			{
				if(enteredVals[value - 49] == False)
				{
					enteredVals[value - 49] = True;
					userProvidedState.grid[i][j] = value;
					j++;
				}
			}
		}
	}
	return userProvidedState;
	printf("Thanks again!\n");
}

//Print introductory message.

void welcome()
{
	printf("Hello! I'm here to solve your 8-puzzle.\n\n");
}

//Print the path from the start to the goal.

void printPath(Node* goal)
{
	//Edit the list.
	
	Node* beginning = goal;
	beginning->leftSibling = NULL;
	beginning->rightSibling = NULL;
	
	while(beginning->parent != NULL) 
	{
		beginning->parent->firstChild = beginning;
		beginning = beginning->parent;
	}
	
	//Now, print out the nodes, starting at the beginning.
	
	Node* current = beginning;
	int i = 0;
	while(current != NULL)
	{
		printf("Step %d:\n", i);
		printGrid(current->state);
		current = current->firstChild;
		i++;
	}
}

//Print each value in the grid for a given state.

void printGrid(State state)
{
	unsigned short i;
	for(i = 1; i <= 3; i++)
	{
		unsigned short j;
		for(j = 1; j <= 3; j++)
			printf("%c ", state.grid[i][j]);
		printf("\n");
	}
}

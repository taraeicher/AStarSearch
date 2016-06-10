#include "share.h"
#include "heuristic.h"
#include "node.h"
#include <stdlib.h>

//Compare two states.

boolean compareStates(State state1, State state2)
{
	boolean retVal = True;
	
	//Loop through each element in the grid.
	
	unsigned short i;
	for(i = 0; i <=3; i++)
	{
		unsigned short j;
		for(j = 0; j <=3; j++)
			if(state1.grid[i][j] != state2.grid[i][j]) goto end;
	}
	
	end: return retVal;
}

//Expand the node.

void expandNode(Node* nodeToExpand, State goalState)
{
	CoordinatePair blankSpaceCoords = findBlankSpace(nodeToExpand->state);	//coordinates of blank space
	
	//boolean values to determine where to insert a child in the linked list of children
	
	boolean hasLeft = False;
	boolean hasRight = False;
	boolean hasUpper = False;
	
	//Child nodes
	Node* leftChild = (Node*)malloc(sizeof(Node));
	Node* upperChild = (Node*)malloc(sizeof(Node));
	Node* rightChild = (Node*)malloc(sizeof(Node));
	Node* lowerChild = (Node*)malloc(sizeof(Node));
	
	//Generate left child if possible.
	
	if(blankSpaceCoords.x >= 0)
	{
		unsigned int temp; //temp variable for swaps
		leftChild->state = nodeToExpand->state;
		leftChild->parent = nodeToExpand;
		leftChild->leftSibling = NULL;
		leftChild->rightSibling = NULL;
		leftChild->firstChild = NULL;
		leftChild->g = nodeToExpand->g + 1;
		leftChild->h = heur(leftChild->state, goalState);
		leftChild->f = leftChild->g + leftChild->h;
		temp = leftChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		leftChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = leftChild->state.grid[blankSpaceCoords.x + 1][blankSpaceCoords.y];
		leftChild->state.grid[blankSpaceCoords.x + 1][blankSpaceCoords.y] = temp;
		nodeToExpand->firstChild = leftChild;	
		hasLeft = True;
	}
	
	//Generate upper child if possible.
	
	if(blankSpaceCoords.y >= 0)
	{
		unsigned int temp; //temp variable for swaps
		upperChild->state = nodeToExpand->state;
		upperChild->parent = nodeToExpand;
		upperChild->leftSibling = NULL;
		upperChild->rightSibling = NULL;
		upperChild->firstChild = NULL;
		upperChild->g = nodeToExpand->g + 1;
		upperChild->h = heur(upperChild->state, goalState);
		upperChild->f = upperChild->g + leftChild->h;
		temp = upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y + 1];
		upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y + 1] = temp;
		hasUpper = True;
		
		//Insert first if no preceding child.
		
		if(hasLeft) 
		{
			leftChild->rightSibling = upperChild;
			upperChild->leftSibling = leftChild;
		}
		else nodeToExpand->firstChild = upperChild;		
	}
	
	//Generate right child if possible.
	
	if(blankSpaceCoords.x < 3)
	{
		unsigned int temp; //temp variable for swaps
		rightChild->state = nodeToExpand->state;
		rightChild->parent = nodeToExpand;
		rightChild->firstChild = NULL;
		rightChild->leftSibling = NULL;
		rightChild->rightSibling = NULL;
		rightChild->g = nodeToExpand->g + 1;
		rightChild->h = heur(rightChild->state, goalState);
		rightChild->f = rightChild->g + rightChild->h;
		temp = rightChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		rightChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = rightChild->state.grid[blankSpaceCoords.x - 1][blankSpaceCoords.y];
		rightChild->state.grid[blankSpaceCoords.x - 1][blankSpaceCoords.y] = temp;
		hasRight = True;
		
		//Insert first if no preceding child.
		
		if(hasUpper)
		{
			upperChild->rightSibling = rightChild;
			rightChild->leftSibling = upperChild;
		}
		else if(hasLeft)
		{
			leftChild->rightSibling = rightChild;
			rightChild->leftSibling = leftChild;
		}
		else nodeToExpand->firstChild = rightChild;		
	}
	
	//Generate lower child if possible.
	
	if(blankSpaceCoords.x < 3)
	{
		unsigned int temp; //temp variable for swaps
		lowerChild->state = nodeToExpand->state;
		lowerChild->parent = nodeToExpand;
		lowerChild->firstChild = NULL;
		lowerChild->leftSibling = NULL;
		lowerChild->rightSibling = NULL;
		lowerChild->g = nodeToExpand->g + 1;
		lowerChild->h = heur(lowerChild->state, goalState);
		lowerChild->f = lowerChild->g + lowerChild->h;
		temp = lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y - 1];
		lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y - 1] = temp;
		
		//Insert first if no preceding child.
		
		if(hasRight)
		{
			rightChild->rightSibling = lowerChild;
			lowerChild->leftSibling = rightChild;
		}
		else if(hasUpper)
		{
			upperChild->rightSibling = lowerChild;
			lowerChild->leftSibling = upperChild;
		}
		else if(hasLeft)
		{
			leftChild->rightSibling = lowerChild;
			lowerChild->leftSibling = leftChild;
		}
		else nodeToExpand->firstChild = lowerChild;		
	}
}

//Find the blank space in the grid.

CoordinatePair findBlankSpace(State theState)
{
	return findValueInGrid(theState, '\0');
}

//Find a value in the grid.

CoordinatePair findValueInGrid(State theState, char value)
{
	CoordinatePair retVal;
	retVal.x = -1;
	retVal.y = -1;
		
		//Loop through each element in the grid.
		
		unsigned short i;
		for(i = 0; i <=3; i++)
		{
			unsigned short j;
			for(j = 0; j <=3; j++)
				if(theState.grid[i][j] == value)
				{
					retVal.x = i;
					retVal.y = j;
				}
		}
		
	return retVal;
}

//Generate the root.

Node* generateRoot(State theState, State goalState)
{
	Node* firstNode = malloc(sizeof(Node));
	firstNode->state = theState;
	firstNode->leftSibling = NULL;
	firstNode->rightSibling = NULL;
	firstNode->firstChild = NULL;
	firstNode->g = 0;
	firstNode->h = heur(theState, goalState);
	firstNode->f = firstNode->h;
	return firstNode;
}

//Update the parent of the node with a duplicate state.

void updateNodeAncestors(Node* nodeToUpdate, Node* newParent)
{
	//Because h will be the same for a given state, only need to examine g(n).
	
	if(nodeToUpdate->g > newParent->g + STEP_SIZE) 
	{
		nodeToUpdate->parent = newParent;
		nodeToUpdate->g = newParent->g + STEP_SIZE;
		nodeToUpdate->f = nodeToUpdate->g + nodeToUpdate->h;
	}
}


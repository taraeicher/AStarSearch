#ifndef NODE_H
#define NODE_H

#include "share.h"

//State (grid) of a node

typedef struct state
{
	char grid[3][3];
} State;

//Basic node contains the state, parent, and child.

typedef struct node
{
	State state;
	struct node* parent;
	struct node* leftSibling;
	struct node* rightSibling;
	struct node* firstChild;
	unsigned int f;
	unsigned int h;
	unsigned int g;
} Node;

//Compare two states.

boolean compareStates(State state1, State state2);

//Expand the node.

void expandNode(Node* nodeToExpand, State goalState);

//Find the blank space in the grid.

CoordinatePair findBlankSpace(State theState);

//Find a value in the grid.

CoordinatePair findValueInGrid(State theState, char value);

//Generate the root.

Node* generateRoot(State theState, State goalState);

//Update the parent of the node with a duplicate state.

void updateNodeAncestors(Node* nodeToUpdate, Node* newParent);

#endif
#include "aStarSearch.h"
#include <stdlib.h>
#include <stdio.h>

//main function

int main()
{
	welcome();
	State start = getStartState();
	List frontier, /*explored*/;
	boolean goalFound = False;
	boolean solutionIsTrivial = False;
	frontier.first = NULL;
	//explored.first = NULL;
	
	State goal = getGoalState();
	Node goalNode;
	Node* firstNode = generateRoot(start, goal);
//printf("root f val = %d\n",firstNode->f);
	addNodeToFrontier(firstNode, &frontier);

	//Loop until the optimal path is found.
	
	do
	{
		Node* expanded = pop(&frontier);
//printf("expanded f val = %d\n",expanded->f);
		//If this is not a goal state, expand it.
		
		if(compareStates(expanded->state, goal)) 
		{	
			goalNode = *expanded;
			goalFound = True;
printf("A goal state was found!\n");			
			//If this is the root, the solution is trivial.
			
			if(compareStates(expanded->state, firstNode->state))
			{
				printf("This puzzle is trivially solved.\n");
				solutionIsTrivial = True;
			}
		}
		else
		{
			expandNode(expanded, goal);
			Node* child = expanded->firstChild;
			
			//Add each child to the frontier as long as it is not a duplicate. If it is, update parent information.
			
			while(child != NULL)
			{
				Node* duplicate = findStateInList(&frontier, *child);
if(duplicate){printf("Frontier duplicate for %p found at %p\n",child,duplicate);printGrid(child->state);}
				if(duplicate) updateNodeAncestors(duplicate, child->parent);	
				else 
				{
					duplicate = findStateInList(&explored, *child);
if(duplicate){printf("Explored duplicate for %p found at %p\n",child,duplicate);printGrid(child->state);}
					if(duplicate) updateNodeAncestors(duplicate, child->parent); 
					else addNodeToFrontier(child, &frontier);
/*ListNode* i = frontier.first; int j=0;
for(;i->next!=NULL;i=i->next,j++);
printf("Frontier count = %d\n",j);*/
				}
				child = child->rightSibling;
			}
		}
		addNodeToExploredSet(expanded, &explored);
/*ListNode* k = frontier.first; int l=0;
for(;k->next!=NULL;k=k->next,l++);
printf("Explored count = %d\n",l);*/
	}
	while(frontier.first !=NULL);
	
	//Print out the path.

	if(goalFound)
	{
		if(!solutionIsTrivial) printPath(&goalNode);
	}
	else printf("There is no solution.\n");
	
	//Deallocate all nodes in explored set.

	ListNode* thisNode = explored.first;

	for(; thisNode != NULL; thisNode = thisNode->next)
	{
		if(thisNode->node != NULL) free(thisNode -> node);
		free(thisNode);
	}

	
	//Exit.
	return(0);
}

//Print introductory message.

void welcome()
{
	printf("Hello! I'm here to solve your 8-puzzle.\n\n");
}

//Get the start state from the user.

State getStartState()
{
	State userProvidedState;	//state to get from user
	boolean enteredVals[9] = {False};	//"bit vector" for entered values
	
	printf("First, I will need your starting state. Tiles must contain single digits between 1 and 8 only.\n");
	printf("For the blank space, enter 0.\n");

	//Get the value for each position.

	unsigned short i,j;
	for(i = 1; i <= 3; i++)
	{
		j = 1;
		while(j <= 3)
		{
			printf("Enter the value for (%d,%d): ", i, j);
			char value = getc(stdin);
			getc(stdin);	//Get newline character.

			//Check that value is a digit or line feed.

			if((int)value >= 49 && (int)value <= 56)
			{
				if(enteredVals[value - 49] == False)
				{
					enteredVals[value - 49] = True;
					userProvidedState.grid[i - 1][j - 1] = value;
					j++;
				}
			}
			else if((int)value == 49)
			{
				userProvidedState.grid[i - 1][j - 1] = value;
				j++;
			}
		}
	}
	printf("Thanks!\n");
	return userProvidedState;
	
}

//Get goal state from user.

State getGoalState()
{
	State userProvidedState;	//state to get from user
	boolean enteredVals[9] = {False};	//"bit vector" for entered values
	
	printf("Now, I will need your goal state. Tiles must contain single digits between 1 and 8 only.\n");
	printf("For the blank space, simply press ENTER.\n");

	//Get the value for each position.

		unsigned short i,j;
	for(i = 1; i <= 3; i++)
	{
		j = 1;
		while(j <= 3)
		{
			printf("Enter the value for (%d,%d): ", i, j);
			char value = getc(stdin);
			getc(stdin);	//Get newline character.

			//Check that value is a digit or line feed.

			if((int)value >= 49 && (int)value <= 56)
			{
				if(enteredVals[value - 49] == False)
				{
					enteredVals[value - 49] = True;
					userProvidedState.grid[i - 1][j - 1] = value;
					j++;
				}
			}
			else if((int)value == 48)
			{
				userProvidedState.grid[i - 1][j - 1] = value;
				j++;
			}
		}
	}
	printf("Thanks again!\n");
	return userProvidedState;
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

//Add a node to the frontier at the appropriate location.

void addNodeToFrontier(Node* node, List* frontier)
{
	//Create a new node to add to the frontier.

	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->node = node;
	newNode->next = NULL;
	newNode->previous = NULL;
	
	ListNode* current = frontier->first;
//if(current != NULL)printf("first node has value %d\n",frontier->first->node->f);
	//If the frontier is empty, make the new node the first node.
	//Else, insert where appropriate.
int i = 0;	
	if(current == NULL)
	{
		frontier->first = newNode;
		newNode->previous = NULL;
		newNode->next = NULL;
	}
	else
	{
		
		ListNode* prev = current;
		//printf("%d vs %d\n",newNode->node->f,current->node->f);
		while(current != NULL && newNode->node->f > current->node->f)
		{i++;//printf("%d vs %d\n",newNode->node->f,current->node->f);
			prev = current;
			current = current->next;
		}
			
		//Insert before the node that is greater than the new node.
			
		if(current != NULL)
		{
			//If the new node's f-value is less than that of the first node, make the new node the first node.
			//Else, ensure that the previous node points to the new node.
		
			if(current == frontier->first) frontier->first = newNode;
			else prev->next = newNode;
			
			//Place the new node between the previous and current nodes.
			
			newNode->previous = prev;
			newNode->next = current;
			current->previous = newNode;
		}
		
		//Insert at the end if appropriate.
		
		else
		{
			prev->next = newNode;
			newNode->previous = prev;
			newNode->next = NULL;
		}	
	}
ListNode* k = frontier->first; int l=0;
for(;k->next!=NULL;k=k->next,l++);
printf("Node added. Frontier count = %d\n",l);
printGrid(newNode->node->state);
//printf("Placed at position %d with value %d. First node value is %d\n",i,node->f,frontier->first->node->f);
//printGrid(node->state);	
}

//Return the node at the top of the queue.

Node* pop(List* frontier)
{
	if(frontier->first == NULL || frontier->first->node == NULL) return NULL;
	ListNode* toDelete = frontier->first;
//printf("Popped with value %d\n",toDelete->node->f);
	Node* retVal = frontier->first->node;
	
	//Delete references to the first node.
	
	if(frontier->first->next != NULL) frontier->first->next->previous = NULL;
	frontier->first = frontier->first->next;
//printf("First node is now %p\n",frontier->first);
	free(toDelete);
	
ListNode* i = frontier->first; int j=0;
if(i!=NULL)for(;i->next!=NULL;i=i->next,j++);
printf("Node popped. Frontier count = %d\n",j);
printGrid(retVal->state);
	return retVal;
}

//Compare two states.

boolean compareStates(State state1, State state2)
{
	//Loop through each element in the grid. Break when two keys do not match.

	unsigned short i;
	for(i = 0; i <3; i++)
	{
		unsigned short j;
		for(j = 0; j <3; j++)
			if(state1.grid[i][j] != state2.grid[i][j]) return False;
	}
	return True;
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
	
	//Generate left child if possible. Else, deallocate node.

	if(blankSpaceCoords.x > 0)
	{
		unsigned int temp; //temp variable for swaps
		leftChild->state = nodeToExpand->state;
		leftChild->parent = nodeToExpand;
		leftChild->leftSibling = NULL;
		leftChild->rightSibling = NULL;
		leftChild->firstChild = NULL;
		temp = leftChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		leftChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = leftChild->state.grid[blankSpaceCoords.x - 1][blankSpaceCoords.y];
		leftChild->state.grid[blankSpaceCoords.x - 1][blankSpaceCoords.y] = temp;
		leftChild->g = nodeToExpand->g + STEP_SIZE;
		leftChild->h = heur(leftChild->state, goalState);
		leftChild->f = leftChild->g + leftChild->h;
		nodeToExpand->firstChild = leftChild;	
		hasLeft = True;
	}
	else free(leftChild);
	
	//Generate upper child if possible. Else, deallocate node.
	
	if(blankSpaceCoords.y < 2)
	{
		unsigned int temp; //temp variable for swaps
		upperChild->state = nodeToExpand->state;
		upperChild->parent = nodeToExpand;
		upperChild->leftSibling = NULL;
		upperChild->rightSibling = NULL;
		upperChild->firstChild = NULL;
		temp = upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y + 1];
		upperChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y + 1] = temp;
		upperChild->g = nodeToExpand->g + STEP_SIZE;
		upperChild->h = heur(upperChild->state, goalState);
		upperChild->f = upperChild->g + upperChild->h;
		hasUpper = True;

		//Insert first if no preceding child.
		
		if(hasLeft) 
		{
			leftChild->rightSibling = upperChild;
			upperChild->leftSibling = leftChild;
		}
		else nodeToExpand->firstChild = upperChild;		
	}
	else free(upperChild);
	
	//Generate right child if possible. Else, deallocate node.
	
	if(blankSpaceCoords.x < 2)
	{
		unsigned int temp; //temp variable for swaps
		rightChild->state = nodeToExpand->state;
		rightChild->parent = nodeToExpand;
		rightChild->firstChild = NULL;
		rightChild->leftSibling = NULL;
		rightChild->rightSibling = NULL;
		temp = rightChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		rightChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = rightChild->state.grid[blankSpaceCoords.x + 1][blankSpaceCoords.y];
		rightChild->state.grid[blankSpaceCoords.x + 1][blankSpaceCoords.y] = temp;
		rightChild->g = nodeToExpand->g + STEP_SIZE;
		rightChild->h = heur(rightChild->state, goalState);
		rightChild->f = rightChild->g + rightChild->h;
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
	else free(rightChild);
	
	//Generate lower child if possible. Else, deallocate node.
	
	if(blankSpaceCoords.y > 0)
	{
		unsigned int temp; //temp variable for swaps
		lowerChild->state = nodeToExpand->state;
		lowerChild->parent = nodeToExpand;
		lowerChild->firstChild = NULL;
		lowerChild->leftSibling = NULL;
		lowerChild->rightSibling = NULL;
		temp = lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y];
		lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y] = lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y - 1];
		lowerChild->state.grid[blankSpaceCoords.x][blankSpaceCoords.y - 1] = temp;
		lowerChild->g = nodeToExpand->g + STEP_SIZE;
		lowerChild->h = heur(lowerChild->state, goalState);
		lowerChild->f = lowerChild->g + lowerChild->h;
		
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
	else free(lowerChild);
}

//Find the blank space in the grid.

CoordinatePair findBlankSpace(State theState)
{
	return findValueInGrid(theState, 10);
}

//Find a value in the grid.

CoordinatePair findValueInGrid(State theState, char value)
{
	CoordinatePair retVal;
	retVal.x = -1;
	retVal.y = -1;
		
		//Loop through each element in the grid.
		
		unsigned short i;
		for(i = 0; i < 3; i++)
		{
			unsigned short j;
			for(j = 0; j < 3; j++)
				if(theState.grid[i][j] == value)
				{
					retVal.x = i;
					retVal.y = j;
				}
		}		
	return retVal;
}

//Update the parent of the node with a duplicate state.

void updateNodeAncestors(Node* nodeToUpdate, Node* newParent)
{
	//Because h will be the same for a given state, only need to examine g(n).
	
	if(nodeToUpdate->g > newParent->g + STEP_SIZE) 
	{printf("Parent updating...\n");
		nodeToUpdate->parent = newParent;
		nodeToUpdate->g = newParent->g + STEP_SIZE;
		nodeToUpdate->f = nodeToUpdate->g + nodeToUpdate->h;
	}
}

//Add a node to the explored set. Simply add to the beginning, since no ordering is needed.

void addNodeToExploredSet(Node* node, List* exploredSet)
{
	//Create a new node to add to the frontier.

	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->node = node;	
	newNode->next = exploredSet->first;
	newNode->previous = NULL;
	if(exploredSet->first != NULL) exploredSet->first->previous = newNode;
	exploredSet->first = newNode;

ListNode* i = exploredSet->first; int j=0;
for(;i->next!=NULL;i=i->next,j++);
printf("Node added. Explored count = %d\n",j);
printGrid(newNode->node->state);
}

//Search the frontier for a node with a given state.

Node* findStateInList(List* listToSearch, Node nodeWithState)
{	
	ListNode* current = listToSearch->first;

	//Continue looping until a match is found.
	
	boolean isEquivalent = False;
	if(current != NULL) isEquivalent = compareStates(current->node->state, nodeWithState.state);
	while(!isEquivalent && current != NULL) 
	{
		current = current->next;
		if(current != NULL) isEquivalent = compareStates(current->node->state, nodeWithState.state);
	}
	
	//If a match was found, return the match.
	
	if(current == NULL) return NULL;
	return current->node;	
}

//Print the path from the start to the goal.

void printPath(Node* goal)
{
	//Build a list.
	
	List path;
	ListNode* new = (ListNode*)malloc(sizeof(ListNode));
	new->node = goal;
	new->previous = NULL;
	new->next = NULL;
	path.first = new;
	
	
	//Add each subsequent ancestor node.
	
	ListNode temp = *path.first;
	ListNode* tmpPtr = &temp;
	while(path.first->node->parent != NULL) 
	{
		temp = *path.first;
		tmpPtr = (ListNode*)malloc(sizeof(ListNode));
		*tmpPtr = temp;
		path.first->node = path.first->node->parent;
		
		//Add to the end.
	
		path.first->next = tmpPtr;

	}
	
	//Now, print out the nodes, starting at the beginning.

	ListNode* thisNode = path.first;
	unsigned int i;
	
	for(i = 0; thisNode != NULL; thisNode = thisNode->next, i++)
	{
		printf("Step %d:\n", i);
		printGrid(thisNode->node->state);
	}
	
	//Deallocate each node in the path.

	thisNode = path.first;
	while(thisNode != NULL)
	{
		ListNode* temp = thisNode;
		thisNode = thisNode->next;
		free(temp);
	}
}

//Print each value in the grid for a given state.

void printGrid(State state)
{
	unsigned short i;
	for(i = 0; i < 3; i++)
	{
		unsigned short j;
		for(j = 0; j < 3; j++)
		{
			if((int)state.grid[i][j] == 10) printf("  ");
			else printf("%c ", state.grid[i][j]);
		}
		printf("\n");
	}
}

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
			
			if(current.grid[i][j] != 10)
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
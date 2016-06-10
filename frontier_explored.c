#include "node.h"
#include "share.h"
#include "frontier_explored.h"
#include <stdlib.h>

//Add a node to the frontier at the appropriate location.

void addNodeToFrontier(Node* node, List frontier)
{
	//Create a new node to add to the frontier.

	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->node = node;
	
	ListNode* current = frontier.first;
	
	//If the frontier is empty, make the new node the first node.
	//Else, insert where appropriate.
	
	if(current == NULL)
	{
		frontier.first = newNode;
		newNode->previous = NULL;
		newNode->next = NULL;
	}
	else
	{
		//Insert before the node that is greater than the new node.
	
		while(current->next != NULL && newNode->node->f < current->next->node->f)
			current = current->next;
			
		//Insert at the end if appropriate.
			
		if(current->next != NULL)
		{
			newNode->previous = current->next->previous;
			newNode->previous->next = newNode;
			current->next = newNode;
			newNode->next = current->next;
		}
		else
		{
			current->next = newNode;
			newNode->previous = current;
			newNode->next = NULL;
		}
		
	}
}

//Add a node to the explored set. Simply add to the beginning, since no order is needed.

void addNodeToExploredSet(Node* node, List exploredSet)
{
	//Create a new node to add to the frontier.

	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->node = node;
	
	newNode->next = exploredSet.first;
	newNode->previous = NULL;
	exploredSet.first->previous = newNode;
	exploredSet.first = newNode;
}

//Return the node at the top of the queue.

Node pop(List frontier)
{
	Node* retVal = frontier.first->node;
	frontier.first->next->previous = NULL;
	frontier.first = frontier.first->next;
	return *retVal;
}

//Search the frontier for a node with a given state.

Node* findStateInList(List listToSearch, Node nodeWithState)
{
	//Create a new node to add to the frontier.

	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->node = &nodeWithState;
	
	ListNode* current = listToSearch.first;
	
	//Continue looping until a match is found.
	
	boolean isEquivalent = compareStates(current->node->state, nodeWithState.state);
	while(!isEquivalent && current != NULL) 
	{
		current = current->next;
		isEquivalent = compareStates(current->node->state, nodeWithState.state);
	}
	return current->node;
	
}





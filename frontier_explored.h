#ifndef FRONTIER_EXPLORED_H
#define FRONTIER_EXPLORED_H

#include "node.h"

//Wrapper for node in list, contains pointer to next and previous

typedef struct listNode
{
	Node* node;
	struct listNode* next;
	struct listNode* previous;
} ListNode;

//list

typedef struct list
{
	ListNode* first;
} List;

//Add a node to the frontier at the appropriate location.

void addNodeToFrontier(Node* node, List frontier);

//Add a node to the explored set. Simply add to the beginning, since no order is needed.

void addNodeToExploredSet(Node* node, List exploredSet);

//Return the node at the top of the queue.

Node pop(List frontier);

//Search the frontier for a node with a given state.

Node* findStateInList(List listToSearch, Node nodeWithState);

#endif
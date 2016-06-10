#include "node.h"
#include "frontier_explored.h"
#include "userOps.h"
#include "share.h"
#include <stdlib.h>
#include <stdio.h>


//main function

int main()
{
	State start = getStartState();
	List frontier, explored;
	boolean goalFound = False;
	frontier.first = NULL;
	explored.first = NULL;
	
	State goal = getGoalState();
	Node goalNode;
	Node* firstNode = generateRoot(start, goal);
	addNodeToFrontier(firstNode, frontier);
	
	//Loop until the optimal path is found.
	
	while(frontier.first !=NULL)
	{
		Node expanded = pop(frontier);
		
		//If this is not a goal state, expand it.
		
		if(compareStates(expanded.state, goal)) 
		{	
			goalNode = expanded;
			goalFound = True;
		}
		else
		{
			expandNode(&expanded, goal);
			Node* child = expanded.firstChild;
			
			//Add each child to the frontier as long as it is not a duplicate. If it is, update parent information.
			
			while(child != NULL)
			{
				Node* duplicate = findStateInList(frontier, *child);
				if(duplicate) updateNodeAncestors(duplicate, child->parent);	
				else 
				{
					duplicate = findStateInList(explored, *child);
					if(duplicate) updateNodeAncestors(duplicate, child->parent);
					else addNodeToFrontier(child, frontier);
				}
				child = child->leftSibling;
			}
		}
		addNodeToExploredSet(&expanded, explored);
	}
		
	//Print out the path.
	
	if(goalFound) printPath(&goalNode);
	else printf("There is no solution.\n");
	
	//Exit.
	return(0);
}
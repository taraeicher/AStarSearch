/*Name: Tara Eicher
 *WSU ID: z847x563
*/

#define STEP_SIZE 1

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

typedef enum{False,True} boolean;

//pair of coordinates

typedef struct coordPair
{
	unsigned short x;
	unsigned short y;
} CoordinatePair;

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

//Get the start state from the user.

State getStartState();

//Get goal state from user.

State getGoalState();

//Print the path from the start to the goal.

void printPath(Node* goal);

//Print each value in the grid for a given state.

void printGrid(State state);

//Add a node to the frontier at the appropriate location.

void addNodeToFrontier(Node* node, List* frontier);

//Return the node at the top of the queue.

Node* pop(List* frontier);

//Search the frontier for a node with a given state.

Node* findStateInList(List* listToSearch, Node nodeWithState);

//Return the sum of manhattan distances for each point in the grid.

unsigned int heur(State current, State goal);

//Return the manhattan distance for two coordinate pairs.

unsigned short manhattanDistance(CoordinatePair current, CoordinatePair goal);

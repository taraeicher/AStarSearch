This program uses the A* search algorithm to solve an 8-puzzle given a start state and a goal state. The manhattan distance is used as the heuristic.

To execute the program:

	1. Issue "make" on the command line to compile.
	2. Issue "./eightPuzzle" on the command line.
	3. Type in the coordinates of your start position as prompted. Start from the left and move right for the
	   first row, then do the same for the other rows. For example:
		
			Enter the value for (1,1): 1
			Enter the value for (1,2): 3
			Enter the value for (1,3): 4
			Enter the value for (2,1): 8
			Enter the value for (2,2): 0
			Enter the value for (2,3): 5
			Enter the value for (3,1): 7
			Enter the value for (3,2): 2
			Enter the value for (3,3): 6
			
	4. Type in the coordinates of your goal position as prompted. Start from the left and move right for the
	   first row, then do the same for the other rows. For example:
	   
			Enter the value for (1,1): 1
			Enter the value for (1,2): 2
			Enter the value for (1,3): 3
			Enter the value for (2,1): 8
			Enter the value for (2,2): 0
			Enter the value for (2,3): 4
			Enter the value for (3,1): 7
			Enter the value for (3,2): 6
			Enter the value for (3,3): 5
			
Expected output:
	
	For the example given above, the output will be as follows:
	
		Solution:

		Step 0:
		1 3 4 
		8   5 
		7 2 6 
		Step 1:
		1 3 4 
		8 2 5 
		7   6 
		Step 2:
		1 3 4 
		8 2 5 
		7 6   
		Step 3:
		1 3 4 
		8 2   
		7 6 5 
		Step 4:
		1 3   
		8 2 4 
		7 6 5 
		Step 5:
		1   3 
		8 2 4 
		7 6 5 
		Step 6:
		1 2 3 
		8   4 
		7 6 5 
		
	For any case in which the start state and the goal state are the same, the output will be as follows:
	
		This puzzle is trivially solved.
		
	For a case that has no solution, the output will be as follows:
	
		There is no solution.


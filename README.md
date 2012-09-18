OthelloAgent
============

This is a simple Othello agent

This othello agent uses a search tree of depth 1 to search for the optimal move. 
Each player move is evaluated with a evaluation function that tries to maximize possible player moves and reduce the possible moves of the opponent
as well as trying to minimize the amount of player bricks that are adjacent to empty squares. 
The evaulation function also conciders positional importance such as corners.

Is it possible to make the agent unbeatable given unlimited time to calculate each move?
Lets say you could increase the depth of the search tree to be infinite depth and we would have infinite time to calculate the best possible move, it still comes down to how good the evaluation function is. At this moment a much better evaluation function would be needed in order to make the agent impossible to beat. If we really wanted an unbeatable agent we would have to make a total search over all solutions.

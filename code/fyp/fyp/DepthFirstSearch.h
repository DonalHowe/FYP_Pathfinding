/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "Cell.h"

// the depth first search class
class DepthFirstSearch
{
	// private class variables
private:

	// boolean to check if the goal has been found to terminate the search
	bool m_depthGoalFound = false;

	//timer to track the search time
	sf::Time m_depthfirstSearchTimer;

	// public class variables and methods
public:
	
	// returns the timer for DFS
	sf::Time& getTimer();

	// returns the termination condition
	bool& getDepthFound();

	// computes the path for depth first search
	void computeShortestPath(Cell* t_curr, Cell* t_goal, Grid* t_grid);

	// default constructor
	DepthFirstSearch();

	// default destructor
	~DepthFirstSearch();
};


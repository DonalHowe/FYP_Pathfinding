#pragma once
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "Cell.h"
class DepthFirstSearch
{
	bool depthGoalFound = false;

	sf::Time depthfirstSearchTimer;

public:
	
	// returns the timer for DFS
	sf::Time& getTimer();

	// returns the termination condition
	bool& getDepthFound();

	// computes the path for depth first search
	void computeShortestPath(Cell* t_curr, Cell* t_goal, Grid* t_grid);

	// constructor
	DepthFirstSearch();

	// destructor
	~DepthFirstSearch();
};


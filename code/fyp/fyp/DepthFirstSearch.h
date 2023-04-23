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

	// the clock used to track the time
	sf::Clock m_clock;

	// boolean to check if the goal has been found to terminate the search
	bool m_depthGoalFound = false;

	//timer to track the search time
	sf::Time m_depthfirstSearchTimer;

	// stops the timer reseting and any bools etc from doing so
	bool initComplete=false;

	// public class variables and methods
public:
	
	// returns the timer for DFS
	sf::Time& getTimer();

	// returns the termination condition
	bool& getDepthFound();

	// sets the timer bool
	void setTimerBool(bool t_b);

	// computes the path for depth first search
	void computeShortestPath(Cell* t_curr, Cell* t_goal, Grid* t_grid);

	void initDepth(Cell* t_curr, Cell* t_goal, Grid* t_grid);

	// default constructor
	DepthFirstSearch();

	// default destructor
	~DepthFirstSearch();
};


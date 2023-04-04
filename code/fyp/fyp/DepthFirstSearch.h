#pragma once
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "Cell.h"
class DepthFirstSearch
{
public:
	bool depthGoalFound = false;
	sf::Time depthfirstSearchTimer;
	void computeShortestPath(Cell* t_curr, Cell* t_goal, Grid* t_grid);
	DepthFirstSearch();
	~DepthFirstSearch();
};


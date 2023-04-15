/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include<stack>
#include<queue>

/// <summary>
/// compares the Gcost  of cell 1 against cell 2's Gcost to return the lower of the two  
/// this functor is used for dijkstras search  to return the lower g cost 
/// </summary>

class GCostComparer
{

public:

	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getGcost()) > (t_n2->getGcost());
	}
};


// the dijkstras search class 
class Dijkstras
{
	// private class variables
private:

	// boolean to check if the goal has been found termination condition
	bool m_djkstrasPathFound = false;

	// timer to track the time taken of the search
	sf::Time m_dijkstrasTimer;
	
	// public variables of the class
public:
	
	// returns the timer for DFS
	sf::Time& getTimer();

	// returns the termination condition
	bool& getDijkstrasPathFound();

	// computes the path for dijkstras search algorithm
	void computeShortestPath(Cell* t_start, Cell* t_Goal, Grid* t_grid);

	// default constructor
	Dijkstras();
	// default destructor
	~Dijkstras();
};


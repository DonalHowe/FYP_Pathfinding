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



class Dijkstras
{
	bool djkstrasPathFound = false;
	sf::Time DjkstrasTimer;
	
public:
	
	// returns the timer for DFS
	sf::Time& getTimer();

	// returns the termination condition
	bool& getDijkstrasPathFound();

	void computeShortestPath(Cell* t_start, Cell* t_Goal, Grid* t_grid);

	Dijkstras();
	~Dijkstras();
};


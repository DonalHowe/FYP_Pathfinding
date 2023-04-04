#pragma once
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "Cell.h"

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
	
	
public:
	bool djkstrasPathFound = false;
	sf::Time DjkstrasTimer;

	void computeShortestPath(Cell* t_start, Cell* t_Goal, Grid* t_grid);

	Dijkstras();
	~Dijkstras();
};


#pragma once
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <stack>s
#include "Cell.h"



class CostDistanceValueComparer
{

public:

	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getGcost() + t_n1->getHcost()) > (t_n2->getGcost() + t_n2->getHcost());
	}
};



class Astar
{
	//astar
	
	
public:
	sf::Time m_Astartimer;
	bool AstarDone = false;
	std::stack<Cell*> m_stack;

	void computeShortestPath(Cell*  t_start, Cell * t_goal,Grid* t_grid);
	Astar();
	~Astar();
};


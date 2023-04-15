#pragma once
// included libraries
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <queue>
#include <stack>


/// <summary>
/// compares the fcost  of cell 1 against cell 2's f cost to return the lower of the two  
/// this functor is used for astar to return the better f cost 
/// </summary>
class CostDistanceValueComparer
{

public:

	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getGcost() + t_n1->getHcost()) > (t_n2->getGcost() + t_n2->getHcost());
	}
};


// the astar class
class Astar
{
	// private variables and methods

	// this is the timer used to calculate the time until completion of the algorithm
	sf::Time m_Astartimer;

	// bool to control if the algorithm is done 
	bool AstarDone = false;
	
	// public methods and variables
public:
	// returns the timer
	sf::Time& getTimer();
	
	//returns the termination condition
	bool &getIfDone();

	// initilises the astar grid
	void AstarInit(Cell* t_finalGoal, Cell* t_StartCurr, Grid* t_grid);

	// computes the shortestPath for the astar search
	std::stack<Cell*> computeShortestPath(Cell*  t_start, Cell * t_goal,Grid* t_grid);

	// the stack to store the path astar has found 
	std::stack<Cell*> m_stack;

	// contructor
	Astar();

	//destructor
	~Astar();
};


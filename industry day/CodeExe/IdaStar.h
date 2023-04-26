

/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
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
class fcostValueThingy
{

public:

	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getGcost() + t_n1->getHcost()) > (t_n2->getGcost() + t_n2->getHcost());
	}
};


// the idastar class

class IdaStar
{

// private variables and methods

	// this is the timer used to calculate the time until completion of the algorithm
	sf::Time m_idaStartimer;

	// bool to control if the algorithm is done 
	bool m_IDAstarDone = false;

	// the initilised condition control
	bool initComplete = false;

	// public methods and variables
public:
	// returns the timer
	sf::Time& getTimer();

	//returns the termination condition
	bool& getIfDone();

	// initilises the idastar grid
	void IdAstarInit(Cell* t_finalGoal, Cell* t_StartCurr, Grid* t_grid);

	// computes the shortestPath for the idastar search
	int computeShortestPath(Cell* t_start, Cell* t_goal, double t_threshold, Grid* t_grid);

	//main function for ida star
	std::stack<Cell*>runIdaStar(Cell* t_start, Cell* t_goal, Grid* t_grid);

	// the threshold used for pruning
	double m_nextThreshold = 100;

	// the stack to store the path idastar has found 
	std::stack<Cell*> m_stack;

	// contructor
	IdaStar();

	//destructor
	~IdaStar();
};


#pragma once
#include <iostream>
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <queue>


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



class Astar
{
	//astar
	// this is the timer used to calculate the time until completion of the algorithm
	sf::Time m_Astartimer;
	// bool to control if the algorithm is done 
	bool AstarDone = false;
	
public:
	// returns the timer
	sf::Time& getTimer();
	
	//returns the termination condition
	bool &getIfDone();

	// initilises the astar grid
	void AstarInit(Cell* t_finalGoal, Cell* t_StartCurr, Grid* t_grid);
	// computes the shortestPath for the astar search
	void computeShortestPath(Cell*  t_start, Cell * t_goal,Grid* t_grid);
	// contructor
	Astar();
	//destructor
	~Astar();
};


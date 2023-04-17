/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
#include<queue>
#include"Cell.h"
#include"Grid.h"
#include<stack>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>


/// <summary>
/// compares the fcost  of cell 1 against cell 2's f cost to return the lower of the two  
/// this functor is used for astar to return the better f cost 
/// </summary>
class fcostComparer
{

public:

	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getGcost() + t_n1->getHcost()) > (t_n2->getGcost() + t_n2->getHcost());
	}
};


class JumpPointSearch
{
	// private class variables and functions
private:

	// this is the timer used to calculate the time until completion of the algorithm
	sf::Time m_JumpPointtimer;

	// bool to control if the algorithm is done 
	bool m_JumpPointSearchDone = false;

	// public class variables and functions
public:

	// returns the timer
	sf::Time& getTimer();

	//returns the termination condition
	bool& getIfDone();

	// initilises the grid for jump point search to function
	void JpsInit(Cell* t_start, Cell* t_goal, Grid* t_grid);

	// computes the shortest path using the jump point search pathfinding algorithm
	void computeShortestPath(Cell* t_start, Cell* t_goal, Grid* t_grid);

	// this function determines whether a cell is a forced neighbour and a jump point
	// for the algorithm
	void determineJumpPoints(Cell* t_current, Cell* t_neighbor, Cell* t_goal, Grid* t_grid, std::priority_queue<Cell*, std::vector<Cell*>, fcostComparer>& t_pq);

	std::vector<Cell*> getForcedNeighbors(Cell* t_cell, int t_dx, int t_dy, Grid* t_grid);

	// default constructor
	JumpPointSearch();

	// default destrucotor
	~JumpPointSearch();
};


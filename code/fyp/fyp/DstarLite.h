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
/// compares the first key against the second to return the smallest 
/// if there is a tie between the tow, it will return the higher in the priority queue
/// </summary>
/// 
class DstarKeyComparer {
public:
	bool operator()(const Cell* a, const Cell* b) const {
		if (a->m_key.first > b->m_key.first) {
			return true;
		}
		else if (a->m_key.first == b->m_key.first && a->m_key.second > b->m_key.second) {
			return true;
		}
		else {
			return false;
		}
	}
};

// dstar lite search class
class DstarLite
{
	//k_m = key modifier
	// it accounts for the moving of the start node which in turn would change the heuristic of further
	// away nodes  if this did not account for that change 
	float m_K_M;

	// timer for dstar  
	sf::Time m_dStarLiteTimer;

	// termination condition
	bool m_dstarGoalFound = false;

public:

	// returns the timer for DFS
	sf::Time& getTimer();

	// returns the termination condition
	bool& getDStarPathFound();
	
	// priority queue  tracks nodes which are being investigated
	std::priority_queue<Cell*, std::vector<Cell*>, DstarKeyComparer> U_pq;
	
	// the main function which handles moving of the start node and obstacle handling
	void DstarLiteMain(Cell* t_finalGoal, Cell* t_StartCurr,Grid * t_grid);

	// updates the costs of each node accordingly depending on the type of inconsistancy
	void updateVertex(Cell* currentCell, Cell* t_finalGoal,Grid * t_grid);

	// computes the shortest path and checks what type of inconsistancy is the node or if it is consistant 
	void ComputeShortestPath(Cell* t_start, Cell* t_StartCurrGrid,Grid * t_grid);

	// initilises the variables for dstar
	void initDstar(Cell* t_finalGoal, Cell* t_StartCurr,Grid * t_grid);

	// calculates the key for dstar
	std::pair<double, double> calculateDstarKey(Cell* t_StartCurr, Cell* t_finalGoal,Grid * t_grid);
	
	// s_last used to keep track of robots position on the grid 
	Cell* s_Last;
	
};


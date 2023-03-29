#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

#include "ScreenSize.h"
#include "Cell.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include "algorithmSwitcher.h"

#include <set>
#include <chrono>
#include <thread>
using namespace std;

// this functor compares the values for the keys owned by cells
class DstarKeyComparer {
public:
	bool operator()(const Cell* a, const Cell* b) const {
		if (a->m_key.first < b->m_key.first) {
			return true;
		}
		else if (a->m_key.first == b->m_key.first && a->m_key.second < b->m_key.second) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Grid
{
	Cell sampleCell;
	Cell* endPt;
	std::vector<Cell> m_GridVec;
	std::vector<int> t_path;
	bool m_status = false;
	int endId;
	int startId;


public:
	Grid();
	~Grid();
	
	
	// function that uses the id of a cell to return a ptr to the actual cell
	Cell* atIndex(int t_id);

	// just used for cell setup in grid
	Cell ptrCell;
	
	// grid size values
	float MAX_CELLS;
	int MAX_ROWS;
	int MAX_COLS;

	// the grid itself 
	std::vector<std::vector<Cell>> m_theTableVector;

	// if start and endpoints fo algorithms are chosen these two are modifies
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;

	// reaise the cost of walls and surrounding cells
	Cell* raiseCost(Cell* start, Cell* goal);

	//k_m is the maximun cost per move allowedand eps being the is an estimate on the cost to go to the goal
	const float EPS = 2.0f;
	 float K_M;
	const double M_INFINITY = std::numeric_limits<int>::max() / 10;

	// sets the neigbours/successors of a cell
	void setNeighbours(Cell* t_cell);

	// sets the predeeccessors of a cell
	void setPredecessors(Cell* t_cell);
	// sets up the grid and neccessary values for cells
	void setupGrid(int t_count);
	void render(sf::RenderWindow & t_window,sf::RenderWindow & t_windowAstar);
	

	// LPA*
	std::stack<Cell*> LPAStar(Cell* t_start, Cell* t_goal);
	void updateNode(Cell* node, Cell* Goal);
	sf::Time m_LpaStartimer;
	bool LPApathFound = false;

	// jps
	std::stack<Cell*> JumpPointSearch(Cell* t_start, Cell* t_goal);
	sf::Time m_JpsStartimer;
	
	// djkstras 
	std::stack<Cell*> Djkstras(Cell* t_start, Cell * t_goal);
	bool djkstrasPathFound = false;
	sf::Time DjkstrasTimer;

	// depth first search 
	std::stack<Cell*> depthfirstSearch(Cell* t_start,Cell* t_curr);
	bool depthGoalFound = false;
	sf::Time depthfirstSearchTimer;

	//astar
	std::stack<Cell*> m_stack;
	std::stack<Cell*> aStar(Cell* t_start, Cell* t_end);
	sf::Time m_Astartimer;
	bool AstarDone = false;


	//dstar lite
	
	
	std::priority_queue<Cell*, std::vector<Cell*>, DstarKeyComparer> U_pq;
	
	std::stack<Cell*> DstarLiteMain(Cell* t_finalGoal, Cell* t_StartCurr);
	void updateVertex(Cell* currentCell, Cell* t_finalGoal);
	void ComputeShortestPath(Cell* t_start, Cell* t_StartCurr);
	void initDstar(Cell* t_finalGoal, Cell* t_StartCurr);
	std::pair<double, double> calculateDstarKey(Cell* t_StartCurr, Cell* t_finalGoal);
	Cell* s_Last;
	sf::Time dStarLiteTimer;

};

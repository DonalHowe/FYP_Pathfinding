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


#include <chrono>
#include <thread>
using namespace std;


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
	bool AstarDone = false;
	float MAX_CELLS;
	int MAX_ROWS;
	int MAX_COLS;
	Cell* atIndex(int t_id);
	Cell ptrCell;
	sf::Time m_timer;
	sf::Time m_Astartimer;
	WhichAlgorithm m_chosenAlgortihm;
	bool algorithmDone = false;
	std::stack<Cell*> m_stack;
	std::stack<Cell*> aStar(Cell* t_start, Cell* t_end);
	double m_infinity = std::numeric_limits<int>::max() / 10;
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;
	std::vector<std::vector<Cell>> m_theTableVector;
	std::list<Cell*> closedList;
	bool goalfound=false;

	Cell* raiseCost(Cell* start, Cell* goal);
	bool LPApathFound = false;
	const float eps = 10.0f;
	const float k_m = 10.0f;


	void setNeighbours(Cell* t_cell);
	
	void setupGrid(int t_count);
	void render(sf::RenderWindow & t_window,sf::RenderWindow & t_windowAstar);
	void update(sf::Time & t_deltatime,WhichAlgorithm t_switcher,GridSize t_gridSizeState);
	void setPredecessors(Cell* t_cell, Cell* t_source);

	// LPA*
	std::stack<Cell*> LPAStar(Cell* t_start, Cell* t_goal);
	void updateNode(Cell* node, Cell* Goal);
	double getDistance(Cell* c1, Cell* c2) const;



	// jps

	std::stack<Cell*> JumpPointSearch(Cell* t_start, Cell* t_goal);
};


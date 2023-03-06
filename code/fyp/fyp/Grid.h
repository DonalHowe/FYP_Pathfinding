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
	std::list<Cell*> Dstar(Cell* start, Cell* goal);
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;
	std::vector<std::vector<Cell>> m_theTableVector;
	std::list<Cell*> closedList;
	

	Cell* raiseCost(Cell* start, Cell* goal);




	void setNeighbours(Cell* t_cell);
	
	void setupGrid(int t_count);
	void render(sf::RenderWindow & t_window,sf::RenderWindow & t_windowAstar);
	void update(sf::Time & t_deltatime,WhichAlgorithm t_switcher,GridSize t_gridSizeState);
	

	
};


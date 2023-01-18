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
	
	std::vector<Cell> m_GridVec;
	std::vector<std::vector<Cell>> m_theTableVector;
	std::vector<int> t_path;
	

	

	bool algorithmDone = false;
	bool m_status = false;
	int endId;
	int startId;
	
public:
	Grid();
	~Grid();
	int MAX_CELLS;
	int MAX_ROWS;
	int MAX_COLS;
	Cell* atIndex(int t_id);
	Cell ptrCell;
	WhichAlgorithm m_chosenAlgortihm;
	
	std::stack<Cell*> m_stack;
	std::stack<Cell*> aStar(Cell* t_start, Cell* t_end);
	vector<Cell*> Dstar(Cell* start, Cell* goal);
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;



	void setNeighbours(Cell* t_cell);
	void selectStartEndPos(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow & t_window,sf::RenderWindow & t_windowAstar);
	void update(sf::Time & t_deltatime,WhichAlgorithm t_switcher,GridSize t_gridSizeState);
	

	
};


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

using namespace std;

// this functor compares the values for the keys owned by cells

class Grid
{
	static Cell* m_cellrenders;
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
	sf::Font m_font;

	
	// function that uses the id of a cell to return a ptr to the actual cell
	Cell* atIndex(int t_id);

	// just used for cell setup in grid
	Cell ptrCell;
	
	// grid size values
	float MAX_CELLS;
	int numberOfRows;
	int numberOfCols;

	// the grid itself 
	std::vector<std::vector<Cell>> m_theTableVector;

	// if start and endpoints fo algorithms are chosen these two are modifies
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;

	const double M_INFINITY = std::numeric_limits<int>::max() / 10;

	// sets the neigbours/successors of a cell
	void setNeighbours(Cell* t_cell);

	// sets the predeeccessors of a cell
	void setPredecessors(Cell* t_cell);
	// sets up the grid and neccessary values for cells
	void setupGrid(int t_count);

	void render(sf::RenderWindow & t_window,sf::RenderWindow & t_windowAstar);
	

	//calculates the heuristic  value of the the cells inputed
	double heuristic(Cell* c1, Cell* c2);

	

	

	

};

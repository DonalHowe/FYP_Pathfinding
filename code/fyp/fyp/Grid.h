#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include "Cell.h"
#include <vector>




using namespace std;
/// <summary>
///   grid class which contains the grid itself which is a two dimesional grid 
/// </summary>

class Grid
{

	sf::Font m_font;

	// just used for cell setup in grid
	Cell *ptrCell;

	// grid size values
	int MAX_CELLS;
	int numberOfRows;
	int numberOfCols;


public:
	Grid();
	~Grid();

	void setMAXCELLS( int t_cellCount);
	void setColumns( int t_ColCount);
	void setRows( int t_rowCount);

	int& getMAXCELLS();
	int& getNumberOfRows();
	int& getnumberOfCols();

	// function that uses the id of a cell to return a ptr to the actual cell
	Cell* atIndex(int t_id);

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

	void render(sf::RenderWindow & t_window);
	
	//calculates the heuristic  value of the the cells inputed
	double heuristic(Cell* c1, Cell* c2);

};

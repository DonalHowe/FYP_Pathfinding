#pragma once
// libraries to be included
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
	// private variavles of the class
private:
	// font for the debug 
	sf::Font m_font;

	// just used for cell setup in grid
	Cell *m_ptrCell;

	// grid size values
	int m_maxCells;
	// the number of rows in the grid
	int m_numberOfRows;
	int m_numberOfCols;

	// public variables of the class
public:
	// default constructor
	Grid();

	// default destructor
	~Grid();

	// sets the max number of cells allowed in the grid
	void setMAXCELLS( int t_cellCount);

	// sets the max number of columns allowed in the grid
	void setColumns( int t_ColCount);

	// sets the max number of rows allowed in the grid
	void setRows( int t_rowCount);

	// resets the grid in transition
	void resetGrid();

	// returns the max number if cells allowed in the grid
	int& getMAXCELLS();

	// returns the max number if rows allowed in the grid
	int& getNumberOfRows();

	// returns the max number if columns allowed in the grid
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

	// render funcction which renders the grid
	void render(sf::RenderWindow & t_window);
	
	//calculates the heuristic  value of the the cells inputed
	double heuristic(Cell* c1, Cell* c2);

};

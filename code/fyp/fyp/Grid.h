#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

#include "ScreenSize.h"
#include "Cell.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
using namespace std;


class Grid
{
	
	Cell sampleCell;
	std::vector<Cell> m_GridVec;
	std::vector<std::vector<Cell>> m_theTableVector;
	static const int MAX_CELLS=2500;
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;
	bool m_reset = false;

	const static int MAX_ROWS=50;
	const static int MAX_COLS=50;

	std::vector<int> m_path;
	int endId;
	int startId;
	
	bool heatMapCreated = false;


public:
	Grid();
	Cell* atIndex(int t_id);
	Cell ptrCell;
	~Grid();
	std::stack<Cell*> m_stack;
	
	void setIntraversable();
	void setNeighbours(Cell* t_cell);
	void selectStartEndPos(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow & t_window);
	void update(sf::Time & t_deltatime);
	void setUpCellIDNumText(sf::Font& m_font);
	std::stack<Cell*> aStar(Cell* t_start,Cell* t_end);
	sf::Text gridNum[MAX_CELLS];

	bool pathfound = false;

};


#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

#include "ScreenSize.h"
#include "Cell.h"
#include <vector>
using namespace std;


class Grid
{
	
	std::vector<Cell> m_GridVec;
	const int MAX_CELLS=2500;
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;
	const static int MAX_ROWS=50;
	const static int MAX_COLS=50;

	Cell *atIndex(int t_id);
public:
	Grid();
	~Grid();
	void setNeighbours(Cell* t_cell);
	void selectStartEndPos(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow & t_window);
	void update(sf::Time & t_deltatime);

};


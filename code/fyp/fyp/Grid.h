#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

#include "ScreenSize.h"
#include "Cell.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "algorithmSwitcher.h"
using namespace std;


class Grid
{
	
	Cell sampleCell;
	WhichAlgorithm m_chosenAlgortihm;
	std::vector<Cell> m_GridVec;
	std::vector<std::vector<Cell>> m_theTableVector;

	static const int MAX_CELLS=2500;
	bool m_startPosChosen = false;
	bool m_endPosChosen = false;
	
	const static int MAX_ROWS=50;
	const static int MAX_COLS=50;

	int endId;
	int startId;
	
public:
	Grid();
	~Grid();
	
	Cell* atIndex(int t_id);
	Cell ptrCell;
	
	std::stack<Cell*> m_stack;
	std::stack<Cell*> aStar(Cell* t_start, Cell* t_end);
	
	sf::Text gridNum[MAX_CELLS];
	
	void setIntraversable();
	void setNeighbours(Cell* t_cell);
	void selectStartEndPos(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow & t_window);
	void update(sf::Time & t_deltatime,WhichAlgorithm t_switcher);
	void setUpCellIDNumText(sf::Font& m_font);
	
};


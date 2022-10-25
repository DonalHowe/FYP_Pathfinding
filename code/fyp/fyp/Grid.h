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
public:
	Grid();
	~Grid();
	void selectStartEndPos(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow & t_window);
	void update(sf::Time & t_deltatime);

};


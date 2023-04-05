#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "algorithmSwitcher.h"
#include "Grid.h"
#include "Cell.h"
class Menu
{
	GridSize m_gridSwitcher;
	WhichAlgorithm m_slgSwitcher;
	Race m_raceDecider=Race::No;
	debug m_debugDecider=debug::Off;

	sf::RectangleShape m_rect;
	std::vector<sf::RectangleShape> m_rectVec;
	
	sf::Font m_font;
	sf::Text m_text[13];


public:
	Menu();
	~Menu();

	WhichAlgorithm& getalg();

	Race& getRaceStatus();
	debug& getdebugStatus();
	std::vector<sf::RectangleShape> getVec();

	GridSize& setGridSize(sf::RenderWindow & t_windowTwo, Grid & t_grid, Grid& t_gridTwo, Cell *t_cell);

	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
};


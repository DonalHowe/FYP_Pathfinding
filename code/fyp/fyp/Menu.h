#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "algorithmSwitcher.h"
#include "Grid.h"
class Menu
{

	sf::RectangleShape m_rect;
	std::vector<sf::RectangleShape> m_rectVec;
	GridSize m_gridSwitcher;
	WhichAlgorithm m_slgSwitcher;
	sf::Font m_font;
	sf::Text m_text[6];
	sf::RenderWindow m_window;
public:
	Menu();
	~Menu();
	GridSize setGridSize(sf::RenderWindow & t_windowTwo, Grid & t_grid);
	std::vector<sf::RectangleShape> getVec();
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
};


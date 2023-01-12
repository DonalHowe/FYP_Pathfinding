#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "algorithmSwitcher.h"
class Menu
{

	sf::RectangleShape m_rect;
	std::vector<sf::RectangleShape> m_rectVec;
	GridSize m_gridSwitcher;

public:
	Menu();
	~Menu();
	GridSize setGridSize(sf::RenderWindow & t_windowTwo);
	std::vector<sf::RectangleShape> getVec();
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
};


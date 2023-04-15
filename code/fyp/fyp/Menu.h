#pragma once
// libraires to be included
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include "algorithmSwitcher.h"
#include "Grid.h"
#include "Cell.h"

// menu class 
class Menu
{
	// objects used inside of the menu class
	GridSize m_gridSwitcher;
	WhichAlgorithm m_slgSwitcher;
	Race m_raceDecider=Race::No;
	debug m_debugDecider=debug::Off;

	// sf::rectangle shape
	sf::RectangleShape m_rect;

	// vector which holds all of the rect shapes in the class
	std::vector<sf::RectangleShape> m_rectVec;
	
	// font used for the text
	sf::Font m_font;

	// all of the text objects used in the class
	sf::Text m_text[13];

	// publuc methods used inside of the class
public:

	//default constructor
	Menu();

	// default destructor
	~Menu();

	// returns which algorithm that has been chosen for use inside of the menu
	WhichAlgorithm& getalg();

	// reuturns if the algorithms are going to race or not
	Race& getRaceStatus();

	// returns if you can see the variable data for dstar lite
	debug& getdebugStatus();

	// returns the rectangle shapes used to make the menu
	std::vector<sf::RectangleShape> getVec();

	// returns the grid size chosen for use
	GridSize& setGridSize(sf::RenderWindow & t_windowTwo, Grid & t_grid, Grid& t_gridTwo, Cell *t_cell);

	// render function of the class 
	void render(sf::RenderWindow& t_window);
	
	// upadte function of the class
	void update(sf::Time t_deltaTime);
};


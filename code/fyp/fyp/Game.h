
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Grid.h"
#include "algorithmSwitcher.h"
#include "Menu.h"
#include "Cell.h"


class Game
{
public:
	Game();
	~Game();
		
	void run();
	WhichAlgorithm m_switcher=WhichAlgorithm::Astar;
	GridSize m_gridSizeState;
	bool clearPath = false;
private:
	bool invalidPath = false;
	bool newStartFound = false;
	bool newEndFound = false;
	bool SrtChosen = false;
	bool EndChosen = false;
	Cell* tempsEnd;
	Cell *m_cellVAR;
	std::stack<Cell*> m_stack;
	void pathChecker(Cell * t_start,Cell * t_end);
	Menu m_menu;
	Grid m_grid;
	sf::CircleShape m_player;
	sf::Font m_font;
	sf::RenderWindow m_window;
	sf::RenderWindow m_windowTwo;

	sf::RenderWindow m_windowAstar;
	int startCell;
	int EndCell;

	void processEvents();
	void movement();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	bool m_exitGame;

};

#endif 




#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Grid.h"
#include "algorithmSwitcher.h"
#include "Menu.h"

class Game
{
public:
	Game();
	~Game();
		
	void run();
	WhichAlgorithm m_switcher=WhichAlgorithm::Astar;
	GridSize m_gridSizeState;

private: 
	Menu m_menu;
	Grid m_grid;
	sf::CircleShape m_player;
	sf::Font m_font;
	sf::RenderWindow m_window;
	sf::RenderWindow m_windowTwo;

	sf::RenderWindow m_windowAstar;
	

	void processEvents();
	void movement();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	bool m_exitGame;

};

#endif 



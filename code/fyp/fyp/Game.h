
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Grid.h"

class Game
{
public:
	Game();
	~Game();
		
	void run();

private:

	Grid m_grid;
	sf::CircleShape m_player;
	sf::Font m_font;
	sf::RenderWindow m_window;

	void processEvents();
	void movement();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	bool m_exitGame;

};

#endif 



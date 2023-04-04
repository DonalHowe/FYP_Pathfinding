#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <fstream>

#include "ScreenSize.h"
#include "Grid.h"
#include "algorithmSwitcher.h"
#include "Menu.h"
#include "Cell.h"
#include "Astar.h"
#include "Dijkstras.h"
#include "DepthFirstSearch.h"
#include "LpaStar.h"
#include "DstarLite.h"



class Game
{

public:

	Game();
	~Game();
		
	WhichAlgorithm m_switcher;
	GridSize m_gridSizeState;
	Race m_raceState=Race::No;
	debug m_debugState=debug::Off;
	Astar m_astar;
	Dijkstras m_dijkstras;
	DepthFirstSearch m_depthFirstSearch;
	DstarLite m_dStarLite;
	LpaStar m_LpaStar;

	void run();
	
private:

	void PlayMode();
	void TestingMode();

	bool SrtChosen = false;
	bool EndChosen = false;
	bool m_exitGame;
	
	Cell* tempsEnd;
	Cell* tempstart;
	Cell* tempstartTwo;
	Cell* tempsEndTwo;
	Cell *m_cellVAR;
	
	Menu m_menu;

	Grid m_grid;
	Grid m_gridTwo;
	
	sf::RenderWindow m_window;
	sf::RenderWindow m_windowTwo;
	sf::RenderWindow m_windowAstar;

	ofstream outputData;
	
	Mode m_mode=Mode::PLAY;

	int startCell;
	int startCellTwo;
	int EndCell;
	int EndCellTwo;

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseInput(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
};





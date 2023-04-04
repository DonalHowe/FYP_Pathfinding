

#define GAME_HPP


#include <SFML/Graphics.hpp>
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
#include <fstream>
#include <thread>
#include <chrono>



class Game
{
public:
	Game();
	~Game();
		
	void run();
	WhichAlgorithm m_switcher;
	GridSize m_gridSizeState;
	Astar m_astar;
	Dijkstras m_dijkstras;
	DepthFirstSearch m_depthFirstSearch;
	DstarLite m_dStarLite;
	LpaStar m_LpaStar;
	bool clearPath = false;

	void PlayMode();
	void TestingMode();
private:
	sf::Time m_colourTimer;
	sf::Clock m_timerClock;



	bool temp = false;
	bool SrtChosen = false;
	bool EndChosen = false;
	

	std::stack<Cell*> lpaStarStack;
	std::stack<Cell*> DStarLiteStack;

	Cell* tempsEnd;
	Cell* tempstart;
	Cell* tempstartTwo;
	Cell* tempsEndTwo;
	Cell *m_cellVAR;
	std::stack<Cell*> m_stack;

	Menu m_menu;
	Grid m_grid;
	Grid m_gridTwo;
	sf::CircleShape m_player;
	sf::Font m_font;
	sf::RenderWindow m_window;
	sf::RenderWindow m_windowTwo;
	ofstream outputData;
	sf::RenderWindow m_windowAstar;
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
	
	bool m_exitGame;

};

//#endif 



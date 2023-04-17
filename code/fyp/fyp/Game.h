/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

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
#include <chrono>
#include <stack>
#include <thread>



class Game
{
	// public variables and methods of the class
public:

	// default constuctor
	Game();
	
	// default destructor
	~Game();
	
	// objects used inside of the class
	WhichAlgorithm m_switcher;
	GridSize m_gridSizeState;
	Race m_raceState=Race::No;
	debug m_debugState=debug::Off;
	Mode m_mode = Mode::PLAY;
	Astar m_astar;
	Dijkstras m_dijkstras;
	DepthFirstSearch m_depthFirstSearch;
	DstarLite m_dStarLite;
	LpaStar m_LpaStar;
	Menu m_menu;
	Grid m_grid;
	Grid m_gridTwo;

	
	void run();
	// controls wall placement 
	bool m_temp = false;
private:

	// if game is in play mode you can place walls and star and end position
	void PlayMode();
	// all start and end points are random including wall placement
	void TestingMode();

	// booleans to set start and endpoints of a path
	bool m_SrtChosen = false;
	bool m_EndChosen = false;
	bool temp = false;
	bool tempOne = false;

	bool m_exitGame;
	
	// cell pointers for path construction
	Cell* m_tempsEnd;
	Cell* m_tempstart;
	Cell* m_tempstartTwo;
	Cell* m_tempsEndTwo;
	Cell *m_cellVAR;

	// stack to draw the path
	std::stack<Cell*> m_AstarStack;
	
	// the different windows used in the application
	sf::RenderWindow m_window;
	sf::RenderWindow m_windowTwo;
	sf::RenderWindow m_windowAstar;

	// for inputing data into the excell files
	ofstream m_outputData;
	
	
	// tracks the start and end cells chosen for both grids
	int m_startCelI_Id;
	int m_startCellTwo_Id;
	int m_EndCell_Id;
	int m_EndCellTwo_Id;

	// game loop functions
	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseInput(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
};





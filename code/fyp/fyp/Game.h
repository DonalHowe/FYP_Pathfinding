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
#include "JumpPointSearch.h"
#include "IdaStar.h"



class Game
{
	// public variables and methods of the class
public:

	// default constuctor
	Game();
	
	// default destructor
	~Game();
	
	// objects used inside of the class
		// which algorithm is being used controller
	WhichAlgorithm m_switcher;
		// which grid size is being used controller
	GridSize m_gridSizeState;
		// if the algorithms are to be raced controller
	Race m_raceState=Race::No;
		// if the debug visual is on or off controller
	debug m_debugState=debug::Off;
		// if the app is in play or test mode controller
	Mode m_mode = Mode::PLAY;
		// astar object
	Astar m_astar;
		// Dijkstras object
	Dijkstras m_dijkstras;
		// DepthFirstSearch object
	DepthFirstSearch m_depthFirstSearch;
		// DstarLite object
	DstarLite m_dStarLite;
		// LpaStar object
	LpaStar m_LpaStar;
		// Menu object
	Menu m_menu;
		// Grid object for first screen
	Grid m_grid;
		// Grid object for second screen
	Grid m_gridTwo;
		// JumpPointSearch object
	JumpPointSearch m_jps;
		// IdaStar object
	IdaStar m_ida;

	
	void run();
	// controls wall placement 
	bool m_temp = false;

	// private member variables of the class
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





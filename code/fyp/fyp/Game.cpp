
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT, 32U }, "Ai Labs" }, m_exitGame{ false },
	m_windowTwo{ sf::VideoMode{ ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT, 32U }, "Menu" },
	m_windowAstar{ sf::VideoMode{ ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT, 32U }, "Astar" }
	
{
	if (!m_font.loadFromFile("BebasNeue.otf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	
	m_player.setFillColor(sf::Color::Black);
	m_player.setRadius(10u);
}


Game::~Game()
{
	
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); 
	while (m_window.isOpen())
	{
		processEvents(); 
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); 
			update(timePerFrame); 
		}
		render(); 
	}
}


void Game::processEvents()
{
	sf::Event newEvent;
	
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) 
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) 
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseInput(newEvent);
		}
	}
}
void Game::movement()
{

	
	for (int i = 0; i < m_grid.m_stack.size(); i++)
	{
		
		if (m_player.getPosition().x > m_grid.m_stack.top()->getRect().getPosition().x)
		{
			m_player.move(-1, 0);
		}


		if (m_player.getPosition().x < m_grid.m_stack.top()->getRect().getPosition().x)
		{
			m_player.move(1, 0);
		}


		if (m_player.getPosition().y > m_grid.m_stack.top()->getRect().getPosition().y)
		{
			m_player.move(0, -1);
		}


		if (m_player.getPosition().y < m_grid.m_stack.top()->getRect().getPosition().y)
		{
			m_player.move(0, 1);
		}
		
	}
	
}
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	

	
}
void Game::processMouseInput(sf::Event t_event)
{

	sf::Vector2f m_QMousePos = sf::Vector2f{ sf::Mouse::getPosition(m_window) };
	if (m_gridSizeState == GridSize::small || m_gridSizeState == GridSize::large || m_gridSizeState == GridSize::veryLarge)
	{
		//mouse click
		
			if (sf::Mouse::Left == t_event.key.code)
			{
				for (int j = 0; j < m_grid.MAX_ROWS; j++)
				{
					for (int i = 0; i < m_grid.MAX_COLS; i++)
					{
						if (m_grid.m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_QMousePos))
						{
							m_grid.m_theTableVector.at(i).at(j).setStartColour();
							m_grid.m_theTableVector.at(i).at(j).setStartPoint(true);
							startCell = m_grid.m_theTableVector.at(i).at(j).getID();
							m_grid.ptrCell = m_grid.m_theTableVector.at(i).at(j);
							SrtChosen = true;
						}
					}
				}
			}
		


		
			if (sf::Mouse::Right == t_event.key.code)
			{
				for (int j = 0; j < m_grid.MAX_ROWS; j++)
				{
					for (int i = 0; i < m_grid.MAX_COLS; i++)
					{
						if (m_grid.m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_QMousePos))
						{
							m_grid.m_theTableVector.at(i).at(j).setEndColour();
							m_grid.m_theTableVector.at(i).at(j).setEndPoint(true);
							EndCell = m_grid.m_theTableVector.at(i).at(j).getID();
							EndChosen = true;
						}
					}
				}
			}
		


		
			if (sf::Mouse::Middle == t_event.key.code)
			{
				for (int j = 0; j < m_grid.MAX_ROWS; j++)
				{
					for (int i = 0; i < m_grid.MAX_COLS; i++)
					{
						if (m_grid.m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_QMousePos))
						{

							m_grid.m_theTableVector.at(i).at(j).setTraversable(false);
							m_grid.LPApathFound = false;
							m_grid.depthGoalFound = false;
							m_grid.djkstrasPathFound = false;
							temp = false;
							invalidPath = true;

						}
					}
				}
			}
		
	}
}

void Game::update(sf::Time t_deltaTime)
{


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_mode = Mode::PLAY;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		m_mode = Mode::TESTING;
	}
	m_menu.update(t_deltaTime);
	m_gridSizeState = m_menu.setGridSize(m_windowTwo, m_grid, m_cellVAR);
	m_switcher = m_menu.getalg();
	

	
	if (m_mode == Mode::PLAY)
	{
		if (SrtChosen == true && EndChosen == true)
		{
			if (m_switcher == WhichAlgorithm::Astar) {

				tempstart = m_grid.atIndex(startCell);
				tempsEnd = m_grid.atIndex(EndCell);

			}

			m_grid.aStar(tempstart, tempsEnd);

			/*if (temp == false && m_grid.LPApathFound == false)
			{


				lpaStarStack = m_grid.LPAStar(tempstart, tempsEnd);
				while (!lpaStarStack.empty())
				{
					Cell* l = lpaStarStack.top();
					l->setColor(sf::Color::Black);
					lpaStarStack.pop();
				}
			}*/

			//if (temp == false && m_grid.djkstrasPathFound == false)
			//{
			//	m_grid.Djkstras(tempstart, tempsEnd);
			//	temp = true;

			//}
			
			//m_grid.depthfirstSearch(tempstart, tempsEnd);
			
			/// <summary>
			///  testing for Dstar Lite
			/// </summary>
			/// <param name="t_deltaTime"></param>
			/*if (m_switcher == WhichAlgorithm::Astar)
			{
				m_grid.aStar(tempstart, tempsEnd);

				std::string AstarResult = std::to_string((m_grid.m_Astartimer.asSeconds()));
				outputData.open("AstarTime.csv");
				outputData << AstarResult;
				outputData.close();

			}*/
			/// <summary>
			///  testing for Dstar Lite
			/// </summary>
			/// <param name="t_deltaTime"></param>
			/*if (m_switcher == WhichAlgorithm::DstarLite)
			{


			}
			/// <summary>
			///  testing for Best First search
			/// </summary>
			/// <param name="t_deltaTime"></param>
			if (m_switcher == WhichAlgorithm::BestFirstSearch)
			{

			}
			/// <summary>
			///  testing for depthFirstSearch
			/// </summary>
			/// <param name="t_deltaTime"></param>
			if (m_switcher == WhichAlgorithm::DEPTH)
			{
				if (temp == false && m_grid.depthGoalFound == false)
				{
					m_grid.depthfirstSearch(tempstart, tempsEnd);
				}


			}
			/// <summary>
			///  testing for djkstras
			/// </summary>
			/// <param name="t_deltaTime"></param>
			if (m_switcher == WhichAlgorithm::DIKSTRAS)
			{
				m_grid.Djkstras(tempstart, tempsEnd);

			}
			/// <summary>
			///  testing for ipa star
			/// </summary>
			/// <param name="t_deltaTime"></param>
			if (m_switcher == WhichAlgorithm::LPASTAR)
			{
				
				


			}

			/// <summary>
			///  testing for djkstras
			/// </summary>
			/// <param name="t_deltaTime"></param>
			if (m_switcher == WhichAlgorithm::JPS)
			{
				m_grid.JumpPointSearch(tempstart, tempsEnd);

			}

			/// <summary>
			///  testing for IDA STAR
			/// </summary>
			/// <param name="t_deltaTime"></param>
			if (m_switcher == WhichAlgorithm::ida)
			{
				

			}*/

		

		}

		
	}
	/// <summary>
	/// this has random start and end position to avoid bias 
	/// </summary>
	/// <param name="t_deltaTime"></param>
	if (m_mode == Mode::TESTING)
	{
		srand((time(NULL)));
		if (m_gridSizeState == GridSize::small)
		{
			
			tempstart = m_grid.atIndex(rand() % 2200 + 1);
			tempsEnd = m_grid.atIndex(rand() % 2200 + 1);
			
			
		}

		if (m_gridSizeState == GridSize::large)
		{
			tempstart = m_grid.atIndex(rand() % 6000 + 1);
			tempsEnd = m_grid.atIndex(rand() % 6000 + 1);

		}

		if (m_gridSizeState == GridSize::veryLarge)
		{
			tempstart = m_grid.atIndex(rand() % 20000 + 1);
			tempsEnd = m_grid.atIndex(rand() % 20000 + 1);
		}

		
		if (m_grid.AstarDone == false)
		{
			m_grid.aStar(tempstart, tempsEnd);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			m_grid.AstarDone = false;
		}

		
		
	}






	
	
	

}


void Game::render()
{
	m_window.clear(sf::Color::White);
	m_windowTwo.clear(sf::Color::White);
	m_grid.render(m_window, m_windowAstar);

	m_menu.render(m_windowTwo);
	m_window.draw(m_player);
	m_window.display();
	m_windowTwo.display();
	m_windowAstar.display();

}




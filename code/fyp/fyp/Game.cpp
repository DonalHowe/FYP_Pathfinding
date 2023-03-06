
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

void Game::pathChecker(Cell * t_start,Cell* t_end)
{
	

	

	// check if the path has an intraversable or not
	if (m_grid.closedList.size() != 0)
	{
		
		// checking for the first intraversable 
		for (auto firstIntraversable = m_grid.closedList.begin();
			firstIntraversable != m_grid.closedList.end();
			firstIntraversable++)
		{
			// getting one previous of the intraversable
			if ((*firstIntraversable)->getTraversable() == false)
			{
				t_start = (*firstIntraversable)->GetPrev();
				invalidPath = true;
		
				
			}
			
		}
		// reverse the list
		m_grid.closedList.reverse();
		// get the one after the intraversable
		for (auto endIntraversable = m_grid.closedList.begin();
			endIntraversable != m_grid.closedList.end();
			endIntraversable++)
		{
			// getting one previous of the intraversable
			if ((*endIntraversable)->getTraversable() == false)
			{
				t_end = (*endIntraversable)->GetPrev();
				invalidPath = true;
				
			}

		}
		m_grid.closedList;
		int o = 0;
		// want to remove the intraversable from the closed list
		for (auto removeIntraversable = m_grid.closedList.begin();
			removeIntraversable != m_grid.closedList.end();
			removeIntraversable++)
		{
			if ((*removeIntraversable)->getTraversable() == false)
			{
				(*removeIntraversable)->inclosedList = false;
				
				m_grid.closedList.remove(*removeIntraversable);

				break;
			}
		}
		
		

	}
	
	// if the path is invalid 
	if (invalidPath == true&&temp==false)
	{
		std::cout <<" corrected list size "  << m_grid.closedList.size() << std::endl;
		m_grid.Dstar(t_start, t_end);
		temp = true;
	}
	//if the path is valid 
	if (invalidPath==false&&m_grid.algorithmDone==false)
	{
		std::cout << "  " << t_start->getID() << " , " << t_end->getID() << std::endl;
		m_grid.Dstar(t_start, t_end);
	}
	
    // colour the  path returned by Dstar
	for (auto itr = m_grid.closedList.begin();
			itr != m_grid.closedList.end();
			itr++)
	{
			if ((*itr) != t_start || (*itr) != t_end)
			{
				(*itr)->setColor(sf::Color::Green);
			}
	}
	if (m_grid.algorithmDone == true)
	{
		m_grid.m_timer;
		std::string result = std::to_string((m_grid.m_timer.asSeconds()));
		outputData.open("DstarTime.csv");
		outputData << result;
		outputData.close();
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


void Game::update(sf::Time t_deltaTime)
{
	
	m_menu.update(t_deltaTime);
	m_gridSizeState = m_menu.setGridSize(m_windowTwo, m_grid, m_cellVAR);
	m_grid.update(t_deltaTime, m_switcher, m_gridSizeState);
	
	if (m_gridSizeState == GridSize::small|| m_gridSizeState == GridSize::large||m_gridSizeState == GridSize::veryLarge)
	{
		sf::Vector2f m_MousePos = sf::Vector2f{ sf::Mouse::getPosition(m_window) };

		for (int i = 0; i < m_grid.MAX_ROWS; i++)
		{
			for (int j = 0; j < m_grid.MAX_COLS; j++)
			{
				if (m_grid.m_theTableVector.size() != 0)
				{

					if (m_grid.m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_MousePos))
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{

							m_grid.m_theTableVector.at(i).at(j).setStartColour();
							m_grid.m_theTableVector.at(i).at(j).setStartPoint(true);
							startCell = m_grid.m_theTableVector.at(i).at(j).getID();
							m_grid.ptrCell = m_grid.m_theTableVector.at(i).at(j);
							SrtChosen = true;

						}

						if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
						{

							m_grid.m_theTableVector.at(i).at(j).setEndColour();
							m_grid.m_theTableVector.at(i).at(j).setEndPoint(true);
							EndCell = m_grid.m_theTableVector.at(i).at(j).getID();
							EndChosen = true;

						}


						 
						if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
						{
							m_grid.m_theTableVector.at(i).at(j).setTraversable(false);
							temp = false;
							
						}


					}

				}
			}
		}
		if (SrtChosen == true && EndChosen == true)
		{
			if (m_switcher == WhichAlgorithm::Astar) {
				 tempstart = m_grid.atIndex(startCell);
				 tempsEnd = m_grid.atIndex(EndCell);
				 //pathChecker(tempstart, tempsEnd);
				 m_grid.aStar(tempstart, tempsEnd);
				 std::cout << "start "<<tempstart->getID() << std::endl;
				 std::cout << " end "<<tempsEnd->getID() << std::endl;
				 std::string AstarResult = std::to_string((m_grid.m_Astartimer.asSeconds()));
				 outputData.open("AstarTime.csv");
				 outputData << AstarResult;
				 outputData.close();
				 int q = 0;
			}
			if (m_switcher == WhichAlgorithm::Dstar)
			{
				Cell* tempstart = m_grid.atIndex(startCell);
				 tempsEnd = m_grid.atIndex(EndCell);
				
			}
		}
	}
		
	
	while (m_stack.size()!=0)
	{
		
		
			m_stack.pop();

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




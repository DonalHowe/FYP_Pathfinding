#include "Grid.h"

Grid::Grid()
{
	setupGrid();
	
	
}

Grid::~Grid()
{
}

void Grid::selectStartEndPos(sf::RenderWindow & t_window)
{
	const  sf::RenderWindow& m_window = t_window;
	sf::Vector2f m_MousePos = sf::Vector2f{ sf::Mouse::getPosition(m_window) };


	for (int i = 0; i < MAX_CELLS; i++)
	{
		if (m_GridVec.at(i).getRect().getGlobalBounds().contains(m_MousePos))
		{
			if (m_startPosChosen == false)
			{
				// for the start position  for the algorithim
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					cout << std::to_string(m_GridVec.at(i).getID()) << endl;
					m_GridVec.at(i).setStartColour();
					m_startPosChosen = true;
				}
			}
			
			if (m_endPosChosen == false)
			{
				// for the start position  for the algorithim
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					cout << std::to_string(m_GridVec.at(i).getID()) << endl;
					m_GridVec.at(i).setEndColour();
					m_endPosChosen = true;
				}
			}
			
		}
	}
	
}

void Grid::setupGrid()
{
	int j = 0;
	sf::Vector2f pos{ 0.0f,0.f };
	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell m_cell;
		m_cell.initRect();
		m_cell.setPos(pos);
		pos.x += m_cell.getRect().getSize().x;
		if (pos.x == ScreenSize::M_WIDTH)
		{
			pos.y += m_cell.getRect().getSize().y;
			pos.x = 0;
		}
		m_GridVec.push_back(m_cell);
		m_GridVec.at(i).setID(j);
		j++;
	}

	int i = 0;
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		t_window.draw(m_GridVec.at(i).getRect());
	}
	
}

void Grid::update(sf::Time& t_deltatime)
{
	
}

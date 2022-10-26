#include "Grid.h"

Cell* Grid::atIndex(int t_id)
{
	int x = t_id % MAX_ROWS;
	int y = t_id / MAX_COLS;
	// does
	int total = x + (y * MAX_COLS);
	return 	&m_GridVec.at(total);
}

Grid::Grid()
{
	setupGrid();
	Cell theCell;
	theCell.setID(901);
	theCell.setStartColour();
	setNeighbours(&theCell);

	int i = 0;
}

Grid::~Grid()
{
}

void Grid::setNeighbours(Cell* t_cell)
{
	int row = t_cell->xPos;
	int col = t_cell->yPos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {

			int id = n_row + (n_col * 50);
			t_cell->setNeighbours(atIndex(id));
			//std::cout <<"ID"<<id<< " Neighbor: " << n_row << "," << n_col << ": " << std::endl;		
		}
	}

		
	
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
					m_GridVec.at(i).setStartPoint(true);
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
					m_GridVec.at(i).setEndPoint(true);
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

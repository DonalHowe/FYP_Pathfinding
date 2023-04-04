#include "Grid.h"


double Grid::heuristic(Cell* c1, Cell* c2)
{
	int dx = abs(c1->Xpos - c2->Xpos);
	int dy = abs(c1->Ypos - c2->Ypos);
	int distance = sqrt(dx * dx + dy * dy);

	return c1->getWeight()*( distance);
}



Cell* Grid::atIndex(int t_id)
{
	int x = t_id / numberOfRows;
	int y = t_id % numberOfCols;
	
	return 	&m_theTableVector.at(y).at(x);
}

Grid::Grid()
{
	if (!m_font.loadFromFile("BebasNeue.otf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	
}

Grid::~Grid()
{
}

void Grid::setMAXCELLS(int t_cellCount)
{
	MAX_CELLS = t_cellCount;
}

void Grid::setColumns(int t_ColCount)
{
	numberOfCols = t_ColCount;
}

void Grid::setRows(int t_rowCount)
{
	numberOfRows = t_rowCount;
}

int& Grid::getMAXCELLS()
{
	return MAX_CELLS;
}

int& Grid::getNumberOfRows()
{
	return numberOfRows;
}

int& Grid::getnumberOfCols()
{
	return numberOfCols;
}

void Grid::setNeighbours(Cell* t_cell)
{
	int row = t_cell->Xpos;
	int col = t_cell->Ypos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < numberOfRows && n_col >= 0 && n_col < numberOfCols) {

			int id = n_row + (n_col * numberOfRows);// this is for the total number of rows you want in your grid i.e 50x50 or a 10x10
			t_cell->setNeighbours(&m_theTableVector.at(n_row).at(n_col));
			
		}
	}
		
}

void Grid::setPredecessors(Cell* t_cell)
{
	int row = t_cell->Xpos;
	int col = t_cell->Ypos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < numberOfRows && n_col >= 0 && n_col < numberOfCols) {

			int id = n_row + (n_col * numberOfRows); // Compute cell ID
			Cell* neighbor = &m_theTableVector.at(n_row).at(n_col);

			// Check if neighbor is traversable
			if (neighbor->getTraversable()==true) {

				// Calculate the new cost to reach the neighbor
				double new_cost = t_cell->getGcost() + distance(t_cell, neighbor);

				// Update the predecessor if the cost has improved
				if (new_cost < neighbor->getGcost()) {
					neighbor->setGcost(new_cost);
					neighbor->setPredecessorss(t_cell);

					// If neighbor is not in the open list, add it
					if (!neighbor->isInOpenList==false) {
						
						//m_openList.push(neighbor);
						neighbor->isInOpenList==true;
					}
				}
			}
		}
	}
}

void Grid::setupGrid(int t_Numbercols)
{
	m_theTableVector.clear();
	numberOfCols = t_Numbercols;
	numberOfRows = t_Numbercols;
	
	
	for (int i = 0; i < numberOfRows; i++)
	{
		std::vector<Cell> tempVec;
		m_theTableVector.push_back(tempVec);
	}


	int count = 0;
	float m_height = 0.0f;
	sf::Vector2f pos{ 0.0f,0.f };

	for (int rows = 0; rows < numberOfRows; rows++)
	{
		for (int cols = 0; cols < numberOfCols; cols++)
		{
			
			Cell tempNode;
			tempNode.setTraversable(true);
			tempNode.Xpos = cols;
			tempNode.Ypos = rows;
			tempNode.initRect(t_Numbercols);
			tempNode.setPos(pos);
			pos.x += tempNode.getRect().getSize().x;
			m_height= tempNode.getRect().getSize().y;
			tempNode.m_rhsText.setFont(m_font);
			tempNode.m_GcostText.setFont(m_font);
			tempNode.m_KeyText.setFont(m_font);
			tempNode.setID(count);
			count++;
			m_theTableVector.at(cols).push_back(tempNode);
		}
		pos.y += m_height;
		pos.x = 0;

	}
	

	for (int i = 0; i < MAX_CELLS; i++)
	{
		setNeighbours(atIndex(i));
		
	}
	for (int i = 0; i < MAX_CELLS; i++)
	{
		setPredecessors(atIndex(i));

	}


}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int row = 0; row < numberOfRows; row++)
	{
		for (int col = 0; col < numberOfCols; col++)
		{
			if (m_theTableVector.size() != 0)
			{
				t_window.draw(m_theTableVector.at(row).at(col).getRect());
				
			}
		}
	}
	
}



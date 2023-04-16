#include "Grid.h"
/// author : donal Howe
/// 

//calculates the heuristic  value of the the cells inputed
double Grid::heuristic(Cell* c1, Cell* c2)
{
	int dx = abs(c1->m_Xpos - c2->m_Xpos);
	int dy = abs(c1->m_Ypos - c2->m_Ypos);
	int distance = sqrt(dx * dx + dy * dy);

	return c1->getWeight()*( distance);
}

// function that uses the id of a cell to return a ptr to the actual cell
Cell* Grid::atIndex(int t_id)
{
	if (m_numberOfRows > m_maxCells)
	{
		m_numberOfRows = m_maxCells;
		m_numberOfCols = m_maxCells;
	}

		int x = t_id / m_numberOfRows;
		int y = t_id % m_numberOfCols;
		// if the x is greater than the total grid size i.e for downsizing this prevents error 
		// being thrown
		if (x > m_theTableVector.size())
		{
			x = 0;
		}
		else if (y > m_theTableVector.size())
		{
			y = 5;
		}
	
	if (&m_theTableVector.at(y).at(x) != nullptr)
	{
		return 	&m_theTableVector.at(y).at(x);
	}
	if (&m_theTableVector.at(y).at(x) == nullptr)
	{
		return 	&m_theTableVector.at(1).at(5);
	}
}

// default constructor loads the font 
Grid::Grid()
{
	if (!m_font.loadFromFile("BebasNeue.otf"))
	{
		std::string s("Error loading font");
		throw std::exception(s.c_str());
	}
	
}

// default destructor
Grid::~Grid()
{
}

// sets the max number of cells allowed in the grid
void Grid::setMAXCELLS(int t_cellCount)
{
	m_maxCells = t_cellCount;
}

// sets the max number of columns allowed in the grid
void Grid::setColumns(int t_ColCount)
{
	m_numberOfCols = t_ColCount;
}

// sets the max number of rows allowed in the grid
void Grid::setRows(int t_rowCount)
{
	m_numberOfRows = t_rowCount;
}

// resets the grid in transition between sizes
void Grid::resetGrid()
{
	
	for (int i = 0; i < m_maxCells; i++)
	{
		if (!m_theTableVector.empty())
		{


			Cell* v = atIndex(i);
			if (v != nullptr)
			{
				if (v->getEndPoint() != false)
				{
					v->setEndPoint(false);
				}
				if (v->GetPrev() != nullptr)
				{
					v->setPrev(nullptr);
				}
				if (v->getStartPoint() != false)
				{
					v->setStartPoint(false);
				}

				if (v->getTraversable() == false)
				{
					v->setTraversable(true);
					v->setColor(sf::Color::White);
				}


				if (!v->getNeighbours().empty())
				{
					v->getNeighbours().clear();
				}
				if (!v->getPredecessors().empty())
				{

					v->getPredecessors().clear();
				}
				if (v->m_isInOpenList == true)
				{
					v->m_isInOpenList = false;
				}
			}
		}
	}
}

// returns the max number if cells allowed in the grid
int& Grid::getMAXCELLS()
{
	return m_maxCells;
}

// returns the max number if rows allowed in the grid
int& Grid::getNumberOfRows()
{
	return m_numberOfRows;
}

// returns the max number if columns allowed in the grid
int& Grid::getnumberOfCols()
{
	return m_numberOfCols;
}

// sets the neigbours/successors of a cell
void Grid::setNeighbours(Cell* t_cell)
{
	int row = t_cell->m_Xpos;
	int col = t_cell->m_Ypos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < m_numberOfRows && n_col >= 0 && n_col < m_numberOfCols) {

			int id = n_row + (n_col * m_numberOfRows);// this is for the total number of rows you want in your grid i.e 50x50 or a 10x10
			t_cell->setNeighbours(&m_theTableVector.at(n_row).at(n_col));
			
		}
	}
		
}

// sets the predeeccessors of a cell
void Grid::setPredecessors(Cell* t_cell)
{
	int row = t_cell->m_Xpos;
	int col = t_cell->m_Ypos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < m_numberOfRows && n_col >= 0 && n_col < m_numberOfCols) {

			int id = n_row + (n_col * m_numberOfRows); // Compute cell ID
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
					if (!neighbor->m_isInOpenList==false) {
						
						//m_openList.push(neighbor);
						neighbor->m_isInOpenList==true;
					}
				}
			}
		}
	}
}

// sets up the grid and neccessary values for cells
void Grid::setupGrid(int t_Numbercols)
{
	m_theTableVector.clear();
	m_numberOfCols = t_Numbercols;
	m_numberOfRows = t_Numbercols;
	
	
	for (int i = 0; i < m_numberOfRows; i++)
	{
		std::vector<Cell> tempVec;
		m_theTableVector.push_back(tempVec);
	}


	int count = 0;
	float m_height = 0.0f;
	sf::Vector2f pos{ 0.0f,0.f };

	for (int rows = 0; rows < m_numberOfRows; rows++)
	{
		for (int cols = 0; cols < m_numberOfCols; cols++)
		{
			
			Cell tempNode;
			tempNode.setTraversable(true);
			tempNode.m_Xpos = cols;
			tempNode.m_Ypos = rows;
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
	

	for (int i = 0; i < m_maxCells; i++)
	{
		setNeighbours(atIndex(i));
		
	}
	for (int i = 0; i < m_maxCells; i++)
	{
		setPredecessors(atIndex(i));

	}


}

// render funcction which renders the grid
void Grid::render(sf::RenderWindow& t_window)
{
	for (int row = 0; row < m_numberOfRows; row++)
	{
		for (int col = 0; col < m_numberOfCols; col++)
		{
			if (m_theTableVector.size() != 0)
			{
				t_window.draw(m_theTableVector.at(row).at(col).getRect());
				
			}
		}
	}
	
}



#include "Grid.h"


class CostDistanceValueComparer
{

public:

		bool operator()(Cell* t_n1, Cell* t_n2) const
		{
			return (t_n1->getGcost() + t_n1->getHcost()) > (t_n2->getGcost() + t_n2->getHcost());
		}
};


void Grid::setUpCellIDNumText(sf::Font& m_font)
{
	/*for (int i = 0; i < MAX_CELLS; i++)
	{
		gridNum[i].setFont(m_font);
		gridNum[i].setScale(.5, .5);
		gridNum[i].setFillColor(sf::Color::Black);
	}*/
}

bool Grid::resetAstar()
{
	 m_startPosChosen = false;
	 m_endPosChosen = false;
	 m_status=true;
	 return false;
}

bool Grid::resetDStar()
{
	m_status = false;
	return false;
}

std::stack<Cell*> Grid::aStar(Cell* t_start, Cell* t_end)
{

	Cell* start = t_start;
	Cell* goal = t_end;
	std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer > pq;
	pq.empty();
	m_stack.empty();
	t_path.clear();
	int infinity = std::numeric_limits<int>::max() / 10;

	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		v->setPrev(nullptr);
		v->setHcost(abs(goal->xPos - v->xPos) + abs(goal->yPos - v->yPos));
		v->setMarked(false);
		v->setGcost( infinity);
		v->setWieght(10);
	}

	start->setGcost(0);
	
	pq.push(start);

	pq.top()->setMarked(true);

	while (pq.size() != 0 && pq.top() != goal)
	{
		Cell* topnode = pq.top();

		for (Cell* q : topnode->getNeighbours())
		{

			Cell* child = q;

			if (child != pq.top()->GetPrev())
			{

				int weight = child->getWeight();

				int distanceToChild = pq.top()->getGcost() + weight;

				if (distanceToChild < child->getGcost() && child->getTraversable() == true)
				{
					child->setGcost( distanceToChild);
					child->setPrev(pq.top());
				}
				if (child->getMarked() == false)
				{
					pq.push(child);
					child->setMarked(true);
				}
				
			}
		}

		pq.pop();
	}

	
	if (m_status == false)
	{
		Cell* pathNode = t_end;

		while (pathNode->GetPrev() != nullptr)
		{
			t_path.push_back(pathNode->getID());
			pathNode = pathNode->GetPrev();
			m_stack.push(pathNode);
		}

		for (int i = 0; i < t_path.size(); i++)
		{
			Cell* m = atIndex(t_path.at(i));
			m->getRect().setFillColor(sf::Color::Black);
		}
	}


	return m_stack;

}

vector<Cell*> Grid::Dstar(Cell* t_start, Cell* t_goal)
{
	


	Cell* start = t_start;
	Cell* goal = t_goal;
	std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer > pq;
	pq = std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer >();
	m_stack = std::stack<Cell*>();
	t_path.clear();
	int infinity = std::numeric_limits<int>::max() / 10;

	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		v->setPrev(nullptr);
		v->setHcost(abs(goal->xPos - v->xPos) + abs(goal->yPos - v->yPos));
		v->setMarked(false);
		v->setGcost(infinity);
		v->setWieght(10);
	}




	/*for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		if (v->getMarked() == true)
		{
			pq.push(v);
		}
	
	}*/
	start->setGcost(0);
	pq.push(start);
	pq.top()->setMarked(true);
	bool dstarPassed = false;

	//	Add the starting node to the priority queue, and mark it as visited.

	//	While the priority queue is not empty, do the following :
	while (pq.empty() == false)
	{
		
		Cell* lowest = pq.top();

		for (Cell* q : lowest->getNeighbours())
		{
			if (lowest->getHcost() < pq.top()->getHcost())
			{
				if (lowest == goal)
				{
					std::cout << "end goal found " << std::endl;
					dstarPassed = true;
					break;
				}
				else
				{
					if (lowest->getHcost() > lowest->getNeighbours().front()->getHcost())
					{
						pq.push(lowest->getNeighbours().front());
					}
				}
			}
			if (lowest->getTraversable() == false)
			{
				lowest->raiseCost(100);
			}
			if (lowest->getTraversable() == true)
			{
				lowest->lowerCost(10);
			}
		}
		pq.pop();
	}
	if (pq.empty() == true&&dstarPassed==false)
	{
		std::cout << "no path found" << std::endl;
	}

	return {};
}



Cell* Grid::atIndex(int t_id)
{
	int x = t_id % MAX_ROWS;
	int y = t_id / MAX_COLS;

	return 	&m_theTableVector.at(x).at(y);
}

Grid::Grid()
{
	setupGrid();
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

			int id = n_row + (n_col * MAX_ROWS);// this is for the total number of rows you want in your grid i.e 50x50 or a 10x10
			t_cell->setNeighbours(atIndex(id));
			
		}
	}
		
}

void Grid::selectStartEndPos(sf::RenderWindow & t_window)
{
	const  sf::RenderWindow& m_window = t_window;
	sf::Vector2f m_MousePos = sf::Vector2f{ sf::Mouse::getPosition(m_window) };
	
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			if (m_theTableVector.size() != 0)
			{

				if (m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_MousePos))
				{
					if (m_startPosChosen == false)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							std::cout << m_theTableVector.at(i).at(j).getID() << std::endl;
							m_theTableVector.at(i).at(j).setStartColour();
							m_theTableVector.at(i).at(j).setStartPoint(true);
							startId = m_theTableVector.at(i).at(j).getID();
							ptrCell = m_theTableVector.at(i).at(j);
							m_startPosChosen = true;

						}
					}
					if (m_endPosChosen == false)
					{
						// for the start position  for the algorithim
						if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
						{
							std::cout << m_theTableVector.at(i).at(j).getID() << std::endl;
							m_theTableVector.at(i).at(j).setEndColour();
							m_theTableVector.at(i).at(j).setEndPoint(true);
							endId = m_theTableVector.at(i).at(j).getID();
							m_endPosChosen = true;
						}

					}

					if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
					{
						m_theTableVector.at(i).at(j).setTraversable(false);
					}


				}

			}
		}
	}
	if (m_endPosChosen == true && m_startPosChosen == true)
	{
		Cell* endCell;
		Cell* StartCell;
		StartCell = atIndex(startId);
		endCell = atIndex(endId);
		if (m_chosenAlgortihm == WhichAlgorithm::Astar) {
			aStar(StartCell, endCell);
			//Dstar(StartCell,endCell);
			//Dstar(StartCell, endCell);
		}
		if (m_chosenAlgortihm == WhichAlgorithm::Dstar)
		{
			
			
			
		}
		
	}
}

void Grid::setupGrid()
{
	sf::Vector2f pos{ 0.0f,0.f };
	for (int i = 0; i < MAX_ROWS; i++)
	{
		std::vector<Cell> tempVec;
		m_theTableVector.push_back(tempVec);
	}

	for (int i = 0; i < MAX_CELLS; i++)
	{
		int x = i % MAX_ROWS;
		int y = i / MAX_COLS;
		Cell tempNode;
		tempNode.xPos = x;
		tempNode.yPos = y;
		tempNode.initRect();
		tempNode.setPos(pos);
		pos.x += tempNode.getRect().getSize().x;
		if (pos.x == ScreenSize::M_WIDTH)
		{
			pos.y += tempNode.getRect().getSize().y;
			pos.x = 0;
		}
		tempNode.setID(x + (y * MAX_ROWS));
		
		m_theTableVector.at(x).push_back(tempNode);
	}

	
	for (int i = 0; i < MAX_CELLS; i++)
	{
		setNeighbours(atIndex(i));
	}
	
	
	
}

void Grid::render(sf::RenderWindow& t_window, sf::RenderWindow& t_windowAstar)
{
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			if (m_theTableVector.size() != 0)
			{
				t_window.draw(m_theTableVector.at(j).at(i).getRect());
				t_windowAstar.draw(m_theTableVector.at(j).at(i).getRect());
			
			}
		}
	}
	/*for (int i = 0; i < MAX_CELLS; i++)
	{
		t_window.draw(gridNum[i]);
	}*/
}

void Grid::update(sf::Time& t_deltatime, WhichAlgorithm t_switcher,GridSize t_gridSizeState)
{
	m_chosenAlgortihm = t_switcher;

	if (m_chosenAlgortihm == WhichAlgorithm::Dstar)
	{
		std::cout << "DSTAR" << std::endl;
		resetAstar();
	}
	if (m_chosenAlgortihm == WhichAlgorithm::Astar)
	{
		std::cout << "ASTAR" << std::endl;
		resetDStar();
	}
	
	
}

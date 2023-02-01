#include "Grid.h"


class CostDistanceValueComparer
{

public:

		bool operator()(Cell* t_n1, Cell* t_n2) const
		{
			return (t_n1->getGcost() + t_n1->getHcost()) > (t_n2->getGcost() + t_n2->getHcost());
		}
};


std::stack<Cell*> Grid::aStar(Cell* t_start, Cell* t_end)
{
	if (t_start != nullptr && t_end != nullptr)
	{


		Cell* start = t_start;
		Cell* goal = t_end;
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
			if (v->getTraversable() == true)
			{
				v->setColor(sf::Color::White);
			}
		
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
						child->setGcost(distanceToChild);
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
		}

	}
	return m_stack;

}

std::stack<Cell*> Grid::Dstar(Cell* t_start, Cell* t_goal)
{
	


	Cell* start = t_start;
	Cell* goal = t_goal;
	std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer > pq;
	std::list<Cell*> m_raiseStates;
	
	pq= std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer >();
	m_stack=std::stack<Cell*>();
	t_path.clear();
	int infinity = std::numeric_limits<int>::max() / 10;

	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		v->setPrev(nullptr);
		v->setHcost(abs(goal->xPos - v->xPos) + abs(goal->yPos - v->yPos));
		v->setMarked(false);
		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}
		if (v->GetPrev() != nullptr)
		{
			v->setRHSCost(v->getHcost() + v->GetPrev()->getHcost());
		}
		
		v->setGcost(infinity);
		v->setWieght(10);
	}

	start->setGcost(0);

	pq.push(start);

	pq.top()->setMarked(true);

	while (pq.size() != 0 && pq.top() != goal)//&& algorithmDone ==false)
	{
		Cell* topnode = pq.top();

		for (Cell* q : topnode->getNeighbours())
		{

			Cell* child = q;

			if (child != pq.top()->GetPrev())//&& algorithmDone ==false)
			{
				
				if (child->GetLoweredBool() == false && child->GetRisenBool() == false)
				{

					if (child->getMarked() == false)
					{
						pq.push(child);
						if (child->getTraversable() == false)
						{
							if (m_raiseStates.empty() == true)
							{

								for (auto it = q->getNeighbours().begin(); it != q->getNeighbours().end(); it++) {
									if ((*it)->getTraversable() == true)
									{
										m_raiseStates.push_back(*it);
									}

								}

								for (std::list<Cell*>::iterator Raiseit = m_raiseStates.begin(); Raiseit != m_raiseStates.end(); Raiseit++)
								{
									(*Raiseit)->raiseCost(1000);
									(*Raiseit)->setRisenBool(true);
									(*Raiseit)->getRect().setFillColor(sf::Color::Cyan);
								}
								int z = 0;
							}
							m_raiseStates.clear();
							int sadasdsa = 0;
						}
						child->setMarked(true);
					}



					int weight = child->getWeight();

					int distanceToChild = pq.top()->getGcost() + weight;

					if (distanceToChild < child->getGcost() && child->getTraversable() == true)
					{
						child->setGcost(distanceToChild);
						child->setPrev(pq.top());
						if (child == goal)
						{
							child->getRect().setFillColor(sf::Color::Magenta);
							
							algorithmDone = true;
							
						}
					}
					
				}
				

			}
			

		}

		pq.pop();
	}

	if (m_status == false)
	{
		Cell* pathNode = t_goal;

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



Cell* Grid::atIndex(int t_id)
{
	int x = t_id % MAX_ROWS;
	int y = t_id / MAX_COLS;

	return 	&m_theTableVector.at(x).at(y);
}

Grid::Grid()
{
	//setupGrid();
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
	
	
}

void Grid::setupGrid(int t_c)
{
	m_theTableVector.clear();
	
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
		tempNode.initRect(t_c);
		tempNode.setPos(pos);
		pos.x += tempNode.getRect().getSize().x;
		if (pos.x > ScreenSize::M_WIDTH)
		{
			pos.y += tempNode.getRect().getSize().y;
			pos.x = 0;
		}
		tempNode.setID(x + (y * MAX_ROWS));
		
		m_theTableVector.at(x).push_back(tempNode);
	}

	std::cout << m_theTableVector.size() << std::endl;
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
				//t_windowAstar.draw(m_theTableVector.at(j).at(i).getRect());
			
			}
		}
	}
	
}

void Grid::update(sf::Time& t_deltatime, WhichAlgorithm t_switcher,GridSize t_gridSizeState)
{
	m_chosenAlgortihm = t_switcher;
	
}

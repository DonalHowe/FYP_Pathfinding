#include "Astar.h"
/// author : donal Howe
/// 


// returns the timer
sf::Time& Astar::getTimer()
{
	return m_Astartimer;
}

// returns the temination condition
bool& Astar::getIfDone()
{
	return m_AstarDone;
}

// initilises all of the necessary variables for astar
void Astar::AstarInit(Cell* t_start, Cell* t_goal, Grid* t_grid)
{
	for (int i = 0; i < t_grid->getMAXCELLS(); i++)
	{
		Cell* v = t_grid->atIndex(i);
		v->setPrev(nullptr);
		v->setHcost(t_grid->heuristic(v, t_goal));
		v->setMarked(false);
		v->setGcost(t_grid->M_INFINITY);
		v->setWieght(10);
		v->setFcost(v->getGcost()+v->getHcost());

		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}

	}
}

// computes the shortest path for astar
std::stack<Cell*> Astar::computeShortestPath(Cell* t_start, Cell* t_goal, Grid*  t_grid)
{

	sf::Clock m_clock;
	m_Astartimer.asSeconds();
	m_Astartimer = m_clock.restart();
	std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer >m_pq;
	m_pq = std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer >();
	

	if (t_start != nullptr && t_goal != nullptr)
	{
		Cell* start = t_start;
		Cell* goal = t_goal;
		AstarInit(start, goal,t_grid);
		start->setColor(sf::Color::Blue);
		start->setGcost(0);
		m_pq.push(start);
		m_pq.top()->setMarked(true);


		while (m_pq.size() != 0 && m_pq.top() != goal)
		{
			Cell* topnode = m_pq.top();

			for (Cell* q : topnode->getNeighbours())
			{

				Cell* child = q;

				if (child != m_pq.top()->GetPrev())
				{

					int weight = child->getWeight();

					int distanceToChild = m_pq.top()->getGcost() + weight;

					if (distanceToChild < child->getGcost() && child->getTraversable() == true)
					{
						child->setGcost(distanceToChild);
						child->setPrev(m_pq.top());
						if (child == goal)
						{
							child->setColor(sf::Color::Magenta);
							m_AstarDone = true;
							m_Astartimer = m_clock.getElapsedTime();
						}
					}
					if (child->getMarked() == false)
					{
						m_pq.push(child);

						child->setMarked(true);
					}

				}
			}

			m_pq.pop();
		}



		Cell* pathNode = t_goal;

		while (pathNode->GetPrev() != nullptr)
		{
			m_stack.push(pathNode);
			pathNode = pathNode->GetPrev();
			pathNode->setColor(sf::Color::Black);
			
		}
	}
	t_goal->setColor(sf::Color::Magenta);

	return m_stack;

}

// default constructor
Astar::Astar()
{
}

// default destructor
Astar::~Astar()
{
}

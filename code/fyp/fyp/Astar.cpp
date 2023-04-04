#include "Astar.h"



sf::Time& Astar::getTimer()
{
	return m_Astartimer;
}

bool& Astar::getIfDone()
{
	return AstarDone;
}

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

		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}

	}
}

void Astar::computeShortestPath(Cell* t_start, Cell* t_goal, Grid*  t_grid)
{

	sf::Clock m_clock;
	m_Astartimer.asSeconds();
	m_Astartimer = m_clock.restart();
	std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer > pq;
	pq = std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer >();
	

	if (t_start != nullptr && t_goal != nullptr)
	{
		Cell* start = t_start;
		Cell* goal = t_goal;

		AstarInit(start, goal,t_grid);

		start->setColor(sf::Color::Blue);
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
						if (child == goal)
						{
							child->setColor(sf::Color::Magenta);
							AstarDone = true;
							m_Astartimer = m_clock.getElapsedTime();
						}
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



		Cell* pathNode = t_goal;

		while (pathNode->GetPrev() != nullptr)
		{
			pathNode = pathNode->GetPrev();
			pathNode->setColor(sf::Color::Black);
			
		}


	}
	t_goal->setColor(sf::Color::Magenta);

	

}

Astar::Astar()
{
}

Astar::~Astar()
{
}

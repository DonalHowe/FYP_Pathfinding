#include "Dijkstras.h"

void Dijkstras::computeShortestPath(Cell* t_start, Cell* t_Goal, Grid* t_grid)
{
	sf::Clock m_clock;
	DjkstrasTimer.asSeconds();
	DjkstrasTimer = m_clock.restart();
	Cell* s = t_start;
	Cell* g = t_Goal;
	Cell* child;
	std::priority_queue<Cell*, std::vector<Cell*>, GCostComparer > pq;
	std::stack<Cell*> m_stack;

	for (int i = 0; i < t_grid->MAX_CELLS; i++)
	{
		Cell* v = t_grid->atIndex(i);
		v->setPrev(nullptr);
		v->setMarked(false);
		v->setGcost(t_grid->M_INFINITY);
		v->setWieght(10);
		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}

	}

	// initilise the distance of s to 0
	s->setGcost(0);
	s->setStartColour();
	pq.push(s);
	pq.top()->setMarked(true);

	while (pq.size() != 0 && pq.top() != g)
	{

		auto iter = pq.top()->getNeighbours().begin();
		auto endIter = pq.top()->getNeighbours().end();

		for (; iter != endIter; iter++)
		{

			Cell* child = (*iter);
			if (child != pq.top()->GetPrev())
			{

				int distanceToChild = ((*iter)->getWeight() + pq.top()->getGcost());

				if (distanceToChild < child->getGcost() && child->getTraversable() == true)
				{
					child->setGcost(distanceToChild);
					child->setPrev(pq.top());
					if (child == t_Goal) {
						std::cout << "djikstras" << std::endl;
						DjkstrasTimer = m_clock.getElapsedTime();
						djkstrasPathFound = true;
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
	Cell* pathNode = t_Goal;
	while (pathNode->GetPrev() != nullptr)
	{
		m_stack.push(pathNode);
		if (pathNode != t_start)
		{
			pathNode->setColor(sf::Color::Black);
		}


		pathNode = pathNode->GetPrev();
	}

	t_Goal->setColor(sf::Color::Magenta);

	
}

Dijkstras::Dijkstras()
{
}

Dijkstras::~Dijkstras()
{
}

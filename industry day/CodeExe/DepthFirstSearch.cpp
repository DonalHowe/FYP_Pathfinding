#include "DepthFirstSearch.h"
/// author : donal Howe
/// 

// returns the timer
sf::Time& DepthFirstSearch::getTimer()
{
	return m_depthfirstSearchTimer;
}

// returns the temination condition
bool& DepthFirstSearch::getDepthFound()
{
	return m_depthGoalFound;
}

void DepthFirstSearch::setTimerBool(bool t_b)
{
	initComplete = t_b;
}

// computes the path using the depth first search pathfinding algorithm 
void DepthFirstSearch::computeShortestPath(Cell* t_curr, Cell* t_goal, Grid* t_grid)
{
	if (initComplete == false)
	{
		m_depthfirstSearchTimer.asSeconds();
		m_depthfirstSearchTimer = m_clock.restart();
		initComplete = true;
	}
	
	if (nullptr != t_curr && m_depthGoalFound == false) {
		// process the current node and mark it
		t_curr->setMarked(true);

		for (auto itr = t_curr->getNeighbours().begin(); itr != t_curr->getNeighbours().end(); itr++)
		{
			if ((*itr)->getTraversable() == false)
			{
				continue;
			}
			// process the linked node if it isn't already marked.
			if ((*itr) == t_goal)
			{
				(*itr)->setPrev(t_curr);
				m_depthfirstSearchTimer = m_clock.getElapsedTime();
				m_depthGoalFound = true;
				break;
			}
			if ((*itr)->getMarked() == false)
			{
				(*itr)->setPrev(t_curr);
				computeShortestPath((*itr), t_goal,t_grid);

			}
		}
	}


	Cell* pathNode = t_goal;
	while (pathNode->GetPrev() != nullptr)
	{
		
		pathNode->setColor(sf::Color::Yellow);
		pathNode = pathNode->GetPrev();
	}

	t_goal->setColor(sf::Color::Magenta);
}

void DepthFirstSearch::initDepth(Cell* t_curr, Cell* t_goal, Grid* t_grid)
{
	for (int i = 0; i < t_grid->getMAXCELLS(); i++)
	{
		Cell* v = t_grid->atIndex(i);
		v->setPrev(nullptr);
		v->setHcost(t_grid->heuristic(v, t_goal));
		v->setMarked(false);
		v->setGcost(t_grid->M_INFINITY);
		v->setWieght(10);
		v->setFcost(v->getGcost() + v->getHcost());

		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}

	}
}

// default constructor
DepthFirstSearch::DepthFirstSearch()
{
}

// default destructor
DepthFirstSearch::~DepthFirstSearch()
{
}

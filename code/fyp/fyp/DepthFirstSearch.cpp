#include "DepthFirstSearch.h"
/// author : donal Howe
/// 


sf::Time& DepthFirstSearch::getTimer()
{
	return depthfirstSearchTimer;
}

bool& DepthFirstSearch::getDepthFound()
{
	return depthGoalFound;
}

void DepthFirstSearch::computeShortestPath(Cell* t_curr, Cell* t_goal, Grid* t_grid)
{
	sf::Clock m_clock;
	depthfirstSearchTimer.asSeconds();
	depthfirstSearchTimer = m_clock.restart();
	
	if (nullptr != t_curr && depthGoalFound == false) {
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
				depthfirstSearchTimer = m_clock.getElapsedTime();
				depthGoalFound = true;
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

DepthFirstSearch::DepthFirstSearch()
{
}

DepthFirstSearch::~DepthFirstSearch()
{
}

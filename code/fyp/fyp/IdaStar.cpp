#include "IdaStar.h"

sf::Time& IdaStar::getTimer()
{
    return m_idaStartimer;
}

bool& IdaStar::getIfDone()
{
    return m_IDAstarDone;
}

void IdaStar::IdAstarInit(Cell* t_start, Cell* t_goal, Grid* t_grid)
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

int IdaStar::computeShortestPath(Cell* t_start, Cell* t_goal,double t_threshold, Grid* t_grid)
{
    // Check if the current node exceeds the threshold
    if (t_start->getFcost() > t_threshold)
    {
        m_nextThreshold = std::min(m_nextThreshold, t_start->getFcost());
        return INT_MAX;
    }

    // Check if the goal node is reached
    if (t_start == t_goal)
    {
        return t_start->getGcost();
    }

    int minCost = INT_MAX;

    // Expand the current node and check its neighbors
    for (Cell* neighbor : t_start->getNeighbours())
    {
        if (neighbor != t_start->GetPrev() && neighbor->getTraversable())
        {
            // Calculate the new g-cost
            int gCost = t_start->getGcost() + neighbor->getWeight();

            // Update the neighbor's g-cost and f-cost if it's lower than the current values
            if (gCost < neighbor->getGcost())
            {
                neighbor->setGcost(gCost);
                neighbor->setFcost(gCost + t_grid->heuristic(neighbor, t_goal));
                neighbor->setPrev(t_start);

                // Recursively search the neighbor node
                int result = computeShortestPath(neighbor, t_goal, t_threshold, t_grid);

                // If a solution is found, return it
                if (result != INT_MAX)
                {
                    return result;
                }

                // If no solution is found, update the minimum cost
                minCost = std::min(minCost, result);
            }
        }
    }

    // If no solution is found, return the minimum cost
    return minCost;

}

std::stack<Cell*> IdaStar::runIdaStar(Cell* t_start, Cell* t_goal, Grid* t_grid)
{
	// Initialize the timer and the threshold
    if (initComplete == false)
    {
        sf::Clock clock;
        m_idaStartimer = clock.restart();
        IdAstarInit(t_start, t_goal, t_grid);
        initComplete = true;

    }
	
	double threshold = t_grid->heuristic(t_start, t_goal);

	while (true)
	{
		// Run the depth-limited search with the current threshold
		int result = computeShortestPath(t_start, t_goal, threshold, t_grid);

		// If a solution is found, return it
		if (result != INT_MAX)
		{
			// Construct the path and return it
			Cell* pathNode = t_goal;
			while (pathNode->GetPrev() != nullptr)
			{
				m_stack.push(pathNode);
				pathNode = pathNode->GetPrev();
				pathNode->setColor(sf::Color::Black);
			}
			t_goal->setColor(sf::Color::Magenta);
			//return result;
		}

		// If no solution is found, increase the threshold to the minimum f-value of nodes
		// that exceeded the current threshold
		if (result == INT_MAX)
		{
			threshold = m_nextThreshold;
			m_nextThreshold = INT_MAX;
		}
	}



    return m_stack;
}

IdaStar::IdaStar()
{
}

IdaStar::~IdaStar()
{
}

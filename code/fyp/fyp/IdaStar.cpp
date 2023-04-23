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
        return t_grid->M_INFINITY;
    }

    // Check if the goal node is reached
    if (t_start == t_goal)
    {
        return t_start->getGcost();
    }

    int minCost = t_grid->M_INFINITY;

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
                if (result != t_grid->M_INFINITY)
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
    std::priority_queue<Cell*, std::vector<Cell*>, fcostValueThingy >m_pq;
    m_pq = std::priority_queue<Cell*, std::vector<Cell*>, fcostValueThingy >();
  
	double threshold = t_grid->heuristic(t_start, t_goal);
    m_pq.push(t_start);



	while (m_IDAstarDone==false)
	{
		// Run the depth-limited search with the current threshold
		int result = computeShortestPath(m_pq.top(), t_goal, threshold, t_grid);

		// If a solution is found, return it
		if (result != t_grid->M_INFINITY)
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
            m_IDAstarDone = true;
			//return result;
		}

		// If no solution is found, increase the threshold to the minimum f-value of nodes
		// that exceeded the current threshold
		if (result == t_grid->M_INFINITY)
		{
            double tempMin = t_grid->M_INFINITY;
          
            for (auto neighbours : m_pq.top()->getNeighbours())
            {
                // gets the lowest value from all of the neighbours
                if (neighbours->getGcost() + neighbours->getHcost() < tempMin)
                {
                    tempMin = (neighbours->getGcost() + neighbours->getHcost());
                }
            }

			threshold = tempMin;
			m_nextThreshold = t_grid->M_INFINITY;
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

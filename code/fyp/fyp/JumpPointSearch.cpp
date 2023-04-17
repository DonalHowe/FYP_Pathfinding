#include "JumpPointSearch.h"
/// author : donal Howe
/// 


// returns the timer for the algorithms completion
sf::Time& JumpPointSearch::getTimer()
{
    return m_JumpPointtimer;
}

// returns the termination condition
bool& JumpPointSearch::getIfDone()
{
    return m_JumpPointSearchDone;
}

// initilises the grid for jump point search to function
void JumpPointSearch::JpsInit(Cell* t_start, Cell* t_goal, Grid* t_grid)
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

// computes the shortest path using the jump point search pathfinding algorithm
void JumpPointSearch::computeShortestPath(Cell* t_start, Cell* t_goal, Grid* t_grid)
{
	// initilises the grid
	JpsInit(t_start,t_goal,t_grid);
	// creates a priority queue that sorts based on the fcost of a cell
	std::priority_queue<Cell*, std::vector<Cell*>, fcostComparer >m_pq;
	m_pq = std::priority_queue<Cell*, std::vector<Cell*>, fcostComparer >();

	t_start->setGcost(0);
	t_start->setMarked(true);
	m_pq.push(t_start);

	while (!m_pq.empty())
	{
		Cell* currentCell = m_pq.top();
		m_pq.pop();
		// if the current cell is the goal node break from the loop
		if (currentCell == t_goal)
		{
			// the algorithm finsihed
			m_JumpPointSearchDone = true;
			break;
		}
		else
		{
			for (auto neighbours : currentCell->getNeighbours())
			{
				determineJumpPoints(currentCell,neighbours, t_goal, t_grid, m_pq);
			}
		}

	

	}



}

// this function determines whether a cell is a forced neighbour and a jump point
// for the algorithm
void JumpPointSearch::determineJumpPoints(Cell* t_current, Cell* t_neighbor, Cell* t_goal, Grid *t_grid, std::priority_queue<Cell*, std::vector<Cell*>, fcostComparer>& t_pq)
{
	// Get the direction from the current cell to the neighbor
	int dx = t_neighbor->m_Xpos - t_current->m_Xpos;
	int dy = t_neighbor->m_Ypos - t_current->m_Ypos;

	// Check if the neighbor is a jump point
	if (t_neighbor->getTraversable()==true && t_neighbor->getTraversable())
	{
		if (t_neighbor == t_goal)
		{
			t_goal->setPrev(t_current);
			t_pq.push(t_goal);
			return;
		}

		// Check if there are any forced neighbors along this direction
		std::vector<Cell*> forcedNeighbors = getForcedNeighbors(t_neighbor, dx, dy, t_grid);
		for (auto forcedNeighbor : forcedNeighbors)
		{
			determineJumpPoints(t_neighbor, forcedNeighbor, t_goal, t_grid, t_pq);
		}
	}
}

std::vector<Cell*> JumpPointSearch::getForcedNeighbors(Cell* t_cell, int t_dx, int t_dy, Grid* t_grid)
{
    std::vector<Cell*> forcedNeighbors;

    //// Check for diagonal movement
    //if (t_dx != 0 && t_dy != 0)
    //{
    //    // Check for horizontal and vertical neighbors
    //    Cell* neighbor1 = t_grid->m_theTableVector.at(t_grid[t_cell->m_Xpos][t_cell->getY() + t_dy];
    //    Cell* neighbor2 = t_grid[t_cell->getX() + t_dx][t_cell->getY()];

    //    if (neighbor1->getTraversable()==true && !neighbor2->getTraversable() == true)
    //    {
    //        forcedNeighbors.push_back(neighbor2);
    //    }
    //    else if (neighbor2->getTraversable()==true && !neighbor1->getTraversable() == true)
    //    {
    //        forcedNeighbors.push_back(neighbor1);
    //    }
    //    else if (neighbor1->getTraversable() == true && neighbor2->getTraversable() == true)
    //    {
    //        // Check for diagonal neighbors
    //        Cell* diagonalNeighbor1 = t_grid[t_cell->getX() - t_dx][t_cell->getY() + t_dy];
    //        Cell* diagonalNeighbor2 = t_grid[t_cell->getX() + t_dx][t_cell->getY() - t_dy];

    //        if (diagonalNeighbor1->getTraversable()==true)
    //        {
    //            forcedNeighbors.push_back(diagonalNeighbor1);
    //        }
    //        if (diagonalNeighbor2->getTraversable()==true)
    //        {
    //            forcedNeighbors.push_back(diagonalNeighbor2);
    //        }
    //    }
    //}
    //else
    //{
    //    // Check for horizontal movement
    //    if (t_dx != 0)
    //    {
    //        Cell* neighbor1 = t_grid[t_cell->getX()][t_cell->getY() + 1];
    //        Cell* neighbor2 = t_grid[t_cell->getX()][t_cell->getY() - 1];

    //        if (neighbor1->isBlocked() && !neighbor2->isBlocked())
    //        {
    //            forcedNeighbors.push_back(neighbor2);
    //        }
    //        else if (neighbor2->isBlocked() && !neighbor1->isBlocked())
    //        {
    //            forcedNeighbors.push_back(neighbor1);
    //        }
    //    }
    //    // Check for vertical movement
    //    else
    //    {
    //        Cell* neighbor1 = t_grid[t_cell->getX() + 1][t_cell->getY()];
    //        Cell* neighbor2 = t_grid[t_cell->getX() - 1][t_cell->getY()];

    //        if (neighbor1->isBlocked() && !neighbor2->isBlocked())
    //        {
    //            forcedNeighbors.push_back(neighbor2);
    //        }
    //        else if (neighbor2->isBlocked() && !neighbor1->isBlocked())
    //        {
    //            forcedNeighbors.push_back(neighbor1);
    //        }
    //    }
    //}

    return forcedNeighbors;
}

// default constructor
JumpPointSearch::JumpPointSearch()
{
}

// default destructor
JumpPointSearch::~JumpPointSearch()
{
}

#include "DstarLite.h"
/// author : donal Howe
/// 



// calculates the key of each cell and storing that into an std::pair
// first of the pair is the min of gcost and rhs cost + heuristic val +
// key modifier
// secdond of the pairing is the min of g cost and rhs cost
std::pair<double, double> DstarLite::calculateDstarKey(Cell* t_currentSearch, Cell* Start,Grid * t_grid)
{
	double heuristicVal = t_grid->heuristic(t_currentSearch, Start) + m_K_M;
	double minVal = std::min(t_currentSearch->getGcost(), t_currentSearch->getRhSCost());
	std::pair<double, double> temp1 = std::make_pair(heuristicVal + minVal, std::min(t_currentSearch->getGcost(), t_currentSearch->getRhSCost()));
	return temp1;
}

// initilises all of the necessary variables for dstar lite
void DstarLite::initDstar(Cell* t_start, Cell* t_currentSearch, Grid* t_grid)
{
	U_pq = std::priority_queue<Cell*, std::vector<Cell*>, DstarKeyComparer>();
	// setting key modifier to 0
	m_K_M = 0;

	// set all of cells in grid to appropriate values
	for (int i = 0; i < t_grid->getMAXCELLS(); i++)
	{
		Cell* v = t_grid->atIndex(i);
		v->setPrev(nullptr);
		// set all costs to infinity
		v->setGcost(t_grid->M_INFINITY);
		v->setRHSCost(t_grid->M_INFINITY);
		// sets the weight
		v->setWieght(10);
		v->setMarked(false);
		if (v->getTraversable() == true)
		{
			if (v != t_currentSearch)
			{
				v->setColor(sf::Color::White);
			}

		}
	}

	// set the rhs of current cell to 0 and calulate the key
	t_currentSearch->setRHSCost(0);
	t_currentSearch->setKey(calculateDstarKey(t_currentSearch, t_start,t_grid).first, calculateDstarKey(t_currentSearch, t_start,t_grid).second);
	// pusn the current cell into the priority queue
	U_pq.push(t_currentSearch);
}


// computes the shortest path
void DstarLite::ComputeShortestPath(Cell* t_start, Cell* t_currentSearch, Grid* t_grid)
{
	// while the key of current cell is less than
	// claulation of that key i.e there is inconcistancy
	// or rhs != gcost i.e inconsistancy
	while (U_pq.top()->getKey() < calculateDstarKey(t_start, t_start,t_grid) || t_start->getGcost() != t_start->getRhSCost())
	{
		// create cell to = current pq top
		Cell* currentCell = U_pq.top();
		if (currentCell != nullptr)
		{
			// old key and new key for comparing reasons
			std::pair<double, double> key_Old = U_pq.top()->getKey();
			std::pair<double, double> key_New = calculateDstarKey(currentCell, t_start,t_grid);
			// set cell to marked to avoid backtracking on itself mid search
			currentCell->setMarked(true);
			// pop from queue once it has been investigated
			U_pq.pop();
			// if its a wall skip that cell
			if (currentCell->getTraversable() == false)
			{
				continue;
			}
			// for a change in the values
			if (key_Old < key_New)
			{
				currentCell->setKey(key_New.first, key_New.second);
				U_pq.push(currentCell);
			}
			// if it is overconsistant
			else if (currentCell->getGcost() > currentCell->getRhSCost())
			{

				// relaxing the node

				currentCell->setGcost(currentCell->getRhSCost());

				// update all of the neighbours
				for (auto pre : currentCell->getNeighbours())
				{
					// update their vertexes


					updateVertex(pre, t_currentSearch,t_grid);
				}

			}
			else {
				// if the nodeis underconsistant

				currentCell->setGcost(t_grid->M_INFINITY);

				// update all of the neighbours 
				for (auto neighbours : currentCell->getNeighbours())
				{

					updateVertex(neighbours, t_currentSearch,t_grid);

				}
				// update the current ccell
				updateVertex(currentCell, t_currentSearch,t_grid);
			}
		}
	}
}


// returns the timer
sf::Time& DstarLite::getTimer()
{
	return m_dStarLiteTimer;
}

// returns the temination condition
bool& DstarLite::getDStarPathFound()
{
	return m_dstarGoalFound;
}

// the main dstar lite function this controls the progression of the start position
void DstarLite::DstarLiteMain(Cell* t_start, Cell* t_currentSearch, Grid* t_grid) {

	// timer for testing purposes
	sf::Clock m_clock;
	m_dStarLiteTimer.asSeconds();
	m_dStarLiteTimer = m_clock.restart();

	// to keep track of the original start pos
	Cell* s_Last = t_start;
	Cell* goal = t_currentSearch;
	
	// if its not equal to the start node
	if (t_start != goal)
	{
		initDstar(t_start, t_currentSearch, t_grid);
		ComputeShortestPath(t_start, t_currentSearch, t_grid);
	}
	
	// t_start . gcost is inifinte still there is no known path 
	float tempMin = t_grid->M_INFINITY;
	Cell* nextNode = nullptr;
	// if not equal to goal node 
	while (t_start != goal)
	{
		// gets the minimal values and moves next node to that neigbour until the best one is found
		for (auto neighbours : t_start->getNeighbours())
		{
			if (neighbours->getWeight() + neighbours->getGcost() < tempMin)
			{
				tempMin = (neighbours->getGcost() + neighbours->getWeight());
				nextNode = neighbours;
			}
		}
		// changes that node to green and progress the start node
		t_start->getRect().setFillColor(sf::Color::Green);
		t_start = nextNode;
	}

	// close the timer if search is finsihed
	if (t_start == goal)
	{
		m_dStarLiteTimer = m_clock.getElapsedTime();
	}
	
	// checking for any edge cost changes of the surrounding neighbours

	for (auto neighbours : t_start->getNeighbours())
	{
		if (neighbours->getTraversable() == false)
		{
			// increase the key modifier to account for change in start pos
			m_K_M = m_K_M + t_grid->heuristic(s_Last, t_start);
			s_Last = t_start;
			// update the surrounding nodes
			updateVertex(neighbours, t_currentSearch, t_grid);
			// recompute the path to the goal
			ComputeShortestPath(t_start, t_currentSearch, t_grid);
		}
	}

}

// investigate the node and update it if necessary
void DstarLite::updateVertex(Cell* currentCell, Cell* t_start, Grid* t_grid) {

	if (currentCell != nullptr || t_start != nullptr)
	{
		// if the current node is not the start node
		if (currentCell != t_start)
		{
			// sets tempMin to infinity so it can keep on getting relaxed down
			double tempMin = t_grid->M_INFINITY;
			// set the minimum rhs value of the surrounding nodes
			// set thier rhs value for this node 
			for (auto neighbours : currentCell->getNeighbours())
			{
				// gets the lowest value from all of the neighbours
				if (neighbours->getGcost() + neighbours->getWeight() < tempMin)
				{
					tempMin = (neighbours->getGcost() + neighbours->getWeight());
				}
			}
			 
			// set the new rhs value
			currentCell->setRHSCost(tempMin);
		}

		// if the node has already in the queue remove it
		priority_queue<Cell*> new_pq;
		while (!U_pq.empty()) {
			Cell* current = U_pq.top();
			U_pq.pop();
			if (current != currentCell) {
				new_pq.push(current);
			}

		}
		// push everything back into the priority queue
		while (!new_pq.empty())
		{
			U_pq.push(new_pq.top());
			new_pq.pop();
		}

		if (currentCell != nullptr)
		{
			// if the node has not been searched
			if (currentCell->getMarked() == false)
			{
				// uopdate the nodes key and put it back into the queue
				if (currentCell->getGcost() != currentCell->getRhSCost())
				{
					currentCell->setKey(calculateDstarKey(currentCell, t_start,t_grid).first, calculateDstarKey(currentCell, t_start,t_grid).second);
					U_pq.push(currentCell);
				}
			}
		}
	}

}
#include "LpaStar.h"
/// author : donal Howe
/// 


// calulates the key if the cell
std::pair<double, double> LpaStar::calculateKey(Cell* s, Cell* t_goal,Grid *t_grid)
{
	
	double MinOfG_rhs = std::min(s->getGcost(), s->getRhSCost());
	double heuristicValue = t_grid->heuristic(s, t_goal);

	return std::make_pair(MinOfG_rhs + heuristicValue, MinOfG_rhs);
}

// returns the temination condition
void LpaStar::setTerminationCondition(bool t_bool)
{
	m_LPApathFound = t_bool;
}

// returns the timer
sf::Time& LpaStar::getTimer()
{
	return m_LpaStartimer;
}

// returns the termination condition
bool& LpaStar::getLpaStarPathFound()
{
	return m_LPApathFound;
}

// initilises all of the necessary variables for life long planning astar
void LpaStar::initLpaStar(Cell* t_start, Cell* t_goal, Grid* t_grid)
{
	m_LpaStartimer.asSeconds();
	m_LpaStartimer = m_clock.restart();

	if (m_LPApathFound == false)
	{
		for (int i = 0; i < t_grid->getMAXCELLS(); i++)
		{
			Cell* v = t_grid->atIndex(i);

			v->setPrev(nullptr);
			v->setHcost(t_grid->heuristic(v, t_goal));
			v->setMarked(false);
			v->setGcost(t_grid->M_INFINITY);
			v->setWieght(10);
			v->setKey(t_grid->M_INFINITY, t_grid->M_INFINITY);
			if (v->getTraversable() == true)
			{
				v->setColor(sf::Color::White);
			}

		}
	}

	// init start g cost and rhs cost to 0
	t_start->setGcost(0);
	t_start->setRHSCost(0);
	// input start key to suit that 

	t_start->setKey(std::min(t_start->getGcost(), t_start->getRhSCost()) + t_grid->heuristic(t_start, t_goal) + m_K_M * m_EPS, 0);
}

// computes the path
void LpaStar::LPAStar(Cell* t_start, Cell* t_goal,Grid * t_grid)
{
	
	initLpaStar(t_start, t_goal, t_grid);

	std::priority_queue<Cell*, std::vector<Cell*>, KeyComparer> u;

	u.push(t_start);

	while (!u.empty() && m_LPApathFound == false)
	{

		// Get the top cell from the priority queue
		Cell* curr = u.top();
		curr->m_isInOpenList = false;
		u.pop();

		// If the current cell is the goal break out 
		if (curr == t_goal)
		{
			std::cout << "found cell" << std::endl;
			m_LpaStartimer = m_clock.getElapsedTime();
			m_LPApathFound = true;
			break;
		}

		// if the current cell is not a wall 
		if (curr->getTraversable() == true)
		{

			// if curr gcost and rhs cost is greater than its rhs cost 
			if (curr->getKey().first > curr->getKey().second)
			{
				// setting the colour of searched cell 

				// setting the rhs cost = to the g newly caluclated g cost
				curr->setRHSCost(curr->getGcost());
				// searching the neighbours of te current cell 
				for (auto succ : curr->getNeighbours())
				{
					// this is the new cost of which is the g cost and the distance from the successor to reorder the pq 
					double new_cost = curr->getGcost() + t_grid->heuristic(curr, succ);
					if (new_cost < succ->getGcost()) {
						// checking if it is not a wall 
						if (succ->getTraversable() == true)
						{
							// setting its previous for rebuilding the path
							succ->setPrev(curr);
							succ->setGcost(new_cost);
							// setting the rhs of a suitable neighbour to the min of current rhs cost and the distance of the successor and the current cell
							succ->setRHSCost(std::min(succ->getRhSCost(), curr->getGcost() + t_grid->heuristic(curr, succ)));
							// checking if it is in the open list
							if (succ->m_isInOpenList) {
								// updating the node it the function where i recalculate the rhs and g coset
								updateNode(succ, t_goal,t_grid);
							}
							else {
								succ->m_isInOpenList = true;
								u.push(succ);
							}
						}
					}
				}
			}
			else
			{
				curr->setGcost(t_grid->M_INFINITY);
				for (auto succ : curr->getNeighbours())
				{
					succ->m_isInOpenList = true;
					updateNode(succ, t_goal, t_grid);
					u.push(succ);
				}
				curr->m_isInOpenList = true;
				updateNode(curr, t_goal, t_grid);
				u.push(curr);
			}
		}
		else
		{
			curr->setKey(t_grid->M_INFINITY, t_grid->M_INFINITY);
		}


	}
	

	if (m_LPApathFound == true)
	{
		// Reconstruct the path from start to goal
		Cell* pathNode = t_goal;

		while (pathNode != nullptr)
		{
			
			pathNode->setColor(sf::Color::Black);
			pathNode = pathNode->GetPrev();

		}
		t_goal->setColor(sf::Color::Green);
		t_start->setColor(sf::Color::Blue);
		

	}


}

// updates each node accordingly
void LpaStar::updateNode(Cell* node, Cell* t_goal, Grid* t_grid)
{
	if (node->getTraversable() == true)
	{

		if (node->m_isInOpenList) {
			// Update the key if the node is in the open list k_m is the maximun cost per move allowed  and eps being the is an estimate on the cost to go to the goal 

			node->setKey(std::min(node->getGcost(), node->getRhSCost()) + t_grid->heuristic(node, t_goal) + m_K_M * m_EPS,
				std::min(node->getGcost(), node->getRhSCost()));
		}
		else {
			// Add the node to the open list with a key of (infinity, infinity)
			node->setKey(std::min(node->getGcost(), node->getRhSCost()) + t_grid->heuristic(node, t_goal) + m_K_M * t_grid->M_INFINITY,
				std::min(node->getGcost(), node->getRhSCost()));
			node->m_isInOpenList = true;
			//u.push(node);
		}

		// Update the rhs value of the node
		if (node == t_goal) {
			node->setRHSCost(0);
		}
		else {
			double min_rhs = t_grid->M_INFINITY;

			for (auto successor : node->getNeighbours()) {


				if (successor->getTraversable() == true)
				{
					double cost = successor->getGcost() + t_grid->heuristic(node, successor);
					if (cost < min_rhs) {
						min_rhs = cost;
						//node->setPrev(succ); // Set the "previous" attribute to the best successor
					}
				}

			}
			node->setRHSCost(min_rhs);
		}
	}


}

// default constructor
LpaStar::LpaStar()
{
}

//default destructor
LpaStar::~LpaStar()
{
}

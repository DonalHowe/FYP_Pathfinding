#include "Grid.h"



class CostDistanceValueComparer
{

public:

	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getGcost() + t_n1->getHcost()) > (t_n2->getGcost() + t_n2->getHcost());
	}
};




class GCostComparer
{

public:

	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getGcost()) > (t_n2->getGcost());
	}
};

class KeyComparer {
public:
	bool operator()(const Cell* a, const Cell* b) const {
		if (a->m_key < b->m_key)
			return true;
	
	}
};


double heuristic(Cell* c1, Cell* c2)
{
	// Calculate the Euclidean distance between the two cells
	int dx = c1->Xpos - c2->Xpos;
	int dy = c1->Ypos - c2->Ypos;
	double distance = std::sqrt(dx * dx + dy * dy);


	return distance;
}

std::pair<double, double> calculateKey(Cell* s, Cell* t_goal)
{
	float km=0;
	double g_rhs = std::min(s->getGcost(), s->getRhSCost());
	double h = heuristic(s, t_goal);

	return std::make_pair(g_rhs + h + km, g_rhs);
}

std::pair<double, double> Grid::calculateDstarKey(Cell* t_cell, Cell* t_start)
{
	double g = t_cell->getGcost();
	double rhs = t_cell->getRhSCost();
	double h = heuristic(t_cell, t_start);
	double k1 = std::min(g, rhs) + h + k_m * eps;
	double k2 = std::min(g, rhs);
	return std::make_pair(k1, k2);
}


void Grid::initDstar(Cell* t_start,Cell*t_goal)
{
	U_pq = std::priority_queue<Cell*, std::vector<Cell*>, DstarKeyComparer>();

	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		v->setPrev(nullptr);
		v->setHcost(heuristic(v, t_start));
		v->setMarked(false);
		v->setGcost(m_infinity);
		v->setWieght(10);
		v->setKey(m_infinity, m_infinity);

		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}

	
	}

	t_goal->setRHSCost(0);
	t_goal->setGcost(0);
	t_goal->setKey(std::min(t_goal->getRhSCost(), heuristic(t_start, t_goal)), 0);
	U_pq.push(t_goal);
	
}



std::stack<Cell*> Grid::ComputeShortestPath(Cell * t_start,Cell * t_goal)
{

	initDstar(t_start, t_goal);
	while (U_pq.top()->getKey() < calculateDstarKey(t_start, t_goal) || t_start->getRhSCost() > t_start->getGcost())
	{
		Cell* currentCell = U_pq.top();
		auto key_Old = currentCell->getKey();
		auto key_New = calculateDstarKey(currentCell, t_start);
		std::cout << currentCell->getID() << std::endl;
		if (currentCell == t_start)
		{
			std::cout << "big chungus" << std::endl;
		}
		if (key_Old < key_New)
		{
			currentCell->setKey(key_New.first, key_New.second);
		}
		else if (currentCell->getGcost() > currentCell->getRhSCost())
		{
			currentCell->setGcost(currentCell->getRhSCost());
			U_pq.pop();
			for (auto predecessor : currentCell->getPredecessors())
			{
				if (predecessor != t_start)
				{
					predecessor->setRHSCost(std::min(currentCell->getRhSCost(), heuristic(predecessor, currentCell) + currentCell->getGcost()));
					updateVertex(predecessor, t_start);
				}
			}
		}
		else
		{
			double g_old = currentCell->getGcost();
			currentCell->setGcost(m_infinity);
			for (auto predecessor : currentCell->getPredecessors())
			{
				if (predecessor->getRhSCost() == g_old + heuristic(predecessor, currentCell))
				{
					if (predecessor != t_start)
					{
						predecessor->setRHSCost(m_infinity);
						updateVertex(predecessor, t_start);
					}
				}
			}
			currentCell->setRHSCost(m_infinity);
			updateVertex(currentCell, t_start);
		}
		currentCell = U_pq.top(); // update the currentCell
	}
	return std::stack<Cell*>();
}


void Grid::updateVertex(Cell* currentCell,Cell * t_start) {

	if (currentCell != t_start) {
		double min_rhs = m_infinity;
		for (auto succ : currentCell->getNeighbours()) {
			double temp_rhs = succ->getGcost() + heuristic(currentCell, succ);
			if (temp_rhs < min_rhs) {
				min_rhs = temp_rhs;
			}
		}
		currentCell->setRHSCost(min_rhs);
	}

	if (currentCell->getGcost() != currentCell->getRhSCost()) {
		auto pair = calculateDstarKey(currentCell, t_start);
		currentCell->setKey(pair.first, pair.second);

		U_pq.push(currentCell);
	}
	else if (currentCell->getGcost() > currentCell->getRhSCost()) {
		currentCell->setGcost(currentCell->getRhSCost());

		for (auto pre : currentCell->getPredecessors()) {
			updateVertex(pre, t_start);
		}
	}
	else {
		if (!U_pq.empty() && U_pq.top() == currentCell) {
			U_pq.pop();
		}
		else {
			std::vector<Cell*> temp;
			while (!U_pq.empty() && U_pq.top() != currentCell) {
				temp.push_back(U_pq.top());
				U_pq.pop();
			}
			for (auto it = temp.begin(); it != temp.end(); ++it) {
				U_pq.push(*it);
			}
		}
	}



	
}



std::stack<Cell*> Grid::JumpPointSearch(Cell* t_start, Cell* t_goal)
{

	/*	

		ii.Determine the jump point of the successor in the direction of its parent.If a jump point is found, set the successor's parent to the jump point.

		iii.Calculate the g - cost and f - cost of the successor and add it to the open list if it has not been visited before or if the new path to the node is cheaper.*/

	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		v->setPrev(nullptr);
		v->setMarked(false);
		v->setWieght(10);
		v->setFcost(heuristic(v, t_goal));
		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}
		
	}

	Cell* m_stat = t_start;
	m_stat->setGcost(0);
	m_stat->setFcost(heuristic(m_stat,t_goal));
	std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer > pq;
	std::vector<Cell*> jpsClosedList;
	pq.push(m_stat);

	

	


	return std::stack<Cell*>();
}


std::stack<Cell*> Grid::aStar(Cell* t_start, Cell* t_end)
{

	sf::Clock m_clock;
	m_Astartimer.asSeconds();
	m_Astartimer = m_clock.restart();


	if (t_start != nullptr && t_end != nullptr)
	{


		Cell* start = t_start;
		Cell* goal = t_end;
		std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer > pq;
		pq = std::priority_queue<Cell*, std::vector<Cell*>, CostDistanceValueComparer >();
		m_stack = std::stack<Cell*>();
		
		int Astarinfinity = std::numeric_limits<int>::max() / 10;

		for (int i = 0; i < MAX_CELLS; i++)
		{
			Cell* v = atIndex(i);
			v->setPrev(nullptr);
			v->setHcost(heuristic(v,t_end));
			v->setMarked(false);
			v->setGcost(Astarinfinity);
			v->setWieght(10);

			if (v->getTraversable() == true)
			{
				v->setColor(sf::Color::White);
			}
			
		}

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
			
					if (distanceToChild < child->getGcost()&& child->getTraversable() == true)
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


		
			Cell* pathNode = t_end;

			while (pathNode->GetPrev() != nullptr)
			{
				pathNode = pathNode->GetPrev();
				pathNode->setColor(sf::Color::Black);
				//std::this_thread::sleep_for(std::chrono::milliseconds(50));
				m_stack.push(pathNode);
			}
		

	}
	t_end->setColor(sf::Color::Magenta);



	return m_stack;

}

Cell* Grid::raiseCost(Cell* t_start, Cell* goal)
{
	Cell *start = t_start;
	std::list<Cell*> m_raiseStates;
	
	if (m_raiseStates.empty() == true)
	{

		for (auto it = start->getNeighbours().begin(); it != start->getNeighbours().end(); it++) {
			if ((*it)->getTraversable() == true)
			{
				m_raiseStates.push_back(*it);
			}
		}

		for (std::list<Cell*>::iterator Raiseit = m_raiseStates.begin(); Raiseit != m_raiseStates.end(); Raiseit++)
		{
			(*Raiseit)->raiseCost(100000);
			(*Raiseit)->setRisenBool(true);
			(*Raiseit)->getRect().setFillColor(sf::Color::Yellow);
		}
		
	}
	m_raiseStates.clear();

	return start;
}



Cell* Grid::atIndex(int t_id)
{
	int x = t_id % MAX_ROWS;
	int y = t_id / MAX_COLS;

	return 	&m_theTableVector.at(x).at(y);
}

Grid::Grid()
{
	
}

Grid::~Grid()
{
}

void  Grid::resetAlgorithm() {

	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		v->setPrev(nullptr);
		v->setMarked(false);
		v->setGcost(m_infinity);
		v->setWieght(10);

		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}

	}

}


std::stack<Cell*> Grid::Djkstras(Cell* t_start,Cell* t_goal) {


	sf::Clock m_clock;
	DjkstrasTimer.asSeconds();
	DjkstrasTimer = m_clock.restart();
	Cell* s = t_start;
	Cell* g = t_goal;
	Cell* child;
	std::priority_queue<Cell*, std::vector<Cell*>,GCostComparer > pq;
	std::stack<Cell*> m_stack;

	

	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell* v = atIndex(i);
		v->setPrev(nullptr);
	
		v->setMarked(false);
		v->setGcost(m_infinity);
		v->setWieght(10);

		if (v->getTraversable() == true)
		{
			v->setColor(sf::Color::White);
		}

	}



	// initilise the distance of s to 0
	s->setGcost (0);
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
			
				if (distanceToChild < child->getGcost()&&child->getTraversable()==true)
				{
					child->setGcost( distanceToChild);
					child->setPrev(pq.top());
					if (child == t_goal) {
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
	Cell* pathNode = t_goal;
	while (pathNode->GetPrev()!=nullptr)
	{
		m_stack.push(pathNode);
		if (pathNode != t_start)
		{
			pathNode->setColor(sf::Color::Black);
		}
		
		
		pathNode = pathNode->GetPrev();
	}

	t_goal->setColor(sf::Color::Magenta);

	return m_stack;
}

std::stack<Cell*> Grid::depthfirstSearch(Cell* t_curr,Cell* t_goal) {


	sf::Clock m_clock;
	depthfirstSearchTimer.asSeconds();
	if (depthGoalFound== true)
	{
		DjkstrasTimer = m_clock.restart();
	}
	

	if (nullptr != t_curr && depthGoalFound==false) {
		// process the current node and mark it
		std::cout << t_curr->getID() << std::endl;
		t_curr->setMarked(true);


		for (auto itr= t_curr->getNeighbours().begin();itr!=t_curr->getNeighbours().end();itr++)
		{
			// process the linked node if it isn't already marked.
			if ((*itr) == t_goal)
			{
				(*itr)->setPrev(t_curr);
				std::cout << "found goal" << std::endl; 
				DjkstrasTimer = m_clock.getElapsedTime();
				depthGoalFound = true;
				break;
			}
			if ((*itr)->getMarked() == false)
			{
				(*itr)->setPrev(t_curr);
				depthfirstSearch((*itr),t_goal);
				
			}
		}
	}


	Cell* pathNode = t_goal;
	while (pathNode->GetPrev() != nullptr)
	{
		m_stack.push(pathNode);
		pathNode->setColor(sf::Color::Black);
		pathNode = pathNode->GetPrev();
	}

	t_goal->setColor(sf::Color::Magenta);
	return std::stack<Cell*>();
}

void Grid::setNeighbours(Cell* t_cell)
{
	int row = t_cell->Xpos;
	int col = t_cell->Ypos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {

			int id = n_row + (n_col * MAX_ROWS);// this is for the total number of rows you want in your grid i.e 50x50 or a 10x10
			t_cell->setNeighbours(&m_theTableVector.at(n_row).at(n_col));
			
		}
	}
		
}

void Grid::setPredecessors(Cell* t_cell)
{
	int row = t_cell->Xpos;
	int col = t_cell->Ypos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {

			int id = n_row + (n_col * MAX_ROWS); // Compute cell ID
			Cell* neighbor = &m_theTableVector.at(n_row).at(n_col);

			// Check if neighbor is traversable
			if (neighbor->getTraversable()==true) {

				// Calculate the new cost to reach the neighbor
				double new_cost = t_cell->getGcost() + distance(t_cell, neighbor);

				// Update the predecessor if the cost has improved
				if (new_cost < neighbor->getGcost()) {
					neighbor->setGcost(new_cost);
					neighbor->setPredecessorss(t_cell);

					// If neighbor is not in the open list, add it
					if (!neighbor->isInOpenList==false) {
						
						//m_openList.push(neighbor);
						neighbor->isInOpenList==true;
					}
				}
			}
		}
	}
}

void Grid::setupGrid(int t_c)
{
	m_theTableVector.clear();
	
	sf::Vector2f pos{ 0.0f,0.f };
	for (int i = 0; i < MAX_ROWS; i++)
	{
		std::vector<Cell> tempVec;
		m_theTableVector.push_back(tempVec);
	}

	for (int i = 0; i < MAX_CELLS; i++)
	{
		int x = i % MAX_ROWS;
		int y = i / MAX_COLS;
		Cell tempNode;
		tempNode.setTraversable(true);
		tempNode.Xpos = x;
		tempNode.Ypos = y;
		tempNode.initRect(t_c);
		tempNode.setPos(pos);
		pos.x += tempNode.getRect().getSize().x;
		if (pos.x > ScreenSize::M_WIDTH)
		{
			pos.y += tempNode.getRect().getSize().y;
			pos.x = 0;
		}
		tempNode.setID(x + (y * MAX_ROWS));
		
		m_theTableVector.at(x).push_back(tempNode);
	}
	
	
	
	for (int i = 0; i < MAX_CELLS; i++)
	{
		setNeighbours(atIndex(i));
		
	}

	for (int i = 0; i < MAX_CELLS; i++)
	{
		
		setPredecessors(atIndex(i));
	}

	for (int i= 0; i < MAX_ROWS; i++)
	{
		Cell* v = atIndex(i);
		v->setTraversable(false);
		v->setColor(sf::Color::White);
	}

	
	for (int j = MAX_CELLS-1; j >= MAX_CELLS - MAX_ROWS; j--)
	{
		Cell* v = atIndex(j);
		v->setTraversable(false);
		v->setColor(sf::Color::White);
	}

}

void Grid::render(sf::RenderWindow& t_window, sf::RenderWindow& t_windowAstar)
{
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			if (m_theTableVector.size() != 0)
			{
				t_window.draw(m_theTableVector.at(j).at(i).getRect());
				//t_windowAstar.draw(m_theTableVector.at(j).at(i).getRect());
			
			}
		}
	}
	
}

/// <summary>
/// //
/// </summary>
/// <param name="t_start"></param>
/// <param name="t_goal"></param>
/// <returns></returns>

std::stack<Cell*> Grid::LPAStar(Cell* t_start, Cell* t_goal)
{
	// init the grid to suit cinditions 
	sf::Clock m_clock;
	m_LpaStartimer.asSeconds();
	m_LpaStartimer = m_clock.restart();
	

	if (LPApathFound == false)
	{
		for (int i = 0; i < MAX_CELLS; i++)
		{
			Cell* v = atIndex(i);

			v->setPrev(nullptr);
			v->setHcost(heuristic(v, t_goal));
			v->setMarked(false);
			v->setGcost(m_infinity);
			v->setWieght(10);
			v->setKey(m_infinity, m_infinity);
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
	t_start->setKey(std::min(t_start->getGcost(), t_start->getRhSCost()) + heuristic(t_start, t_goal) + k_m * eps, 0);

	std::priority_queue<Cell*, std::vector<Cell*>, KeyComparer> u;
	u.push(t_start);

	while (!u.empty() && LPApathFound == false)
	{

		// Get the top cell from the priority queue
		Cell* curr = u.top();
		curr->isInOpenList = false;
		u.pop();

		// If the current cell is the goal break out 
		if (curr == t_goal)
		{
			std::cout << "found cell" << std::endl;
			m_LpaStartimer = m_clock.getElapsedTime();
			LPApathFound = true;
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
					double new_cost = curr->getGcost() + heuristic(curr, succ);
					if (new_cost < succ->getGcost()) {
						// checking if it is not a wall 
						if (succ->getTraversable() == true)
						{
							// setting its previous for rebuilding the path
							succ->setPrev(curr);
							succ->setGcost(new_cost);
							// setting the rhs of a suitable neighbour to the min of current rhs cost and the distance of the successor and the current cell
							succ->setRHSCost(std::min(succ->getRhSCost(), curr->getGcost() + heuristic(curr, succ)));
							// checking if it is in the open list
							if (succ->isInOpenList) {
								// updating the node it the function where i recalculate the rhs and g coset
								updateNode(succ, t_goal);
							}
							else {
								succ->isInOpenList = true;
								u.push(succ);
							}
						}
					}
				}
			}
			else
			{
				curr->setGcost(m_infinity);
				for (auto succ : curr->getNeighbours())
				{
					succ->isInOpenList = true;
					updateNode(succ, t_goal);
					u.push(succ);
				}
				curr->isInOpenList = true;
				updateNode(curr, t_goal);
				u.push(curr);
			}
		}
		else
		{
			curr->setKey(m_infinity, m_infinity);
		}
		
		
	}
	std::stack<Cell*> pathTVec= std::stack<Cell*>();

	if (LPApathFound==true)
	{
		// Reconstruct the path from start to goal
		Cell* pathNode = t_goal;
	
		while (pathNode != nullptr)
		{
			std::cout << pathNode->getID() << std::endl;
			pathTVec.push(pathNode);
			pathNode = pathNode->GetPrev();
		
		}
		std::cout << " path vec size " << pathTVec.size() <<std::endl;;
		
	}

	return pathTVec;
}

void Grid::updateNode(Cell* node, Cell* t_goal)
{
	if (node->getTraversable() == true)
	{


		if (node->isInOpenList) {
			// Update the key if the node is in the open list k_m is the maximun cost per move allowed  and eps being the is an estimate on the cost to go to the goal 

			node->setKey(std::min(node->getGcost(), node->getRhSCost()) + heuristic(node, t_goal) + k_m * eps,
				std::min(node->getGcost(), node->getRhSCost()));
		}
		else {
			// Add the node to the open list with a key of (infinity, infinity)
			node->setKey(std::min(node->getGcost(), node->getRhSCost()) + heuristic(node, t_goal) + k_m * m_infinity,
				std::min(node->getGcost(), node->getRhSCost()));
			node->isInOpenList = true;
			//u.push(node);
		}

		// Update the rhs value of the node
		if (node == t_goal) {
			node->setRHSCost(0);
		}
		else {
			double min_rhs = m_infinity;

			for (auto successor : node->getNeighbours()) {


				if (successor->getTraversable() == true)
				{
					double cost = successor->getGcost() + heuristic(node, successor);
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



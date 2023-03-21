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
		return (t_n1->getGcost() ) > (t_n2->getGcost());
	}
};


class KeyComparer {
public:
	bool operator()(const Cell* a, const Cell* b) const {
		return a->m_key > b->m_key;
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
					child->setColor(sf::Color::Green);
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
std::stack<Cell*> Grid::Djkstras(Cell* t_start,Cell* t_goal) {

	Cell* s = t_start;
	Cell* g = t_goal;
	Cell* child;
	std::priority_queue<Cell*, std::vector<Cell*>,GCostComparer > pq;
	std::stack<Cell*> m_stack;

	

	for(int i=0;i<MAX_CELLS;i++)
	{

		Cell* v = atIndex(i);
		v->setGcost( m_infinity);
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
	//child = pq.top();

	while (pq.size() != 0 && pq.top() != g)
	{

		auto iter = pq.top()->getNeighbours().begin();
		auto endIter = pq.top()->getNeighbours().end();

		for (; iter != endIter; iter++)
		{
			// (*iter) is an Arc instance
			// Arc::node() 
			Cell* child = (*iter);
			if (child != pq.top()->GetPrev())
			{
				
				int distanceToChild = ((*iter)->getWeight() + pq.top()->getGcost());
				child->setColor(sf::Color::Green);
				if (distanceToChild < child->getGcost())
				{
					child->setGcost( distanceToChild);
					child->setPrev(pq.top());
					if (child == t_goal) {
						std::cout << "djikstras" << std::endl;
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


void Grid::setPredecessors(Cell* t_cell, Cell* t_source)
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
	
	int g = 0;
	
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

void Grid::update(sf::Time& t_deltatime, WhichAlgorithm t_switcher,GridSize t_gridSizeState)
{
	m_chosenAlgortihm = t_switcher;
	
}


std::stack<Cell*> Grid::LPAStar(Cell* t_start, Cell* t_goal)
{
	// init the grid to suit cinditions 
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
			LPApathFound = true;
			break;
		}
		
		// if the current cell is not a wall 
		if (curr->getTraversable() == true)
		{
			
			// if curr gcost and rhs cost is greater than its rhs cost 
			if (curr->getKey().first > curr->getKey().second)
			{
				curr->setColor(sf::Color::Cyan);
				curr->setRHSCost(curr->getGcost());

				for (auto succ : curr->getNeighbours())
				{
					double new_cost = curr->getGcost() + heuristic(curr, succ);
					if (new_cost < succ->getGcost()) {
						if (succ->getTraversable() == true)
						{
							succ->setPrev(curr);
							succ->setGcost(new_cost);
							succ->setRHSCost(std::min(succ->getRhSCost(), curr->getGcost() + heuristic(curr, succ)));
							if (succ->isInOpenList) {
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
			// Update the key if the node is in the open list
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



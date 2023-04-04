#include "DstarLite.h"




std::pair<double, double> DstarLite::calculateDstarKey(Cell* t_currentSearch, Cell* Start,Grid * t_grid)
{


	double heuristicVal = t_grid->heuristic(t_currentSearch, Start) + K_M;
	double minVal = std::min(t_currentSearch->getGcost(), t_currentSearch->getRhSCost());
	std::pair<double, double> temp1 = std::make_pair(heuristicVal + minVal, std::min(t_currentSearch->getGcost(), t_currentSearch->getRhSCost()));
	return temp1;
}





void DstarLite::initDstar(Cell* t_start, Cell* t_currentSearch, Grid* t_grid)
{
	U_pq = std::priority_queue<Cell*, std::vector<Cell*>, DstarKeyComparer>();
	K_M = 0;

	for (int i = 0; i < t_grid->getMAXCELLS(); i++)
	{
		Cell* v = t_grid->atIndex(i);
		v->setPrev(nullptr);

		// set all gcosets to infinity
		v->setGcost(t_grid->M_INFINITY);

		v->setRHSCost(t_grid->M_INFINITY);

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


	t_currentSearch->setRHSCost(0);
	t_currentSearch->setKey(calculateDstarKey(t_currentSearch, t_start,t_grid).first, calculateDstarKey(t_currentSearch, t_start,t_grid).second);
	U_pq.push(t_currentSearch);


}



void DstarLite::ComputeShortestPath(Cell* t_start, Cell* t_currentSearch, Grid* t_grid)
{

	while (U_pq.top()->getKey() < calculateDstarKey(t_start, t_start,t_grid) || t_start->getGcost() != t_start->getRhSCost())
	{
		Cell* currentCell = U_pq.top();
		if (currentCell != nullptr)
		{


			std::pair<double, double> key_Old = U_pq.top()->getKey();
			std::pair<double, double> key_New = calculateDstarKey(currentCell, t_start,t_grid);

			currentCell->setMarked(true);
			U_pq.pop();
			if (currentCell->getTraversable() == false)
			{
				continue;
			}

			if (key_Old < key_New)
			{
				currentCell->setKey(key_New.first, key_New.second);
				U_pq.push(currentCell);
			}// if it is overconsistant
			else if (currentCell->getGcost() > currentCell->getRhSCost())
			{

				// relaxing the node

				currentCell->setGcost(currentCell->getRhSCost());

				for (auto pre : currentCell->getNeighbours())
				{
					// update their vertexes


					updateVertex(pre, t_currentSearch,t_grid);
				}

			}
			else {
				// if the nodeis underconsistant

				currentCell->setGcost(t_grid->M_INFINITY);

				for (auto neighbours : currentCell->getNeighbours())
				{

					updateVertex(neighbours, t_currentSearch,t_grid);

				}

				updateVertex(currentCell, t_currentSearch,t_grid);
			}
		}
	}




}



sf::Time& DstarLite::getTimer()
{
	return dStarLiteTimer;
}

bool& DstarLite::getDStarPathFound()
{
	return dstarGoalFound;
}

void DstarLite::DstarLiteMain(Cell* t_start, Cell* t_currentSearch, Grid* t_grid) {


	sf::Clock m_clock;
	dStarLiteTimer.asSeconds();
	dStarLiteTimer = m_clock.restart();

	Cell* s_Last = t_start;
	Cell* goal = t_currentSearch;
	initDstar(t_start, t_currentSearch,t_grid);
	ComputeShortestPath(t_start, t_currentSearch,t_grid);


	// t_start . gcost is inifinte still there is no known path 
	float tempMin = t_grid->M_INFINITY;
	Cell* nextNode = nullptr;
	while (t_start != goal)
	{
		for (auto neighbours : t_start->getNeighbours())
		{

			if (neighbours->getWeight() + neighbours->getGcost() < tempMin)
			{
				tempMin = (neighbours->getGcost() + neighbours->getWeight());
				nextNode = neighbours;
			}
		}
		
		t_start->setColor(sf::Color::Green);
		t_start = nextNode;
	}

	
	// checking for any edge cost changes of the surrounding neighbours

	for (auto neighbours : t_start->getNeighbours())
	{
		if (neighbours->getTraversable() == false)
		{
			K_M = K_M + t_grid->heuristic(s_Last, t_start);
			s_Last = t_start;
			updateVertex(neighbours, t_currentSearch, t_grid);
			
		}
		ComputeShortestPath(t_start, t_currentSearch, t_grid);
	}

	if (t_start == goal)
	{
		dStarLiteTimer = m_clock.getElapsedTime();
	}


	

}





void DstarLite::updateVertex(Cell* currentCell, Cell* t_start, Grid* t_grid) {

	if (currentCell != nullptr || t_start != nullptr)
	{
		if (currentCell != t_start)
		{
			double tempMin = t_grid->M_INFINITY;
			for (auto neighbours : currentCell->getNeighbours())
			{
				if (neighbours->getGcost() + neighbours->getWeight() < tempMin)
				{

					tempMin = (neighbours->getGcost() + neighbours->getWeight());
				}
			}

			currentCell->setRHSCost(tempMin);
		}


		priority_queue<Cell*> new_pq;
		while (!U_pq.empty()) {
			Cell* current = U_pq.top();
			U_pq.pop();
			if (current != currentCell) {
				new_pq.push(current);
			}

		}

		while (!new_pq.empty())
		{
			U_pq.push(new_pq.top());
			new_pq.pop();
		}

		if (currentCell != nullptr)
		{
			if (currentCell->getMarked() == false)
			{


				if (currentCell->getGcost() != currentCell->getRhSCost())
				{
					currentCell->setKey(calculateDstarKey(currentCell, t_start,t_grid).first, calculateDstarKey(currentCell, t_start,t_grid).second);
					U_pq.push(currentCell);
				}
			}
		}
	}

}
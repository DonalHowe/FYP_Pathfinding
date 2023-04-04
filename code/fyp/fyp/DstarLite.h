#pragma once
#include<queue>
#include"Cell.h"
#include"Grid.h"
#include<stack>
#include <SFML/Graphics.hpp>

class DstarKeyComparer {
public:
	bool operator()(const Cell* a, const Cell* b) const {
		if (a->m_key.first > b->m_key.first) {
			return true;
		}
		else if (a->m_key.first == b->m_key.first && a->m_key.second > b->m_key.second) {
			return true;
		}
		else {
			return false;
		}
	}
};

class DstarLite
{

public:
	//dstar lite
	float K_M;

	std::priority_queue<Cell*, std::vector<Cell*>, DstarKeyComparer> U_pq;

	void DstarLiteMain(Cell* t_finalGoal, Cell* t_StartCurr,Grid * t_grid);
	void updateVertex(Cell* currentCell, Cell* t_finalGoal,Grid * t_grid);
	void ComputeShortestPath(Cell* t_start, Cell* t_StartCurrGrid,Grid * t_grid);
	void initDstar(Cell* t_finalGoal, Cell* t_StartCurr,Grid * t_grid);
	std::pair<double, double> calculateDstarKey(Cell* t_StartCurr, Cell* t_finalGoal,Grid * t_grid);
	Cell* s_Last;
	sf::Time dStarLiteTimer;
	bool dstarGoalFound = false;
};


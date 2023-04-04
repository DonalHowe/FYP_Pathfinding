#pragma once
#include<queue>
#include"Cell.h"
#include"Grid.h"
#include<stack>
#include <SFML/Graphics.hpp>

class KeyComparer {
public:
	bool operator()(const Cell* a, const Cell* b) const {
		if (a->m_key.first < b->m_key.first) {
			return true;
		}
		else if (a->m_key.first == b->m_key.first && a->m_key.second < b->m_key.second) {
			return true;
		}
		else {
			return false;
		}
	}
};


class LpaStar
{
public:
	//k_m is the maximun cost per move allowedand eps being the is an estimate on the cost to go to the goal
	const float EPS = 2.0f;
	float K_M;
	// LPA*
	std::stack<Cell*> LPAStar(Cell* t_start, Cell* t_goal, Grid* t_grid);
	void updateNode(Cell* node, Cell* Goal, Grid* t_grid);
	std::pair<double, double> calculateKey(Cell* s, Cell* t_goal, Grid* t_grid);
	sf::Time m_LpaStartimer;
	bool LPApathFound = false;

	LpaStar();
	~LpaStar();
};


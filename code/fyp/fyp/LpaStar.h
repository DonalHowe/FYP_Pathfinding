/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
#include<queue>
#include"Cell.h"
#include"Grid.h"
#include<stack>
#include <SFML/Graphics.hpp>



/// <summary>
/// compares the first key against the second to return the smallest 
/// if there is a tie between the two it it returns the higher in the priority queue
/// </summary>
class KeyComparer {
public:
	bool operator()(const Cell* t_a, const Cell* t_b) const {
		if (t_a->m_key.first < t_b->m_key.first) {
			return true;
		}
		else if (t_a->m_key.first == t_b->m_key.first && t_a->m_key.second < t_b->m_key.second) {
			return true;
		}
		else {
			return false;
		}
	}
};


// life long planning a star class 
class LpaStar
{
	// private variables and methods of the class
private:

	// the clock for timer
	sf::Clock m_clock;

	//k_m is the maximun cost per move allowedand eps being the is an estimate on the cost to go to the goal
	const float m_EPS = 2.0f;

	// k_m is the key modifier a value that changes as the search progresses
	float m_K_M;
	
	// the timer for lpa star tracks timer to completion
	sf::Time m_LpaStartimer;

	// temination condition
	bool m_LPApathFound = false;

	// public methods of the class
public:

	// sets the bool for temination back to false
	void setTerminationCondition(bool t_bool);

	// returns the timer for DFS
	sf::Time& getTimer();

	// returns the termination condition
	bool& getLpaStarPathFound();

	//initilises variables for lpaStar
	void initLpaStar(Cell* t_start, Cell* t_goal, Grid* t_grid);

	// lpa star function finds the path 
	void LPAStar(Cell* t_start, Cell* t_goal, Grid* t_grid);

	// update the values of each node or vertex
	void updateNode(Cell* t_node, Cell* Goal, Grid* t_grid);

	//calculates the key of each node 
	std::pair<double, double> calculateKey(Cell* t_current, Cell* t_goal, Grid* t_grid);
	
	// default constructor 
	LpaStar();

	// default destructor
	~LpaStar();
};


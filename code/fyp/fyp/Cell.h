#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"

class Cell
{


	sf::RectangleShape m_rect;
	int m_ID = 0;
	sf::Vector2f m_pos;
	double m_Hcost;
	double m_Fcost;
	double m_Gcost;
	bool m_traversable = true;
	int m_costDistance;
	int prevNeighbour;
	bool m_marked = false;
	bool m_isEndoint = false;
	bool m_isStartoint = false;
public:
	bool getEndPoint();
	void setEndPoint( bool t_et);
	void setStartPoint( bool t_st);

	bool getStartPoint();
	bool getMarked();
	void setMarked(bool t_marked);
	
	void setStartColour();
	void setEndColour();

	int getCostDistance();
	void setCostDistance(int t_cost);

	int getID();

	void setTraversable(bool t_traversable);
	bool getTraversable();

	void setID(int t_id);

	void setPos(sf::Vector2f t_pos);

	double getHcost();
	double getFcost();
	double getGcost();
	sf::Vector2f getPos();
	sf::RectangleShape getRect();
	void initRect();



	int xPos;
	int yPos;


	std::vector<Cell*> m_neighbour;
	void setNeighbours(Cell* t_neighbour);

};


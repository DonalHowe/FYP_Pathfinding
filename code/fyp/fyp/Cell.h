#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include <list>
class Cell
{

	Cell* prev;

	sf::Vector2f m_pos;
	sf::RectangleShape m_rect;

	std::list<Cell*> m_neighbour;

	int m_ID = 0;
	int m_wieght;
	
	double m_Hcost;
	double m_Fcost;
	double m_Gcost;

	bool m_marked = false;
	bool m_isEndoint = false;
	bool m_isStartoint = false;
	bool m_traversable = true;

public:

	void setColor(sf::Color t_color);
	void setWieght(int t_w);
	void setEndPoint( bool t_et);
	void setStartPoint( bool t_st);
	void setPrev(Cell* t_prev);
	void setTraversable(bool t_traversable);
	void setMarked(bool t_marked);
	void setGcost(int t_gcost);
	void setHcost(double t_hcost);
	void initRect();
	void setStartColour();
	void setEndColour();
	void setID(int t_id);
	void setPos(sf::Vector2f t_pos);
	void setNeighbours(Cell* t_neighbour);
	void modifyHCost();// this func for d*

	Cell* GetPrev();
	
	bool& getTraversable();
	bool& getEndPoint();
	bool& getStartPoint();
	bool& getMarked();

	int& getWeight();
	int& getID();

	double& getHcost();
	double& getFcost();
	double& getGcost();

	sf::Vector2f &getPos();
	sf::RectangleShape &getRect();
	std::list<Cell*>& getNeighbours();

	int rectXPos;
	int rectYPos;
	int xPos;
	int yPos;

	
	

};


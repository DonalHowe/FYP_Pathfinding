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
public:
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

};


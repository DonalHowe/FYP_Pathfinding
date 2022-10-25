#include "Cell.h"

void Cell::setStartColour()
{
    m_rect.setFillColor(sf::Color::Blue);
}

int Cell::getPrevNeighbour()
{
    return prevNeighbour;
}

bool Cell::getMarked()
{
    return m_marked;
}


void Cell::setMarked(bool t_marked)
{
    m_marked = t_marked;
}



void Cell::setPrevNeighbour(int t_prev)
{
    prevNeighbour = t_prev;
}


void Cell::setEndColour()
{
    m_rect.setFillColor(sf::Color::Black);
}



int Cell::getCostDistance()
{
    return m_costDistance;
}

void Cell::setCostDistance(int t_cost)
{
    m_costDistance = t_cost;
}

int Cell::getID()
{
    return m_ID;
}

void Cell::setTraversable(bool t_traversable)
{
    m_traversable = t_traversable;
}

bool Cell::getTraversable()
{
    return m_traversable;
}

void Cell::setID(int t_id)
{
    m_ID = t_id;
}

void Cell::setPos(sf::Vector2f t_pos)
{
    m_rect.setPosition(t_pos);
}

double Cell::getHcost()
{
    return m_Hcost;
}

double Cell::getFcost()
{
    return m_Fcost;
}

double Cell::getGcost()
{
    return m_Gcost;
}

sf::Vector2f Cell::getPos()
{
    return m_pos;
}

sf::RectangleShape Cell::getRect()
{
    return m_rect;
}

void Cell::initRect()
{
    m_rect.setFillColor(sf::Color::Transparent);
    m_rect.setOutlineColor(sf::Color::Black);
    m_rect.setOutlineThickness(1.5f);
    m_rect.setSize(sf::Vector2f{ ScreenSize::M_WIDTH / 50,ScreenSize::M_HEIGHT / 50 });
}

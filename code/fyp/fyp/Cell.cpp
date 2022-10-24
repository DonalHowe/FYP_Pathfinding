#include "Cell.h"

int Cell::getID()
{
    return m_ID;
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
    m_rect.setOutlineThickness(4u);
    m_rect.setSize(sf::Vector2f{ ScreenSize::M_WIDTH / 10,ScreenSize::M_HEIGHT / 10 });
}

#include "Cell.h"

Cell::Cell()
{
}

Cell::~Cell()
{
}

void Cell::setStartColour()
{
    m_rect.setFillColor(sf::Color::Blue);
}


bool &Cell::getMarked()
{
    return m_marked;
}

bool& Cell::GetRisenBool()
{
    return m_HcostRisen;
}

bool& Cell::GetLoweredBool()
{
    return m_HcostLowered;
}


void Cell::setMarked(bool t_marked)
{
    m_marked = t_marked;
}

void Cell::setWieght(int t_w)
{
    m_wieght = t_w;
}


int& Cell::getWeight()
{
    return m_wieght;
}


void Cell::setGcost(double t_gcost)
{
    m_Gcost = t_gcost;
}

void Cell::setEndColour()
{
    m_rect.setFillColor(sf::Color::Green);
}


void Cell::setColor(sf::Color t_color)
{
    m_rect.setFillColor(t_color);
}

bool &Cell::getEndPoint()
{
    return m_isEndoint;
}

int &Cell::getID()
{
    return m_ID;
}

void Cell::setRHSCost(double t_rhs)
{
    m_RHScost = t_rhs;
}

void Cell::raiseCost(double t_raise)
{
    m_Hcost += t_raise;
}

void Cell::lowerCost(double t_lower)
{
    m_Hcost -= t_lower;
}

void Cell::setLowerBool(bool t_lower)
{
    m_HcostLowered = t_lower;
}

void Cell::setRisenBool(bool t_lower)
{
    m_HcostLowered = t_lower;
}

Cell* Cell::GetPrev()
{
    return prev;
}

void Cell::setPrev(Cell* t_prev)
{
    prev = t_prev;
}


bool &Cell::getStartPoint()
{
    return m_isStartoint;
}

void Cell::setEndPoint(bool t_)
{
    m_isEndoint = t_;
}

void Cell::setTraversable(bool t_traversable)
{
    m_rect.setFillColor(sf::Color::Red);
    m_key.first= 1000000;
    m_key.second= 1000000;
    m_traversable = t_traversable;
  
}

void Cell::setStartPoint(bool t_et)
{
    m_isStartoint = t_et;
}

bool &Cell::getTraversable()
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

void Cell::setHcost(double t_hcost)
{
    m_Hcost = t_hcost;
}

double &Cell::getHcost()
{
    return m_Hcost;
}

double &Cell::getFcost()
{
    return m_Fcost;
}

bool &Cell::getJumpPoint()
{
    return isJumpPoint;
}

void Cell::setJumpPoint(bool t_b)
{
    isJumpPoint = t_b;
}

double& Cell::getGcost()
{
    return m_Gcost;
}

double& Cell::getRhSCost()
{
    return m_RHScost;
}

sf::Vector2f &Cell::getPos()
{
    return m_pos;
}

sf::RectangleShape &Cell::getRect()
{
    return m_rect;
}

void Cell::initRect(int t_c )
{
    float count = t_c;
    m_rect.setFillColor(sf::Color::White);
    m_rect.setOutlineColor(sf::Color::Black);
    m_rect.setOutlineThickness(2.5f);
    m_rect.setSize(sf::Vector2f{ ScreenSize::M_WIDTH / count,ScreenSize::M_HEIGHT / count });
   
  
}

std::list<Cell*>& Cell::getNeighbours()
{
    return m_neighbour;
}

void Cell::setNeighbours(Cell* t_neighbour)
{
    m_neighbour.push_back(t_neighbour);
}

std::list<Cell*>& Cell::getPredecessors()
{
    return m_predecessors;
}

void Cell::setPredecessorss(Cell* t_neighbour)
{
    m_predecessors.push_back(t_neighbour);
}

void Cell::setFcost(double t_fcost)
{
    m_Fcost = t_fcost;
}


std::pair<double, double> &Cell::getKey()
{
    return m_key;
}

void Cell::setKey(double t1, double t2)
{
    m_key = std::make_pair(t1, t2);
}

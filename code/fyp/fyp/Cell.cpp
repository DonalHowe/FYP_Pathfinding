#include "Cell.h"

Cell::Cell()
{
    
    m_KeyText.setString("KEY: INF,INF ");
    m_rhsText.setString("RHS: INF" );
    m_GcostText.setString("G: INF:");
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
    m_GcostText.setString("G: " + std::to_string(m_Gcost));
}

void Cell::setEndColour()
{
    m_rect.setFillColor(sf::Color::Green);
}


void Cell::setColor(sf::Color t_color)
{
    m_rect.setFillColor(t_color);
}



int &Cell::getID()
{
    return m_ID;
}

void Cell::setRHSCost(double t_rhs)
{
    m_RHScost = t_rhs;
    m_rhsText.setString("RHS: " + std::to_string(m_RHScost));
}

void Cell::raiseCost(double t_raise)
{
    m_Hcost += t_raise;
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

void Cell::setEndPoint(bool t_)
{
    m_isEndoint = t_;
}

bool Cell::getEndPoint()
{
    return m_isEndoint;
}

void Cell::setTraversable(bool t_traversable)
{
    m_rect.setFillColor(sf::Color::Red);
    m_wieght =100000;
    m_traversable = t_traversable;
  
}

void Cell::setStartPoint(bool t_et)
{
    m_isStartoint = t_et;
}

bool Cell::getStartPoint()
{
    return m_isStartoint;
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
    sf::Vector2f G_CostOffset{ 0,25 };
    sf::Vector2f Key_Offset{ 0,50 };
    m_pos = t_pos;
    m_rect.setPosition(t_pos);

    m_rhsText.setPosition(t_pos);
    m_GcostText.setPosition(t_pos+G_CostOffset);
    m_KeyText.setPosition(t_pos+ Key_Offset);
  
    m_rhsText.setCharacterSize(15u);
    m_rhsText.setFillColor(sf::Color::Red);

    m_KeyText.setCharacterSize(15u);
    m_KeyText.setFillColor(sf::Color::Black);

    m_GcostText.setCharacterSize(15u);
    m_GcostText.setFillColor(sf::Color::Blue);
 
  
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
    m_KeyText.setString("KEY: " + std::to_string(t1)+"," + std::to_string(t2));
    m_key = std::make_pair(t1, t2);
}

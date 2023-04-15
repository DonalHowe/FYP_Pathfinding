#include "Cell.h"
/// author : donal Howe
/// 

// default constructor which sets strings 
Cell::Cell()
{
    m_KeyText.setString("KEY: INF,INF ");
    m_rhsText.setString("RHS: INF" );
    m_GcostText.setString("G: INF:");
}

//default destructor
Cell::~Cell()
{
}

// sets a the coulour for the first cell in the path
// where the search starts from
void Cell::setStartColour()
{
    m_rect.setFillColor(sf::Color::Blue);
}

// returns if the cell has been marked
bool &Cell::getMarked()
{
    return m_marked;
}

// returns a cells risen bool which is if its hcost value has been raised
bool& Cell::GetRisenBool()
{
    return m_HcostRisen;
}

// sets the cell to have been marked or not 
void Cell::setMarked(bool t_marked)
{
    m_marked = t_marked;
}

// sets the weight of a cell or its edgecost how much it is to move there
void Cell::setWieght(int t_w)
{
    m_wieght = t_w;
}

// returns a cells weight
int& Cell::getWeight()
{
    return m_wieght;
}

// sets the cells g cost value
void Cell::setGcost(double t_gcost)
{
    m_Gcost = t_gcost;
    m_GcostText.setString("G: " + std::to_string(m_Gcost));
}

// sets a the coulour for the last cell in the path
  // where the search end from
void Cell::setEndColour()
{
    m_rect.setFillColor(sf::Color::Green);
}

//sets the colour of a cells sf::rectangleShape
void Cell::setColor(sf::Color t_color)
{
    m_rect.setFillColor(t_color);
}

// returns the cells id number
int &Cell::getID()
{
    return m_ID;
}

// sets the cells rhs cost value
void Cell::setRHSCost(double t_rhs)
{
    m_RHScost = t_rhs;
    m_rhsText.setString("RHS: " + std::to_string(m_RHScost));
}

// raises the cost of cell
void Cell::raiseCost(double t_raise)
{
    m_Hcost += t_raise;
}

// sets is risen booloan of the cell 
void Cell::setRisenBool(bool t_lower)
{
    m_HcostLowered = t_lower;
}

// returns a cells previous pointer cell or pointer to that cells parent
Cell* Cell::GetPrev()
{
    return m_prev;
}

// sets that cells previous pointer
void Cell::setPrev(Cell* t_prev)
{
    m_prev = t_prev;
}

// sets if the cell is the end poinht in the search
void Cell::setEndPoint(bool t_)
{
    m_isEndoint = t_;
}

// returns the cells enpoint boolean
bool Cell::getEndPoint()
{
    return m_isEndoint;
}

// sets the cells traversable boolean and weight to 10000000000 so its never searched
void Cell::setTraversable(bool t_traversable)
{
    m_rect.setFillColor(sf::Color::Red);
    m_wieght =100000;
    m_traversable = t_traversable;
}

// sets if the cell is the start poinht in the search
void Cell::setStartPoint(bool t_et)
{
    m_isStartoint = t_et;
}

// returns the cells startpoint boolean
bool Cell::getStartPoint()
{
    return m_isStartoint;
}

//returns the cells traversable boolean
bool &Cell::getTraversable()
{
    return m_traversable;
}

// sets the cells if number
void Cell::setID(int t_id)
{
    m_ID = t_id;
}

// sets the position of each cell and its corresponding info
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

// sets the cells h cost value
void Cell::setHcost(double t_hcost)
{
    m_Hcost = t_hcost;
}

// returns the cells h cost value
double &Cell::getHcost()
{
    return m_Hcost;
}

// returns the cell s f cost value
double &Cell::getFcost()
{
    return m_Fcost;
}

// returns if that cell is a jumppoint
bool &Cell::getJumpPoint()
{
    return m_isJumpPoint;
}

// sets if that cell us a jumppoint
void Cell::setJumpPoint(bool t_b)
{
    m_isJumpPoint = t_b;
}

// returns the cells g cost value
double& Cell::getGcost()
{
    return m_Gcost;
}

// returns the cells rhs cost value
double& Cell::getRhSCost()
{
    return m_RHScost;
}

// returns the cells sf::Rectangle shapes position
sf::Vector2f &Cell::getPos()
{
    return m_pos;
}

// returns the cells sf::RectangleShape
sf::RectangleShape &Cell::getRect()
{
    return m_rect;
}

// fucntion whic creates the sf::rectangle shape 

void Cell::initRect(int t_c )
{
    float count = t_c;
    m_rect.setFillColor(sf::Color::White);
    m_rect.setOutlineColor(sf::Color::Black);
    m_rect.setOutlineThickness(2.5f);
    m_rect.setSize(sf::Vector2f{ ScreenSize::M_WIDTH / count,ScreenSize::M_HEIGHT / count });
}

// return that cells neighbours
std::list<Cell*>& Cell::getNeighbours()
{
    return m_neighbour;
}

// sets that cells neigbours
void Cell::setNeighbours(Cell* t_neighbour)
{
    m_neighbour.push_back(t_neighbour);
}

// retuns that cells predecessors
std::list<Cell*>& Cell::getPredecessors()
{
    return m_predecessors;
}

// sets the predecessors for that cell
void Cell::setPredecessorss(Cell* t_neighbour)
{
    m_predecessors.push_back(t_neighbour);
}

// sets the fcost value for that cell
void Cell::setFcost(double t_fcost)
{
    m_Fcost = t_fcost;
}

// returns the cells std::pair whihc is its key
std::pair<double, double> &Cell::getKey()
{
    return m_key;
}

// sets the values for the cells key
void Cell::setKey(double t1, double t2)
{
    m_KeyText.setString("KEY: " + std::to_string(t1)+"," + std::to_string(t2));
    m_key = std::make_pair(t1, t2);
}

/// author : donal Howe
/// 
/// included libraries and dependencies
/// 

#pragma once
#include <list>
#include <limits>
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

// the cell class 
class Cell
{
    // public variables of the class
public:

    // the  default constructor 
     Cell();

     // default destructor
    ~Cell();

    // sets a the coulour for the first cell in the path
    // where the search starts from
    void setStartColour();

    // sets a the coulour for the last cell in the path
   // where the search end from
    void setEndColour();

    //sets the colour of a cells sf::rectangleShape
    void setColor(sf::Color t_color);

    // sets the cell to have been marked or not 
    void setMarked(bool t_marked);

    // returns if the cell has been marked
    bool& getMarked();
    
    // sets the cells traversable boolean
    void setTraversable(bool t_traversable);

    //returns the cells traversable boolean
    bool& getTraversable();
    
    // sets if the cell is the end poinht in the search
    void setEndPoint(bool t_isEndpoint);

    // returns the cells enpoint boolean
    bool getEndPoint();

    // sets if the cell is the start poinht in the search
    void setStartPoint(bool t_isStartpoint);

    // returns the cells startpoint boolean
    bool getStartPoint();
   
    // returns the cells id number
    int& getID();

    // sets the cells if number
    void setID(int t_id);

    // returns the cells g cost value
    double& getGcost();

    // sets the cells g cost value
    void setGcost(double t_gcost);

    // returns the cells h cost value
    double& getHcost();

    // sets the cells h cost value
    void setHcost(double t_hcost);

    // returns the cells rhs cost value
    double& getRhSCost();

    // sets the cells rhs cost value
    void setRHSCost(double t_rhs);

    // returns a cells risen bool which is if its hcost value has been raised
    bool& GetRisenBool();

    // sets is risen booloan of the cell 
    void setRisenBool(bool t_isRisen);

    // raises the cost of cell
    void raiseCost(double t_raise);
 
    // sets the weight of a cell or its edgecost how much it is to move there
    void setWieght(int t_w);

    // returns a cells weight
    int& getWeight();

    // returns the cells sf::Rectangle shapes position
    sf::Vector2f& getPos();

    // sets the position of the cells sf::rectangleShape
    void setPos(sf::Vector2f t_pos);
    
    // returns the cells sf::RectangleShape
    sf::RectangleShape& getRect();

    // fucntion whic creates the sf::rectangle shape 
    void initRect(int t_c);

    // returns a cells previous pointer cell or pointer to that cells parent
    Cell* GetPrev();

    // sets that cells previous pointer
    void setPrev(Cell* t_prev);

    // return that cells neighbours
    std::list<Cell*>& getNeighbours();

    // sets that cells neigbours
    void setNeighbours(Cell* t_neighbour);

    // retuns that cells predecessors
    std::list<Cell*>& getPredecessors();

    // sets the predecessors for that cell
    void setPredecessorss(Cell* t_neighbour);

    // sets the fcost value for that cell
    void setFcost(double t_fcost);

    // returns the cell s f cost value
    double& getFcost();

    // returns if that cell is a jumppoint
    bool &getJumpPoint();

    // sets if that cell us a jumppoint
    void setJumpPoint(bool t_b);
  
    // the cells gcost value
    double m_Gcost=0;

    // the cells hcost value
    double m_Hcost;

    // the cells rhscost value
    double m_RHScost;

    // the cells fcost value
    double m_Fcost;

    // the cells xpos value which is column number
    float Xpos;

    // the cells ypos value which is row number
    float Ypos;

    // the cells weight
    int m_wieght;

    // the cells is in open list boolean 
    bool isInOpenList = false;

    // returns the cells std::pair whihc is its key
    std::pair<double, double> &getKey();

    // sets the values for the cells key
    void setKey(double t1,double t2);

    // the cells key value
    std::pair<double,double> m_key;

    // rhs cost text 
    sf::Text m_rhsText;

    // g cost text 
    sf::Text m_GcostText;

    // key cost text 
    sf::Text m_KeyText;
   
   // privare variables of the class
private:

    // class private booleans
    bool m_marked;
    bool m_isEndoint;
    bool m_isStartoint;
    bool m_traversable;
    bool isJumpPoint = false;
    bool m_HcostRisen;
    bool m_HcostLowered;

    // class private ints
    int m_ID;
  
    // class private sf::Vector2f
    sf::Vector2f m_pos;

    // class private sf::rectangles shapes
    sf::RectangleShape m_rect;

    // class private Cell pointers
    Cell* prev;

    // class private lists/ datastructures
    std::list<Cell*> m_neighbour;
    std::list<Cell*> m_predecessors;

};


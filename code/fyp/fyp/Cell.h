#pragma once
#include <list>
#include <utility>
#include <cmath>
#include <limits>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "ScreenSize.h"


class Cell
{
public:
     Cell();
    ~Cell();

   
    void setStartColour();
    void setEndColour();
    void setColor(sf::Color t_color);

    void setMarked(bool t_marked);
    bool& getMarked();

    void setTraversable(bool t_traversable);
    bool& getTraversable();

   
    void setEndPoint(bool t_isEndpoint);
    void setStartPoint(bool t_isStartpoint);
   

    int& getID();
    void setID(int t_id);

    double& getGcost();
    void setGcost(double t_gcost);

    double& getHcost();
    void setHcost(double t_hcost);

    double& getRhSCost();
    void setRHSCost(double t_rhs);

   

    bool& GetRisenBool();
    void setRisenBool(bool t_isRisen);

  

    void raiseCost(double t_raise);
 

    void setWieght(int t_w);
    int& getWeight();


    sf::Vector2f& getPos();
    void setPos(sf::Vector2f t_pos);

    sf::RectangleShape& getRect();
    void initRect(int t_c);

    Cell* GetPrev();
    void setPrev(Cell* t_prev);

    std::list<Cell*>& getNeighbours();
    void setNeighbours(Cell* t_neighbour);

    std::list<Cell*>& getPredecessors();
    void setPredecessorss(Cell* t_neighbour);

    void setFcost(double t_fcost);
    double& getFcost();

    bool &getJumpPoint();
    void setJumpPoint(bool t_b);
  
    double m_Gcost;
    double m_Hcost;
    double m_RHScost;
    double m_Fcost;

    float Xpos;
    float Ypos;
    int m_wieght;
  
    bool isInOpenList = false;

    std::pair<double, double> &getKey();
    void setKey(double t1,double t2);
    std::pair<double,double> m_key;

private:
    bool m_marked;
    bool m_isEndoint;
    bool m_isStartoint;
    bool m_traversable;
    bool isJumpPoint = false;
    int m_ID;
  
    bool m_HcostRisen;
    bool m_HcostLowered;

    sf::Vector2f m_pos;
    sf::RectangleShape m_rect;

    Cell* prev;

    std::list<Cell*> m_neighbour;
    std::list<Cell*> m_predecessors;

};


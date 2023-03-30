#include "Menu.h"

Menu::Menu()
{

    if (!m_font.loadFromFile("BebasNeue.otf"))
    {
        std::string s("Error loading font");
        throw std::exception(s.c_str());
    }
    
  
    float yPos = 100;
    float XPos = 10;
    m_rect.setFillColor(sf::Color::Red);
    m_rect.setSize(sf::Vector2f{ 150,150 });
    
    for (int i = 0; i < 9; i++)
    {
        m_text[i].setFont(m_font);
        m_text[i].setPosition(XPos, yPos);
        m_text[i].setCharacterSize(40u);
        m_text[i].setFillColor(sf::Color::Black);
        m_rect.setPosition(XPos, yPos);
        m_rect.setOutlineThickness(4u);
        m_rect.setOutlineColor(sf::Color::Black);
        m_rectVec.push_back(m_rect);
        XPos += 300;
       
       
    }
    m_text[0].setString(" Small");
    m_text[1].setString(" Medium");
    m_text[2].setString(" Large");
    m_text[3].setString(" Astar");
    m_text[3].setPosition(10, 260);
    m_rectVec.at(3).setFillColor(sf::Color::Blue);
    m_rectVec.at(3).setPosition(10, 260);

    m_text[4].setString("Dstar_Lite");
    m_text[4].setPosition(310, 260);
    m_rectVec.at(4).setFillColor(sf::Color::Cyan);
    m_rectVec.at(4).setPosition(310, 260);

 
    m_text[5].setString("LPA_Star");
    m_text[5].setPosition(10, 420);
    m_rectVec.at(5).setFillColor(sf::Color::Green);
    m_rectVec.at(5).setPosition(10, 420);

    m_text[6].setString("Depth(dfs)");
    m_text[6].setPosition(310, 420);
    m_rectVec.at(6).setFillColor(sf::Color::Green);
    m_rectVec.at(6).setPosition(310, 420);

    m_text[7].setString(" Jps");
    m_text[7].setPosition(610, 260);
    m_rectVec.at(7).setFillColor(sf::Color::Green);
    m_rectVec.at(7).setPosition(610, 260);

    
    
    m_text[8].setString(" Djkstras");
    m_text[8].setPosition(610, 420);
    m_rectVec.at(8).setFillColor(sf::Color::Green);
    m_rectVec.at(8).setPosition(610, 420);

  


   

}

Menu::~Menu()
{
}

WhichAlgorithm& Menu::getalg()
{
    return m_slgSwitcher;
}

GridSize Menu::setGridSize(sf::RenderWindow& t_windowTwo, Grid& t_grid,Cell *t_cell)
{
    
    const  sf::RenderWindow& m_windowTwo = t_windowTwo;
    sf::Vector2f m_MousePos = sf::Vector2f{ sf::Mouse::getPosition(m_windowTwo) };
   
        if (m_rectVec.at(0).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::small;
                t_grid.m_theTableVector.clear();
                t_grid.numberOfRows = 6;
                t_grid.numberOfCols = 6;
                t_grid.MAX_CELLS = t_grid.numberOfRows* t_grid.numberOfCols;
               
               
                t_grid.setupGrid(t_grid.numberOfCols);
              
                
                std::cout << " small" << std::endl;
            }
            m_rectVec.at(0).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(0).setSize(sf::Vector2f{ 150,150 });
        }

        if (m_rectVec.at(1).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::large;
                t_grid.m_theTableVector.clear();
                t_grid.MAX_CELLS = 6400;
                t_grid.numberOfRows = 80;
                t_grid.numberOfCols = 80;
              
                t_grid.setupGrid(80);
               
                std::cout << " Large " << std::endl;
            }
            m_rectVec.at(1).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(1).setSize(sf::Vector2f{ 150,150 });
        }

        if (m_rectVec.at(2).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::veryLarge;
                t_grid.m_theTableVector.clear();
               
                t_grid.MAX_CELLS = 22500;
                t_grid.numberOfRows = 150;
                t_grid.numberOfCols = 150;
             
                t_grid.setupGrid(150);
            
                std::cout << "22 500 " << std::endl;
            }
            m_rectVec.at(2).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(2).setSize(sf::Vector2f{ 150,150 });
        }
        if (m_rectVec.at(3).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
              
                m_slgSwitcher = WhichAlgorithm::Astar;
               
                std::cout << "Astar" << std::endl;
            }
            m_rectVec.at(3).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(3).setSize(sf::Vector2f{ 150,150 });
        }

        if (m_rectVec.at(4).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
               
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
               
                m_slgSwitcher = WhichAlgorithm::DstarLite;
                std::cout << "Dstar" << std::endl;
            }
           
            m_rectVec.at(4).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(4).setSize(sf::Vector2f{ 150,150 });
        }

       

        if (m_rectVec.at(5).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                
                m_slgSwitcher = WhichAlgorithm::LPASTAR;
                std::cout << "LPA* " << std::endl;
            }
            m_rectVec.at(5).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(5).setSize(sf::Vector2f{ 150,150 });
        }


        if (m_rectVec.at(6).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                //t_grid.resetAlgorithm();
               
                m_slgSwitcher = WhichAlgorithm::DEPTH;
                std::cout << "DEpthFirstSearch " << std::endl;
            }
            m_rectVec.at(6).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(6).setSize(sf::Vector2f{ 150,150 });
        }


        if (m_rectVec.at(7).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

             
               
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                
                m_slgSwitcher = WhichAlgorithm::JPS;
                std::cout << "jump Point " << std::endl;
            }
            m_rectVec.at(7).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(7).setSize(sf::Vector2f{ 150,150 });
        }

        if (m_rectVec.at(8).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

              
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
               
                m_slgSwitcher = WhichAlgorithm::DIKSTRAS;
               
                std::cout << "DIKSTRAS " << std::endl;
            }
            m_rectVec.at(8).setSize(sf::Vector2f{ 190,150 });
        }
        else {
            m_rectVec.at(8).setSize(sf::Vector2f{ 150,150 });
        }





  
        return m_gridSwitcher;

}

std::vector<sf::RectangleShape> Menu::getVec()
{
    return m_rectVec;
}

void Menu::render(sf::RenderWindow& t_window)
{
    
    for (int i = 0; i < 9; i++)
    {
        t_window.draw(m_rectVec.at(i));
      
    }

    for (int i = 0; i < 11; i++)
    {
       
        t_window.draw(m_text[i]);
    }
}

void Menu::update(sf::Time t_deltaTime)
{
}

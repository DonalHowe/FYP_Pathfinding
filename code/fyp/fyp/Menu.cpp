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
    
    for (int i = 0; i < 11; i++)
    {
        m_text[i].setFont(m_font);
        m_text[i].setPosition(XPos, yPos);
        m_text[i].setCharacterSize(40u);
        m_text[i].setFillColor(sf::Color::Black);
        m_rect.setPosition(XPos, yPos);
        m_rectVec.push_back(m_rect);
        XPos += 300;
       
       
    }
    m_text[0].setString("2,500");
    m_text[1].setString("6,400");
    m_text[2].setString("22,500");

  
   
    m_text[3].setString("Astar");
    m_text[3].setPosition(10, 260);
    m_rectVec.at(3).setFillColor(sf::Color::Blue);
    m_rectVec.at(3).setPosition(10, 260);

    m_text[4].setString("Dstar_Lite");
    m_text[4].setPosition(310, 260);

    m_rectVec.at(4).setFillColor(sf::Color::Cyan);
    m_rectVec.at(4).setPosition(310, 260);

    m_text[5].setString("IDA_Star");
    m_text[5].setPosition(610, 260);
    m_rectVec.at(5).setFillColor(sf::Color::Green);
    m_rectVec.at(5).setPosition(610, 260);

    m_text[6].setString("LPA_Star");
    m_text[6].setPosition(310, 420);
    m_rectVec.at(6).setFillColor(sf::Color::Green);
    m_rectVec.at(6).setPosition(10, 420);

    m_text[7].setString("Depth(dfs");
    m_text[7].setPosition(610, 420);
    m_rectVec.at(7).setFillColor(sf::Color::Green);
    m_rectVec.at(7).setPosition(310, 420);

    m_text[8].setString("Jps");
    m_text[8].setPosition(10, 580);
    m_rectVec.at(8).setFillColor(sf::Color::Green);
    m_rectVec.at(8).setPosition(610, 420);

    
    m_rectVec.at(9).setFillColor(sf::Color::Green);
    m_rectVec.at(9).setPosition(10, 580);

    m_text[9].setString("Djkstras");
    m_text[9].setPosition(310, 580);

    m_text[10].setString("BFS");
    m_text[10].setPosition(10, 420);
    m_rectVec.at(10).setFillColor(sf::Color::Green);
    m_rectVec.at(10).setPosition(310, 580);


   

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
                t_grid.MAX_CELLS = 2500;
                t_grid.MAX_ROWS = 50;
                t_grid.MAX_COLS = 50;
               
                t_grid.setupGrid(50);
                
                std::cout << " small" << std::endl;
            }
        }

        if (m_rectVec.at(1).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::large;
                t_grid.m_theTableVector.clear();
                t_grid.MAX_CELLS = 6400;
                t_grid.MAX_ROWS = 80;
                t_grid.MAX_COLS = 80;
              
                t_grid.setupGrid(80);
                std::cout << " Large " << std::endl;
            }
        }
        if (m_rectVec.at(2).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::veryLarge;
                t_grid.m_theTableVector.clear();
               
                t_grid.MAX_CELLS = 22500;
                t_grid.MAX_ROWS = 150;
                t_grid.MAX_COLS = 150;
             
                t_grid.setupGrid(150);
                std::cout << "22 500 " << std::endl;
            }
        }
        if (m_rectVec.at(3).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
             
                m_slgSwitcher = WhichAlgorithm::Astar;
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                std::cout << "Astar" << std::endl;
            }
        }
        if (m_rectVec.at(4).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
               
                m_slgSwitcher = WhichAlgorithm::DstarLite;
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
              
                std::cout << "Dstar" << std::endl;
            }
           

        }

        if (m_rectVec.at(5).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
              
                m_slgSwitcher = WhichAlgorithm::ida;
                std::cout << "IDA* " << std::endl;
            }
        }
        // nothing here
        if (m_rectVec.at(6).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                m_slgSwitcher = WhichAlgorithm::BestFirstSearch;
                std::cout << "Best First Search " << std::endl;
            }
        }

        if (m_rectVec.at(7).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                m_slgSwitcher = WhichAlgorithm::LPASTAR;
                std::cout << "LPA* " << std::endl;
            }
        }


        if (m_rectVec.at(8).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                m_slgSwitcher = WhichAlgorithm::DEPTH;
                std::cout << "DEpthFirstSearch " << std::endl;
            }
        }


        if (m_rectVec.at(9).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                m_slgSwitcher = WhichAlgorithm::JPS;
                std::cout << "jump Point " << std::endl;
            }
        }

        if (m_rectVec.at(10).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                m_slgSwitcher = WhichAlgorithm::DIKSTRAS;
                std::cout << "DIKSTRAS " << std::endl;
            }
        }





  
        return m_gridSwitcher;

}

std::vector<sf::RectangleShape> Menu::getVec()
{
    return m_rectVec;
}

void Menu::render(sf::RenderWindow& t_window)
{
    
    for (int i = 0; i < 11; i++)
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

#include "Menu.h"

Menu::Menu()
{
    float yPos = 100;
    float XPos = 10;
    m_rect.setFillColor(sf::Color::Red);
    m_rect.setSize(sf::Vector2f{ 150,200 });
    
    for (int i = 0; i < 6; i++)
    {
        m_rect.setPosition(XPos, yPos);
        m_rectVec.push_back(m_rect);
        XPos += 300;
       
       
    }
    m_rectVec.at(3).setFillColor(sf::Color::Blue);
    m_rectVec.at(3).setPosition(10, 400);
    m_rectVec.at(4).setFillColor(sf::Color::Black);
    m_rectVec.at(4).setPosition(310, 400);
    m_rectVec.at(5).setFillColor(sf::Color::Green);
    m_rectVec.at(5).setPosition(610, 400);

}

Menu::~Menu()
{
}

GridSize Menu::setGridSize(sf::RenderWindow& t_windowTwo, Grid& t_grid)
{
    
    const  sf::RenderWindow& m_windowTwo = t_windowTwo;
    sf::Vector2f m_MousePos = sf::Vector2f{ sf::Mouse::getPosition(m_windowTwo) };
   
        if (m_rectVec.at(0).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::small;
                t_grid.MAX_CELLS = 2500;
                t_grid.MAX_ROWS = 50;
                t_grid.MAX_COLS = 50;
                t_grid.setupGrid();
                std::cout << " small" << std::endl;
            }
        }

        if (m_rectVec.at(1).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::large;
                t_grid.MAX_CELLS = 5000;
                t_grid.MAX_ROWS = 100;
                t_grid.MAX_COLS = 100;
                t_grid.setupGrid();
                std::cout << " Large " << std::endl;
            }
        }
        if (m_rectVec.at(2).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::veryLarge;
                t_grid.MAX_CELLS = 5000;
                t_grid.MAX_ROWS = 1000;
                t_grid.MAX_COLS = 1000;
                t_grid.setupGrid();
                std::cout << "very large " << std::endl;
            }
        }
        if (m_rectVec.at(3).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_slgSwitcher = WhichAlgorithm::Astar;
                t_grid.m_chosenAlgortihm = WhichAlgorithm::Astar;
                std::cout << "Astar" << std::endl;
            }
        }
        if (m_rectVec.at(4).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_slgSwitcher = WhichAlgorithm::Dstar;
                t_grid.m_chosenAlgortihm = WhichAlgorithm::Dstar;
                std::cout << "Dstar" << std::endl;
            }
           

        }

        if (m_rectVec.at(5).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_slgSwitcher = WhichAlgorithm::IDA;
                t_grid.m_chosenAlgortihm = WhichAlgorithm::IDA;
                std::cout << "IDA " << std::endl;
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
    for (int i = 0; i < 6; i++)
    {
        t_window.draw(m_rectVec.at(i));
    }
    
}

void Menu::update(sf::Time t_deltaTime)
{
}

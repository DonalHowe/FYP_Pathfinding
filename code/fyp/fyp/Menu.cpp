#include "Menu.h"

Menu::Menu()
{

    if (!m_font.loadFromFile("BebasNeue.otf"))
    {
        std::string s("Error loading font");
        throw std::exception(s.c_str());
    }
    
  
    float yPos = 40;
    float XPos = 10;
    m_rect.setFillColor(sf::Color::Red);
   
    
    for (int i = 0; i < 13; i++)
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
    m_text[3].setPosition(10, 210);
    m_rectVec.at(3).setFillColor(sf::Color::Blue);
    m_rectVec.at(3).setPosition(10, 210);

    m_text[4].setString("Dstar\nLite");
    m_text[4].setPosition(310, 210);
    m_rectVec.at(4).setFillColor(sf::Color::Cyan);
    m_rectVec.at(4).setPosition(310, 210);

 
    m_text[5].setString("LPA\nStar");
    m_text[5].setPosition(10, 380);
    m_rectVec.at(5).setFillColor(sf::Color::Green);
    m_rectVec.at(5).setPosition(10, 380);

    m_text[6].setString("Depth\n(dfs)");
    m_text[6].setPosition(310, 380);
    m_rectVec.at(6).setFillColor(sf::Color::Green);
    m_rectVec.at(6).setPosition(310, 380);

    m_text[12].setString("Jump\nPoint \nSearch");
    m_text[12].setPosition(610, 380);
    m_rectVec.at(12).setFillColor(sf::Color::Green);
    m_rectVec.at(12).setPosition(610, 380);


    m_text[8].setString("Dijkstras");
    m_text[8].setPosition(610, 210);
    m_rectVec.at(8).setFillColor(sf::Color::Green);
    m_rectVec.at(8).setPosition(610, 210);


    m_text[7].setString("I Want To Race The\nAlgorithms");
    m_text[7].setPosition(10, 590);
    m_rectVec.at(7).setFillColor(sf::Color::Green);
    m_rectVec.at(7).setPosition(10, 590);
  

    m_text[9].setString("I Don't Want To Race\nThe Algorithms");
    m_text[9].setPosition(10, 700);
    m_rectVec.at(9).setFillColor(sf::Color::Green);
    m_rectVec.at(9).setPosition(10, 700);
    
 

    m_text[10].setString(" I Want Debug On");
    m_text[10].setPosition(460, 590);
    m_rectVec.at(10).setFillColor(sf::Color::Green);
    m_rectVec.at(10).setPosition(460, 590);

    m_text[11].setString("I Want Debug Off");
    m_text[11].setPosition(460, 700);
    m_rectVec.at(11).setFillColor(sf::Color::Green);
    m_rectVec.at(11).setPosition(460, 700);

  


   

}

Menu::~Menu()
{
}

WhichAlgorithm& Menu::getalg()
{
    return m_slgSwitcher;
}

GridSize& Menu::setGridSize(sf::RenderWindow& t_windowTwo, Grid& t_grid, Grid& t_gridTwo,Cell *t_cell)
{
    
    const  sf::RenderWindow& m_windowTwo = t_windowTwo;
    sf::Vector2f m_MousePos = sf::Vector2f{ sf::Mouse::getPosition(m_windowTwo) };
   
        if (m_rectVec.at(0).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::small;
                t_grid.m_theTableVector.clear();
                t_gridTwo.m_theTableVector.clear();

                t_grid.setRows(10);
                t_grid.setColumns(10);
                t_gridTwo.setRows(10);
                t_gridTwo.setColumns(10);

                t_grid.setMAXCELLS(t_grid.getNumberOfRows() * t_grid.getnumberOfCols());
                t_gridTwo.setMAXCELLS(t_gridTwo.getNumberOfRows() * t_gridTwo.getnumberOfCols());
               
                t_grid.setupGrid(t_grid.getnumberOfCols());
                t_gridTwo.setupGrid(t_gridTwo.getnumberOfCols());
              
                
                std::cout << " small" << std::endl;
            }
            m_rectVec.at(0).setSize(sf::Vector2f{ 190,150 });
            m_rectVec.at(0).setFillColor(sf::Color::Yellow);
        }
        else {
            m_rectVec.at(0).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(0).setFillColor(sf::Color::Red);
        }

        if (m_rectVec.at(1).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::large;
                t_grid.m_theTableVector.clear();
                t_gridTwo.m_theTableVector.clear();

                t_grid.setRows(50);
                t_grid.setColumns(50);
                t_gridTwo.setRows(50);
                t_gridTwo.setColumns(50);


                t_grid.setMAXCELLS(t_grid.getNumberOfRows() * t_grid.getnumberOfCols());
                t_gridTwo.setMAXCELLS(t_gridTwo.getNumberOfRows() * t_gridTwo.getnumberOfCols());

                t_grid.setupGrid(t_grid.getnumberOfCols());
                t_gridTwo.setupGrid(t_gridTwo.getnumberOfCols());

               
                std::cout << " meduim " << std::endl;
            }
            m_rectVec.at(1).setSize(sf::Vector2f{ 190,150 });
            m_rectVec.at(1).setFillColor(sf::Color::Yellow);
            m_rectVec.at(1).setOutlineThickness(8u);

        }
        else {
            m_rectVec.at(1).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(1).setFillColor(sf::Color::Red);
            m_rectVec.at(1).setOutlineThickness(4u);
        }

        if (m_rectVec.at(2).getGlobalBounds().contains(m_MousePos))
        {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                m_gridSwitcher = GridSize::veryLarge;
                t_grid.m_theTableVector.clear();
                t_gridTwo.m_theTableVector.clear();
              
                t_grid.setRows( 100);
                t_grid.setColumns( 100);
                t_gridTwo.setRows( 100);
                t_gridTwo.setColumns(100);
             
                t_grid.setMAXCELLS(t_grid.getNumberOfRows() * t_grid.getnumberOfCols());
                t_gridTwo.setMAXCELLS(t_gridTwo.getNumberOfRows() * t_gridTwo.getnumberOfCols());


                t_grid.setupGrid(t_grid.getnumberOfCols());
                t_gridTwo.setupGrid(t_gridTwo.getnumberOfCols());
            
                std::cout << "100000 " << std::endl;
            }
            m_rectVec.at(2).setSize(sf::Vector2f{ 170,150 });
            m_rectVec.at(2).setOutlineThickness(8u);
            m_rectVec.at(2).setFillColor(sf::Color::Yellow);
        }
        else {
            m_rectVec.at(2).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(2).setFillColor(sf::Color::Red);
            m_rectVec.at(2).setOutlineThickness(4u);
        }
        if (m_rectVec.at(3).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;
              
                m_slgSwitcher = WhichAlgorithm::Astar;
               
                std::cout << "Astar" << std::endl;
            }
            m_rectVec.at(3).setSize(sf::Vector2f{ 190,150 });
            m_rectVec.at(3).setFillColor(sf::Color::Yellow);
            m_rectVec.at(3).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(3).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(3).setFillColor(sf::Color::Cyan);
            m_rectVec.at(3).setOutlineThickness(4u);
        }

        if (m_rectVec.at(4).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
               
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;


                m_slgSwitcher = WhichAlgorithm::DstarLite;
                std::cout << "Dstar" << std::endl;
            }
           
            m_rectVec.at(4).setSize(sf::Vector2f{ 190,150 });
            m_rectVec.at(4).setFillColor(sf::Color::Yellow);
            m_rectVec.at(4).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(4).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(4).setFillColor(sf::Color::Cyan);
            m_rectVec.at(4).setOutlineThickness(4u);
        }

       

        if (m_rectVec.at(5).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                
                m_slgSwitcher = WhichAlgorithm::LPASTAR;
                std::cout << "LPA* " << std::endl;
            }
            m_rectVec.at(5).setSize(sf::Vector2f{ 190,150 });
            m_rectVec.at(5).setFillColor(sf::Color::Yellow);
            m_rectVec.at(5).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(5).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(5).setFillColor(sf::Color::Green);
            m_rectVec.at(5).setOutlineThickness(4u);
        }


        if (m_rectVec.at(6).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;
               
               
                m_slgSwitcher = WhichAlgorithm::DEPTH;
                std::cout << "DEpthFirstSearch " << std::endl;
            }
            m_rectVec.at(6).setSize(sf::Vector2f{ 190,150 });
            m_rectVec.at(6).setFillColor(sf::Color::Yellow);
            m_rectVec.at(6).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(6).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(6).setFillColor(sf::Color::Green);
            m_rectVec.at(6).setOutlineThickness(4u);
        }


        if (m_rectVec.at(12).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;


                m_slgSwitcher = WhichAlgorithm::JPS;
                std::cout << "jump point search " << std::endl;
            }
            m_rectVec.at(12).setSize(sf::Vector2f{ 170,150 });
            m_rectVec.at(12).setFillColor(sf::Color::Yellow);
            m_rectVec.at(12).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(12).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(12).setFillColor(sf::Color::Green);
            m_rectVec.at(12).setOutlineThickness(4u);
        }



        if (m_rectVec.at(8).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

              
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;
               
                m_slgSwitcher = WhichAlgorithm::DIKSTRAS;
               
                std::cout << "DIKSTRAS " << std::endl;
            }
            m_rectVec.at(8).setSize(sf::Vector2f{ 170,150 });
            m_rectVec.at(8).setFillColor(sf::Color::Yellow);
            m_rectVec.at(8).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(8).setSize(sf::Vector2f{ 150,150 });
            m_rectVec.at(8).setFillColor(sf::Color::Cyan);
            m_rectVec.at(8).setOutlineThickness(4u);
        }

        if (m_rectVec.at(7).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;

                m_raceDecider = Race::yes;
                std::cout << "Race yes " << std::endl;
            }
            m_rectVec.at(7).setSize(sf::Vector2f{ 320,90 });
            m_rectVec.at(7).setFillColor(sf::Color::Yellow);
            m_rectVec.at(7).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(7).setSize(sf::Vector2f{ 285,90 });
            m_rectVec.at(7).setFillColor(sf::Color::Magenta);
            m_rectVec.at(7).setOutlineThickness(4u);
        }



        if (m_rectVec.at(9).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;

                m_raceDecider = Race::No;
                std::cout << "Race No " << std::endl;
            }
            m_rectVec.at(9).setSize(sf::Vector2f{ 320,90 });
            m_rectVec.at(9).setFillColor(sf::Color::Yellow);
            m_rectVec.at(9).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(9).setSize(sf::Vector2f{ 285,90 });
            m_rectVec.at(9).setFillColor(sf::Color::Magenta);
            m_rectVec.at(9).setOutlineThickness(4u);
        }


        if (m_rectVec.at(10).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;

                m_debugDecider = debug::On;
                std::cout << "debugon " << std::endl;
            }
            m_rectVec.at(10).setSize(sf::Vector2f{ 320,90 });
            m_rectVec.at(10).setFillColor(sf::Color::Yellow);
            m_rectVec.at(10).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(10).setSize(sf::Vector2f{ 285,90 });
            m_rectVec.at(10).setFillColor(sf::Color::Blue);
            m_rectVec.at(10).setOutlineThickness(4u);
        }

        if (m_rectVec.at(11).getGlobalBounds().contains(m_MousePos))
        {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                t_grid.m_endPosChosen = false;
                t_grid.m_startPosChosen = false;
                t_gridTwo.m_startPosChosen = false;
                t_gridTwo.m_endPosChosen = false;

                m_debugDecider = debug::Off;
                std::cout << "debugoff " << std::endl;
            }
            m_rectVec.at(11).setSize(sf::Vector2f{ 320,90 });
            m_rectVec.at(11).setFillColor(sf::Color::Yellow);
            m_rectVec.at(11).setOutlineThickness(8u);
        }
        else {
            m_rectVec.at(11).setSize(sf::Vector2f{ 285,90 });
            m_rectVec.at(11).setFillColor(sf::Color::Blue);
            m_rectVec.at(11).setOutlineThickness(4u);
        }


  
        return m_gridSwitcher;

}

Race& Menu::getRaceStatus()
{
    return m_raceDecider;
}

debug& Menu::getdebugStatus()
{
    return m_debugDecider;
}

std::vector<sf::RectangleShape> Menu::getVec()
{
    return m_rectVec;
}

void Menu::render(sf::RenderWindow& t_window)
{
    
    for (int i = 0; i < 13; i++)
    {
        t_window.draw(m_rectVec.at(i));
      
    }

    for (int i = 0; i < 13; i++)
    {
       
        t_window.draw(m_text[i]);
    }
}

void Menu::update(sf::Time t_deltaTime)
{
}

#include "GameControl.h"


GameControl::GameControl()
	:m_window(sf::VideoMode(WIDTH,LENGTH), "Mouse and Cat")
{}

//GameControl* GameControl::m_instance = nullptr;
//int GameControl::m_level;

void GameControl::run()
{
    bool startOver = false;
   
    Manage::fillTexturVector();
    Manage::load();
    m_board.setController(this);
    mainMenu();
}

void GameControl::mainMenu()
{
    while (m_window.isOpen())
    {
        m_window.clear();
        Manage::cover(m_window, "backCatMouse");
        
        m_menu.drawMenu(m_window);
        m_window.display();
        
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                m_window.close();
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });    //set location

                if (m_menu.isClickMenu(location) == "help")
                {
                    helpScreen();
                }
                else if (m_menu.isClickMenu(location) == "exit")
                {
                    exitGame();
                }
                else if (m_menu.isClickMenu(location) == "newGame")
                {
                    startGame();
                }

                break;
            }
          
            default:
                break;

            }

        }
       
    }
}

void GameControl::startGame()
{
    auto boardFile = std::ifstream("Board.txt");
    m_board.loadFromFile(boardFile);

    while (m_board.getLevel() < NUMOFLEVELS || (m_mouse && m_mouse->getLife() > 0))
    {
        m_board.setLevel(m_board.getLevel()+1);
        m_cats.clear();
        m_board.clearBoard();
        m_board.getStills(boardFile);

        if (!levelRun())
        {
            break;
        }

    }
    m_mouse.reset();
    m_board.setLevel(0);
}


bool GameControl::levelRun()
{

    m_window.setFramerateLimit(60);
    sf::Clock clock;

    bool mouseMoved = false;
   
    while (m_window.isOpen())//timer


    {
        const auto deltaTime = clock.restart();

        drawGame();

        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                m_window.close();
                return false;
            }

            case sf::Event::KeyPressed:
            {
                mouseMoved = true;
                move(event.key.code, deltaTime);
                break;
            }
            default:
                break;

            }

        }

        catsTurn(mouseMoved, deltaTime);

        m_board.checkCollisions(m_mouse, m_cats);

        if (Board::getCheeseCount() == 0 || m_mouse->getLife() == 0)
        {
            return true;
        }
    }
    return true;
}


void GameControl::catsTurn(bool mouseMoved,const sf::Time& deltaTime)
{
    if (mouseMoved)
    {
        for (auto& cat : m_cats)
        {
            cat->setDirection(cat->catMovment(m_mouse->getPosition()));
           // cat->move(deltaTime);
            cat->move(deltaTime.asSeconds());
        }
    }
}


void GameControl::move(const sf::Keyboard::Key& key, const sf::Time &deltaTime)
{
    sf::Vector2f direction;

    switch (key)
    {
    case sf::Keyboard::Key::Space:
    {
        direction= sf::Vector2f(0, 0);
        break;
    }
    case sf::Keyboard::Key::Left:
    {
        direction = sf::Vector2f(-1, 0);
        break;
    }
    case sf::Keyboard::Key::Down:
    {
        direction = sf::Vector2f(0, 1);
        break;
    }
    case sf::Keyboard::Key::Up:
    {
        direction = sf::Vector2f(0, -1);
        break;
    }
    case sf::Keyboard::Key::Right:
    {
        direction = sf::Vector2f(1, 0);
        break;
    }
    }

    m_mouse->setDirection(direction);
  //  m_mouse->move(deltaTime);
    m_mouse-> move(deltaTime.asSeconds());
    //move (deltaTime.asSeconds()); 
       //uts float
}


void GameControl::helpScreen()
{
    std::cout << "helpButton\n";

    sf::RenderWindow helpWindow(sf::VideoMode(1063, 597), "Help Screen");
    helpWindow.setFramerateLimit(60);

    while (helpWindow.isOpen())
    {
        Manage::cover(helpWindow, "HELP");
        helpWindow.display();

        const auto deltaTime = sf::seconds(1.0f / 60.0f);

        sf::Event event;
        while (helpWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                helpWindow.close();
                break;
            }
        }
    }
}

void GameControl::exitGame()
{
    std::cout << "exitButton\n";
    m_window.close();
}

//void GameControl::newGame()
//{
//    std::cout << "newGameButton\n";
//}

void GameControl::drawGame()
{
    m_window.clear();
    Manage::cover(m_window, "garssBack");
    m_board.draw(m_window);
    m_data.printData(m_window);
    m_board.printBoardData(m_window);
    m_mouse->printMouseData(m_window);
    m_mouse->draw(m_window);
    drawCats();
    m_board.drawPresents(m_window);
    m_window.display();

}

void GameControl::removeCat()
{
    
    if (Cat::isCatDead())
    {
        m_cats.pop_back();
        Cat::setDead();
    }
}

//void GameControl::freezeCat()
//{
//    for (auto& cat : m_cats)
//    {
//        cat->setDirection({0,0});
//        cat->move(deltaTime);
//    }
//}


void GameControl::addCat(const sf::Vector2f& tileSize, const sf::Vector2f& position)
{
    m_cats.push_back(std::make_unique<Cat>(tileSize, position, Manage::getTexture(O_CAT)));
}

void GameControl::saveMouse(const sf::Vector2f& tileSize,const sf::Vector2f& position)
{
    if (!m_mouse)
    {
        m_mouse = std::make_unique<Mouse>(tileSize, position, Manage::getTexture(O_MOUSE));
    }
    else
    {
        m_mouse->setPosition(position);
        m_mouse->setSize(tileSize);
    }
}

void GameControl::drawCats()
{
    for (auto& cat : m_cats)
        cat->draw(m_window);
}

void GameControl::resetMovingPos()
{
    if (m_mouse->isMouseEaten())
    {
        m_mouse->setPosition(m_mouse->getInitPos());

        for (auto& cat : m_cats)
        {
            cat->setPosition(cat->getInitPos());
        }
        m_mouse->mouseGotEaten(false);

    }
}
#include "GameControl.h"


GameControl::GameControl()
	:m_window(sf::VideoMode(WIDTH,LENGTH), "Mouse and Cat")
{}


void GameControl::run()
{
    Manage::getInstance()->getInstance()->playMusic();
    Manage::getInstance()->playMusic(); //??
    bool startOver = false;
   
    Manage::getInstance()->fillTexturVector();
    Manage::getInstance()->fillSoundVector();
    Manage::getInstance()->load();
    m_board.setController(this);
    mainMenu();
}

void GameControl::mainMenu()
{
    bool endGame = false;
    while (m_window.isOpen())
    {
        m_window.clear();
        Manage::getInstance()->cover(m_window, "backCatMouse");
        sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
        m_menu.drawMenu(m_window, mousePosition);
       // m_menu.drawMenu(m_window);
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
                    endGame = true;
                }
                else if (m_menu.isClickMenu(location) == "Music")
                {
                    if (Manage::getInstance()->getMusic().getStatus() == Manage::getInstance()->getMusic().Playing)
                        Manage::getInstance()->stopMusic();
                    else
                        Manage::getInstance()->startMusic();
                }

                break;
            }
          
            default:
                break;

            }
            if (endGame)
            {
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
        if (m_board.getLevel()>= NUMOFLEVELS || (m_mouse && m_mouse->getLife() == 0))
        {
            break;
        }

        m_board.setLevel(m_board.getLevel()+1);
        m_cats.clear();
        m_board.clearBoard();
        m_data.restartTime();
        
        m_board.getStills(boardFile);

        if (levelRun(boardFile)==0)
        {
            break;
        }
        else if (levelRun(boardFile) == 2)
        {
            levelRun(boardFile);
        }
    }
    
    m_mouse.reset();
    m_board.setLevel(0);
}


int GameControl::levelRun(std::ifstream& boardFile)
{
    std::cout << "in start of level run\n";

    if (m_data.timeOut())
    {
        std::cout << "time out\n";

    }
    m_window.setFramerateLimit(60);
    sf::Clock clock;

    bool mouseMoved = false;

    while (m_window.isOpen())
        //timer
    {
        const auto deltaTime = clock.restart();

        m_data.updateTime(m_board.getInitLevelTime());
        drawGame();

        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                m_window.close();
                return 0;
            }

            case sf::Event::KeyPressed:
            {
                mouseMoved = true;
                setDirection(event.key.code);
                break;
            }
            case sf::Event::KeyReleased:
                setDirection(sf::Keyboard::Space);
                break;

            default:
                break;
            }
           
        }

        catsTurn(mouseMoved, deltaTime);

        m_mouse->move(deltaTime.asSeconds());       
        m_board.checkCollisions(m_mouse, m_cats);
        m_mouse->setScale();

        if (Board::getCheeseCount() == 0 || m_mouse->getLife() == 0)
        {
            return 1;
        }

        if (m_data.timeOut())
        {
            sf::Sound* sound = Manage::getInstance()->getSound(O_TIMEOUT);
            m_cats.clear();
            m_board.setLevel(m_board.getLevel());
            m_board.clearBoard();
            m_data.restartTime();
            m_data.setTimeOut();
            m_board.startOver(true);
            m_board.getStills(boardFile);
            m_board.startOver(false);
            m_mouse->addLife(-1);
            return 2;
        }
    }
    return 1;
}


void GameControl::catsTurn(bool mouseMoved,const sf::Time& deltaTime)
{
    if (mouseMoved)
    {
        for (auto& cat : m_cats)
        {
            cat->setDirection(cat->catMovment(m_mouse->getPosition()));
            cat->move(deltaTime.asSeconds());
            cat->setScale();

        }
    }
}


void GameControl::setDirection(const sf::Keyboard::Key& key)
{
    sf::Vector2f direction;

    switch (key)
    {
    case sf::Keyboard::Key::Left:
    {
        direction = LEFT;
        break;
    }
    case sf::Keyboard::Key::Down:
    {
        direction = DOWN;
        break;
    }
    case sf::Keyboard::Key::Up:
    {
        direction = UP;
        break;
    }
    case sf::Keyboard::Key::Right:
    {
        direction = RIGHT;
        break;
    }
    case sf::Keyboard::Space:
        direction = STAY;
        break;
    }
    //m_mouse->setScale();
    //m_mouse-> move(deltaTime.asSeconds());
    m_mouse->setDirection(direction);
}


void GameControl::helpScreen()
{

    sf::RenderWindow helpWindow(sf::VideoMode(1063, 597), "Help Screen");
    helpWindow.setFramerateLimit(60);

    while (helpWindow.isOpen())
    {
        Manage::getInstance()->cover(helpWindow, "HELP");
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


void GameControl::drawGame()
{
    m_window.clear();
    Manage::getInstance()->cover(m_window, "garssBack");
    m_board.draw(m_window);
    m_data.printData(m_window);
    m_board.printBoardData(m_window);
    m_mouse->printMouseData(m_window);
    m_data.draw(m_window);
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

void GameControl::addCat(const sf::Vector2f& tileSize, const sf::Vector2f& position)
{
    m_cats.push_back(std::make_unique<Cat>(tileSize, position, Manage::getInstance()->getTexture(O_CAT)));
}

void GameControl::saveMouse(const sf::Vector2f& tileSize,const sf::Vector2f& position)
{
    if (!m_mouse)
    {
        m_mouse = std::make_unique<Mouse>(tileSize, position, Manage::getInstance()->getTexture(O_MOUSE));
    }
    else
    {
        m_mouse->setPosition(position);
        m_mouse->setSize(tileSize);
        m_mouse->setInitPos(position);
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


#include "GameControl.h"


GameControl::GameControl()
	:m_window(sf::VideoMode(WIDTH,LENGTH), "Mouse and Cat")
{}


void GameControl::run()
{
    Manage::getInstance()->playMusic();    
    Manage::getInstance()->fillTexturVector();
    Manage::getInstance()->fillSoundBufVector();
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
            if (endGame)   //check if window already closed
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

    while (shouldContinueGame())  //game loop
    {
        if (shouldEndGame())  //the game ended
        {
            break;
        }

        setupNextLevel(boardFile);   //clear all

        if (levelRun(boardFile) == 0)  //level end because window closed
        {
            break;
        }
        else if (levelRun(boardFile) == 2)  //level end because time out
        {
            levelRun(boardFile);
        }
    }

    handleEndGame();
}

bool GameControl::shouldContinueGame()
{
    return m_board.getLevel() < NUMOFLEVELS || (m_mouse && m_mouse->getLife() > 0);
}

bool GameControl::shouldEndGame()
{
    return m_board.getLevel() >= NUMOFLEVELS || (m_mouse && m_mouse->getLife() == 0);
}

void GameControl::setupNextLevel(std::ifstream& boardFile)
{
    m_board.setLevel(m_board.getLevel() + 1);
    m_cats.clear();
    m_board.clearBoard();
    m_data.restartTime();
    m_board.getStills(boardFile);
}

void GameControl::handleEndGame()
{
    if (m_mouse->getLife() == 0 )
    {
        displayEndScreen(O_OVER);  //if game ended because the user lost
    }
    else if (m_board.getLevel() >= NUMOFLEVELS&& m_mouse->getLife() > 0)
    {
        displayEndScreen(O_WIN);  //if game ended because the user won
    }

    m_mouse.reset();
    m_board.setLevel(0);
}

void GameControl::displayEndScreen(int textureKey)
{
    sf::Clock timer;
    sf::Time elapsedTime = sf::Time::Zero;

    while (elapsedTime < sf::seconds(TIME))   //display end screen for 5 seconds
    {
        m_window.clear();
        elapsedTime += timer.restart();
        sf::Sprite screen;
        screen.setTexture(*Manage::getInstance()->getTexture(textureKey));
        m_window.draw(screen);
        m_window.display();
    } 
}


int GameControl::levelRun(std::ifstream& boardFile)
{
    m_window.setFramerateLimit(FRAME_LIMIT);
    sf::Clock clock;

    bool mouseMoved = false;   //the mouse didnt start moving

    while (m_window.isOpen())
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
                mouseMoved = true;   //the mouse start moving
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

        catsTurn(mouseMoved, deltaTime);   //move cat

        m_mouse->move(deltaTime.asSeconds());       
        m_board.checkCollisions(m_mouse, m_cats);  
        m_mouse->setScale();

        if (Board::getCheeseCount() == 0 || m_mouse->getLife() == 0)  //or passed a level or lost
        {
            return 1;
        }

        if (m_data.timeOut())  //lost because time out
        {
            sf::Sound* sound = Manage::getInstance()->getSound(O_TIMEOUT);
            resetBoardAfterTimeOut(boardFile);

            return 2;
        }
    }
    return 1;
}

void GameControl::resetBoardAfterTimeOut(std::ifstream& boardFile)
{
    m_cats.clear();
    m_board.setLevel(m_board.getLevel());  //dont change level
    m_board.clearBoard();
    m_data.restartTime();
    m_data.setTimeOut();
    m_board.startOver(true); //need to read the same level
    m_board.getStills(boardFile);
    m_board.startOver(false); // reset to true to cintionue read othe levels
    m_mouse->addLife(-1);  //remove life
}


void GameControl::catsTurn(bool mouseMoved,const sf::Time& deltaTime)
{
    if (mouseMoved)  //only if the mouse allready moved
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
 
    m_mouse->setDirection(direction);
}


void GameControl::helpScreen()
{
    sf::RenderWindow helpWindow(sf::VideoMode(HELP_WIDTH, HELP_HEIGHT), "Help Screen");
    helpWindow.setFramerateLimit(FRAME_LIMIT);

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
    m_board.drawPresents(m_window);
    drawCats();
    m_window.display();
}

void GameControl::removeCat()   //remove one cat from the vector
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
    if (!m_mouse)  //if mouse didnt created yet
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

void GameControl::resetMovingPos()  //if mouse bean eaten, reset to init positions
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


#include "GameControl.h"


GameControl::GameControl()
	:m_window(sf::VideoMode(WIDTH,LENGTH), "Mouse and Cat")
{}

GameControl* GameControl::m_instance = nullptr;

void GameControl::run()
{
    Manage::fillTexturVector();

	//while (m_board.getLevel() < NUMOFLEVELS)
	//{
		m_board.loadFromFile();

		//m_board.draw(m_window);

		//m_menu.drawMenu(m_window);


		levelRun();
	//}
}


void GameControl::levelRun()
{
	makeWindow();
}


void GameControl::makeWindow()
{
    m_window.setFramerateLimit(60);
    sf::Clock clock;
    bool gameStarted = false;

    while (m_window.isOpen())
    {
        const auto deltaTime = clock.restart();

       // m_window.clear();
        cover();
       // m_board.draw(m_window);
        //m_mouse->draw(m_window);
        //drawCats();
       // m_menu.drawMenu(m_window);

      //  m_window.display();
        if (!gameStarted)
        {
            m_menu.drawMenu(m_window);
            m_window.display(); 
        }
        else
        {
            startGame();

           // cover();

        }

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

                if (m_menu.isClickMenu(location)=="help")
                {
                    helpScreen();
                }
                else if (m_menu.isClickMenu(location) == "exit")
                {
                    exitGame();
                }
                else if (m_menu.isClickMenu(location) == "newGame")
                {
                    newGame();
                }
                else if (m_menu.isClickMenu(location) == "start")
                {
                    gameStarted = true;

                }

                break;
            }
            case sf::Event::KeyPressed:
            {               
                move(event.key.code, deltaTime);
                break;
            }
            default:
                break;

            }
        }
        //the cats play (for)
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
    m_mouse->move(deltaTime);
       
}


GameControl* GameControl::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new GameControl();
    }
    return m_instance;
    
}

void GameControl::helpScreen()
{
    std::cout << "helpButton\n";

    sf::RenderWindow helpWindow(sf::VideoMode(1063, 597), "Help Screen");
    helpWindow.setFramerateLimit(60);

    while (helpWindow.isOpen())
    {
        //m_window.clear();
        helpcover( helpWindow);
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
}

void GameControl::newGame()
{
    std::cout << "newGameButton\n";
}

void GameControl::startGame()
{
    std::cout << "startGameButton\n";
    m_window.clear();
    m_board.draw(m_window);
    m_mouse->draw(m_window);
    drawCats();
    m_window.display();

}

void GameControl::cover()
{
    sf::Texture back;
    sf::Sprite background;
    back.loadFromFile("back.png");
    background.setTexture(back);
    //m_window.clear();
    m_window.draw(background);
    //m_window.display();
}

void GameControl::helpcover( sf::RenderWindow &helpWindow)
{
    sf::Texture back;
    sf::Sprite background;
    back.loadFromFile("HELP.png");
    background.setTexture(back);
    //m_window.clear();
    helpWindow.draw(background);
  //  helpWindow.display();
}

void GameControl::addCat(const sf::Vector2f& position)
{
    m_cats.push_back(std::make_unique<Cat>(position, Manage::getTexture(O_CAT)));
}

void GameControl::saveMouse(const sf::Vector2f& position)
{
    m_mouse = std::make_unique<Mouse>(position, Manage::getTexture(O_MOUSE));
}

void GameControl::drawCats()
{
    for (auto& cat : m_cats)
        cat->draw(m_window);
}

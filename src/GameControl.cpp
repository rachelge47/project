#include "GameControl.h"


GameControl::GameControl()
	:m_window(sf::VideoMode(WIDTH,LENGTH), "Mouse and Cat")//,
   // m_mouse (std::make_unique<Mouse>(sf::Vector2f({0, 0}), Manage::getTexture()[O_MOUSE]))
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

    while (m_window.isOpen())
    {
        m_window.clear();
        cover();
        m_board.draw(m_window);
        m_mouse->draw(m_window);
        drawCats();
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
               
            }

            }
        }
    }
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
}

void GameControl::exitGame()
{
    std::cout << "exitButton\n";
}

void GameControl::newGame()
{
    std::cout << "newGameButton\n";
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

void GameControl::addCat(const sf::Vector2f& position)
{
    m_cats.push_back(std::make_unique<Cat>(position, Manage::getTexture()[O_CAT]));
}

void GameControl::saveMouse(const sf::Vector2f& position)
{
    m_mouse = std::make_unique<Mouse>(position, Manage::getTexture()[O_MOUSE]);
}

void GameControl::drawCats()
{
    for (auto& cat : m_cats)
        cat->draw(m_window);
}

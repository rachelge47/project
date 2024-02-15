#include "GameControl.h"


GameControl::GameControl()
	:m_window(sf::VideoMode(WIDTH,LENGTH), "Mouse and Cat")
{}


void GameControl::run()
{
	//while (m_board.getLevel() < NUMOFLEVELS)
	//{
		//m_board.loadFromFile();

		m_board.draw(m_window);

		m_menu.drawMenu(m_window);

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

        m_board.draw(m_window);
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

#include "GameControl.h"

void GameControl::run()
{

	while (m_board.getLevel() < NUMOFLEVELS)
	{
		m_board.loadFromFile();

		m_board.draw(m_window);

		m_menu.draw(m_window);

		levelRun();
	}


}



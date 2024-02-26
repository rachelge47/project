#include "Data.h"
#include "GameControl.h"

void Data::printData(sf::RenderWindow& window)
{
	//GameControl::getLevel();

	Manage::load1();

	m_info.setTexture(Manage::infoTexture());

	m_info.setSize({ 350, 550 });
	m_info.setPosition({ 1330, 5 });

	window.draw(m_info);


}



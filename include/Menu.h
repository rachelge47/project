#pragma once
#include "Button.h"
#include <vector>

class Menu {
public:

	void drawMenu( sf::RenderWindow& window)const ;

private:
	std::vector <Button> m_menu;

};

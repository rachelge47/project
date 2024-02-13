#pragma once
#include "Button.h"
#include <vector>

class Menu {
public:

	void draw( sf::RenderWindow& window)const ;

private:
	std::vector <Button> m_menu;

};

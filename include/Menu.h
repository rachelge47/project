#pragma once
#include "Button.h"
#include <vector>

class Menu {
public:

	Menu();

	void drawMenu( sf::RenderWindow& window)const ;
	virtual std::string isClickMenu(const sf::Vector2f& location) const;
	virtual ~Menu()=default;

private:

	std::vector<std::unique_ptr<Button>> m_menu;
	sf::Font m_font;

	sf::Text makeButton(const std::string& str, const sf::Font& font);


};


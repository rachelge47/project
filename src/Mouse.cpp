#include "Mouse.h"

Mouse::Mouse(const sf::Vector2f& tileSize, const sf::Vector2f& position, const sf::Texture* texture)
	: MovingObject(tileSize, position, texture, 150.f), m_score(0), m_life(3)
{}

void Mouse::printMouseData(sf::RenderWindow& window)
{
	sf::Text text;
	float down = DOWN_M;

	std::string str = std::to_string(m_score);
	text = make(str, Manage::getInstance()->getFont(), down);

	window.draw(text);

	str = std::to_string(m_life);
	down += M_SPACE;
	text = make(str, Manage::getInstance()->getFont(), down);
	window.draw(text);

}



sf::Text Mouse::make(const std::string& str, const sf::Font* font, float down)
{
	sf::Text text(str, *font);
	text.setPosition({ POS_X, down });
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(TEXT_SIZE);

	return text;
}
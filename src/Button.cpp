#include "Button.h"
#include "GameControl.h"

Button::Button (const sf::Text& text, const sf::Vector2f &position)
	:m_text(text), m_position(position)
{
	m_button.setSize({ 300,350 });
	Manage::load();
	m_button.setTexture(Manage::buttonTexture());
}

void Button::drawButton(sf::RenderWindow& window) 
{
	setPosition(m_position);
	window.draw(m_button);
	window.draw(m_text);
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_button.setPosition(position);
	m_text.setPosition(m_button.getPosition() + sf::Vector2f(70, 20));
}

bool Button::isClick(const sf::Vector2f& location) const
{
	return m_button.getGlobalBounds().contains(location);
}

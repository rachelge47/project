#include "Button.h"
#include "GameControl.h"

Button::Button (const sf::Text& text, const sf::Vector2f &position)
	:m_text(text), m_position(position)
{
	m_button.setSize({ 150,50 });
	m_button.setFillColor(sf::Color(217, 173, 242));  //set color of button
	m_button.setOutlineThickness(5);
	m_button.setOutlineColor(sf::Color::Red);

}


void Button::drawButton(sf::RenderWindow& window) 
{
	setPosition(m_position);
	window.draw(m_button);

	//float x = (m_button.getSize().x - m_text.getLocalBounds().width) / 2;
	//float y = (m_button.getSize().y - m_text.getLocalBounds().height) / 2;
	//m_text.setPosition(x, y);
	//m_text.move(30, 0);
	window.draw(m_text);
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_button.setPosition(position);
	m_text.setPosition(m_button.getPosition() + sf::Vector2f(5, 5));
}

bool Button::isClick(const sf::Vector2f& location) const
{
	return m_button.getGlobalBounds().contains(location);
}


void HelpButton::action()
{
	GameControl::getInstance()->helpScreen();
}

void ExitButton::action()
{
	GameControl::getInstance()->exitGame();
}

void NewGameButton::action()
{
	GameControl::getInstance()->newGame();
}


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameControl;

class Button {
public:

	Button(const sf::Text &text, const sf::Vector2f& position);
	virtual void action() = 0;
	void drawButton( sf::RenderWindow& window) ;
	virtual int getSize() { return m_button.getSize().x; }
	virtual void setPosition(const sf::Vector2f& position); ///?
	bool isClick(const sf::Vector2f& location) const;
	//isClick();

private:

	sf::RectangleShape m_button;
	sf::Vector2f m_position;
	sf::Text m_text;
};

class HelpButton : public Button
{
public:
	HelpButton(const sf::Text& text, const sf::Vector2f& position) :Button(text,position) {}
	virtual void action () override;
};

class ExitButton : public Button
{
public:
	ExitButton(const sf::Text& text, const sf::Vector2f& position) :Button(text,position) {}
	virtual void action() override;
};

class NewGameButton : public Button
{
public:
	NewGameButton(const sf::Text& text, const sf::Vector2f& position) :Button(text,position) {}
	virtual void action() override;
};
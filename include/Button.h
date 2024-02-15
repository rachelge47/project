#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameControl.h"

class Button {
public:

	Button(const sf::Text &text);
	virtual void action() = 0;
	void drawButton( sf::RenderWindow& window) const;
	void setPosition(const sf::Vector2f& position); ///?

private:

	//void getFont();
	sf::RectangleShape m_button;
	sf::Text m_text;
	//std::vector <sf::Text> m_titles;
	//sf::Font m_font;
};

class HelpButton : public Button
{
public:
	HelpButton(const sf::Text& text) :Button(text) {}
	virtual void action () override;
};

class ExitButton : public Button
{
public:
	ExitButton(const sf::Text& text) :Button(text) {}
	virtual void action() override;
};

class NewGameButton : public Button
{
public:
	NewGameButton(const sf::Text& text) :Button(text) {}
	virtual void action() override;
};
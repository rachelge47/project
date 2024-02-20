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
	virtual bool isClick(const sf::Vector2f& location) const;
	sf::Text getText() { return m_text; }
	virtual~Button()= default;

private:

	sf::RectangleShape m_button;
	sf::Vector2f m_position;
	sf::Text m_text;
};

class HelpButton : public Button
{
public:
	using Button::Button;
	//HelpButton(const sf::Text& text, const sf::Vector2f& position) :Button(text,position) {}
	virtual void action () override;
};

class ExitButton : public Button
{
public:
	using Button::Button;
	//ExitButton(const sf::Text& text, const sf::Vector2f& position) :Button(text,position) {}
	virtual void action() override;
};

class NewGameButton : public Button
{
public:
	using Button::Button;
	//NewGameButton(const sf::Text& text, const sf::Vector2f& position) :Button(text,position) {}
	virtual void action() override;
};

class StartButton : public Button
{
public:
	using Button::Button;
	virtual void action() override;
};

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Manage.h"

class GameControl; 

class Button {

public:
    Button(const sf::Text& text, const sf::Vector2f& position);
    void drawButton(sf::RenderWindow& window, const sf::Vector2f& mousePosition);
    float getSize() { return m_button.getSize().x; }
    void setPosition(const sf::Vector2f& position);
    bool isClick(const sf::Vector2f& location) const;
    virtual ~Button() = default;
    sf::Text getText() { return m_text; }

private:
    //----functions------
    void updateHover(const sf::Vector2f& mousePosition);

    //----members--------
    sf::Vector2f m_position;     
    sf::Text m_text;            
    bool m_hovered;            

protected:
    sf::RectangleShape m_button;
};

// Derived class for HelpButton
class HelpButton : public Button {
public:
    using Button::Button; 
};

// Derived class for ExitButton
class ExitButton : public Button {
public:
    using Button::Button; 
};

// Derived class for NewGameButton
class NewGameButton : public Button {
public:
    using Button::Button; 
};

// Derived class for StartButton
class StartButton : public Button {
public:
	using Button::Button;
};

class MusicButton : public Button
{
public:
	using Button::Button;
 
};

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameControl; 

class Button {

public:
    Button(const sf::Text& text, const sf::Vector2f& position);
    void drawButton(sf::RenderWindow& window, const sf::Vector2f& mousePosition);
    virtual int getSize() { return m_button.getSize().x; }
    virtual void setPosition(const sf::Vector2f& position);
    virtual bool isClick(const sf::Vector2f& location) const;
    virtual ~Button() = default;
    sf::Text getText() { return m_text; }

private:
    sf::RectangleShape m_button; 
    sf::Vector2f m_position;     
    sf::Text m_text;            
    bool m_hovered;            

    void updateHover(const sf::Vector2f& mousePosition);
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

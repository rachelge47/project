
#include "Button.h"
#include "GameControl.h"

Button::Button(const sf::Text& text, const sf::Vector2f& position)
    : m_text(text), m_position(position), m_hovered(false)
{
    m_button.setSize(BUTTON_SIZE);
    m_button.setScale(SCALE_BUTTON);
    Manage::getInstance()->load();
    m_button.setTexture(Manage::getInstance()->buttonTexture());
}

void Button::drawButton(sf::RenderWindow& window, const sf::Vector2f& mousePosition)
{
    updateHover(mousePosition);
    setPosition(m_position);
    window.draw(m_button);
    window.draw(m_text);
}

void Button::setPosition(const sf::Vector2f& position)
{
    m_position = position; 
    m_button.setPosition(m_position);

    // Calculate the text position to center it within the button
    sf::FloatRect textBounds = m_text.getLocalBounds();
    float offsetX = (m_button.getSize().x - textBounds.width) / 2.0f;
    float offsetY = (m_button.getSize().y - textBounds.height) / 11.0f;

    m_text.setPosition(m_position + sf::Vector2f(offsetX, offsetY));
}

void Button::updateHover(const sf::Vector2f& mousePosition)
{
    m_hovered = m_button.getGlobalBounds().contains(mousePosition);

    // Adjust the size when the button is hovered
    m_button.setSize(m_hovered ? sf::Vector2f(HOVERD) : sf::Vector2f(NOT_HOVERD));
}

bool Button::isClick(const sf::Vector2f& location) const
{
    return m_button.getGlobalBounds().contains(location);
}

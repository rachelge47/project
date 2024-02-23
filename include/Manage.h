#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

const int WIDTH = 1700;
const int LENGTH = 900;

const sf::Vector2f UP = { 0 , -1 };

const sf::Vector2f DOWN = { 0 , 1 };

const sf::Vector2f RIGHT = { 1 , 0 };

const sf::Vector2f LEFT = { -1 , 0 };


enum ObjectType {
    O_WALL,
    O_DOOR,
    O_KEY,
    O_PRESENT,
    O_CHEESE,
    O_MOUSE,
    O_CAT
};

class Manage {
public:
    static void fillTexturVector();
    static void cover( sf::RenderWindow& window, const std::string& backName);
    static sf::Texture *getTexture(int index) { return &m_textures[index]; }
    static void load();
    static const std::string m_names[7];
private:
    static std::vector<sf::Texture> m_textures;
    static sf::Texture m_menuBack;
    static sf::Texture m_gameBack;
    static sf::Texture m_helpBack;

};
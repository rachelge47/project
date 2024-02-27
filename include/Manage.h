#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

const int WIDTH = 1700;
const int LENGTH = 900;

const sf::Vector2f UP = { 0 , -1 };

const sf::Vector2f DOWN = { 0 , 1 };

const sf::Vector2f RIGHT = { 1 , 0 };

const sf::Vector2f LEFT = { -1 , 0 };

const char MOUSE = '%';
const char CAT = '^';
const char KEY = 'F';
const char PRESENT = '$';
const char DOOR = 'D';
const char CHEESE = '*';
const char WALL = '#';
const char EMPTY = ' ';
const int NUMOFLEVELS = 3;


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
    static void load1();
    static sf::Texture* buttonTexture();
    static sf::Font* getFont();
    static sf::Texture* infoTexture();
    static const std::string m_names[7];
private:
    static std::vector<sf::Texture> m_textures;
    static sf::Texture m_menuBack;
    static sf::Texture m_gameBack;
    static sf::Texture m_helpBack;
    static sf::Texture m_buttonBack;
    static sf::Texture m_infoBack;
    static sf::Font m_font;
};
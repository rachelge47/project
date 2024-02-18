#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

const int WIDTH = 1700;
const int LENGTH = 900;

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
    static std::vector<sf::Texture> getTexture() { return m_textures; }
    static const std::string m_names[7];
private:
    static std::vector<sf::Texture> m_textures;

};
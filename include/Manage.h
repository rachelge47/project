#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int WIDTH = 1700;
const int LENGTH = 900;

const sf::Vector2f UP = { 0 , -1 };

const sf::Vector2f DOWN = { 0 , 1 };

const sf::Vector2f RIGHT = { 1 , 0 };

const sf::Vector2f LEFT = { -1 , 0 };
const sf::Vector2f STAY = { 0 , 0 };

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

enum soundType {
    O_CATMOUSE,
    O_EATCHEESE,
    O_GAMEOVER,
    O_PASSLEVEL,
    O_LOST,
    O_OPENDOOR,
    O_GETPRESENT,
    O_WON,
    O_TIMEOUT
};



class Manage {
public:
   // Manage();
    static Manage* getInstance();
    void playMusic();
    void fillSoundVector();
    void fillTexturVector();
    void cover( sf::RenderWindow& window, const std::string& backName);
    sf::Texture *getTexture(int index) { return &m_textures[index]; }
    //static sf::Sound *getSound(int index) { return &m_sounds[index]; }
    sf::Sound* getSound(int index);
    sf::Music& getMusic() { return m_music; }
    void stopMusic() { m_music.pause(); }
    void startMusic() { m_music.play(); }
    sf::SoundBuffer* getSoundBuffer(int index);

    void load();
    void load1();
    sf::Texture* buttonTexture();
    sf::Font* getFont();
    sf::Texture* infoTexture();
   
    ~Manage() { delete m_instance; }


private:

    Manage();
    std::vector<sf::Texture> m_textures;
    //static std::vector<sf::Sound> m_sounds;
    sf::Sound m_sound;
    std::vector<sf::SoundBuffer> m_soundBuffers;

    std::string m_names[7];
    std::string m_soundNames[9];

    sf::Texture m_menuBack;
    sf::Texture m_gameBack;
    sf::Texture m_helpBack;
    sf::Texture m_buttonBack;
    sf::Texture m_infoBack;
    sf::Texture m_muteButton;
    sf::Font m_font;
    sf::Music m_music;

    static Manage* m_instance;
    
};
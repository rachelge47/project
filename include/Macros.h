#pragma once
#include <SFML/Graphics.hpp>


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
    O_CAT,
    O_OVER,
    O_WIN
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

//game control
const int WINDOW_WIDTH = 1700;
const int WINDOW_HEIGHT = 900;
const int FRAME_LIMIT = 60;
const int HELP_WIDTH = 1063;
const int HELP_HEIGHT = 597;

//board:
const int BOARD_WIDTH = 1300;
const int BOARD_HEIGHT = 800;
const sf::Vector2f CUR_POS = { 70.f,70.f };
const float TIME = 5.0f;
const sf::Vector2f START_POINT = { 20.f,20.f }; 
const float DOWN_B = 140.f; 
const float POS_X = 1550.f; //line 342 int int mouse line 29
const int TEXT_SIZE = 80;

//button

const sf::Vector2f BUTTON_SIZE = { 200.f, 250.f };
const sf::Vector2f SCALE_BUTTON = { 1.f, 0.4f };
const sf::Vector2f HOVERD = { 320.f, 370.f }; 
const sf::Vector2f NOT_HOVERD = { 300.f, 350.f };

//data

const sf::Vector2f INFO_SIZE = { 350.f, 550.f }; 
const sf::Vector2f INFO_POS = { 1330.f, 5.f }; 
//const sf::Vector2f TEXT_SIZE = { 1330.f, 5.f }; //line 55,68
const sf::Vector2f TIME_TEXT_POS = { 1350.f, 600.f }; 
//const sf::Vector2f TEXT_POS = { 1550.f, 20.f }; //line 66

//mange

const int NUM_OF_NAMES = 9;
const int VOLUME = 30;
const int M_TEXT_SIZE = 65;


//menu

const sf::Vector2f INIT_POS = { 700.f, 100.f }; 
const sf::Vector2f MUTE_POS = { 20.f, 40.f }; 
const int R_SPACE = 20;

//Mouse

const float DOWN_M = 220.f;
const int M_SPACE = 90;

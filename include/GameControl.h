#pragma once
#include "Board.h"
#include "Menu.h"
#include "Cat.h"
#include "Mouse.h"


const int NUMOFLEVELS = 3;
//const int WIDTH = 1300;
//const int LENGTH = 800;

class GameControl {

public:

	void run();
	void levelRun();
	void makeWindow();
	static GameControl* getInstance();
	void helpScreen();
	void exitGame();
	void newGame();
	void cover();
	void saveMouse(const sf::Vector2f &position);
	void addCat(const sf::Vector2f& position);
	~GameControl() { delete m_instance; }

private:
	GameControl(); // single tone
	void drawCats();

	static GameControl* m_instance; //single tone
	Board m_board;
	Menu m_menu;
	std::unique_ptr<Mouse> m_mouse;// (std::make_unique<Mouse>(sf::Vector2f({ 0, 0 }), Manage::getTexture()[O_MOUSE]));
	sf::RenderWindow m_window;
	std::vector <std::unique_ptr <Cat>> m_cats;

};
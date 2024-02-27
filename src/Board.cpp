#include "Board.h"
#include "GameControl.h"
#include "collisions.h"

const int BOARD_WIDTH = 1300;
const int BOARD_HEIGHT = 800;


Board::Board()
	:m_level(0), m_firstPresent(false)
{}

int Board::m_initCheeseCount;
int Board::m_cheeseCount;// m_initCheeseCount;
int Board::m_keyCount;
int Board::m_presentCount;
int Board::m_initKeyCount;



void Board::loadFromFile(std::ifstream& boardFile)
{	
	if (!boardFile.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	//getStills(boardFile);

	//boardFile.clear();  // Clear any error flags
}

void Board::clearBoard()
{
	m_stills.clear();
	m_presents.clear();
	m_firstPresent = false;
	m_cheeseCount = 0;
	m_initCheeseCount = 0;
	m_initKeyCount = 0;
	m_keyCount = 0;

}


void Board::getStills(std::ifstream& boardFile)
{
	std::string line;

	std::vector<std::string> fileContent;

	//contain the board to know num of rows and cols
	//for (auto line = std::string(); std::getline(boardFile, line) && !line.empty();)
	//{
	//	fileContent.push_back(line);
	//}

	

	while (std::getline(boardFile, line))
	{
		if (line.empty())
		{
			break;
		}

		fileContent.push_back(line);
	}
	int rows = fileContent.size();
	int cols= fileContent[0].size();
	
	//calculate the tiles size Depends on the size of window
	float tileWidth = (BOARD_WIDTH)/ cols;
	float tileHeight = (BOARD_HEIGHT) / rows;
	
	sf::Vector2f tileSize = { tileWidth,tileHeight };
	m_boardSize = { tileWidth * cols,tileHeight * rows };

	sf::Vector2f currentPosition(20, 20);

	for (int i = 0; i < fileContent.size(); i++)
	{
		for (int j = 0; j < fileContent[i].size(); j++)
		{
			currentPosition.x = 20 + (j * tileWidth);
			currentPosition.y = 20 + (i * tileHeight);
			
			switch (fileContent[i][j])
			{
			case WALL:
			{
				m_stills.push_back(std::make_unique<Wall>(tileSize,currentPosition, Manage::getTexture(O_WALL)));
				break;
			}
			case CHEESE:
			{
				m_initCheeseCount++;
				m_cheeseCount++;
				m_stills.push_back(std::make_unique<Cheese>(tileSize,currentPosition, Manage::getTexture(O_CHEESE)));
				break;
			}
			case KEY:
			{
				m_initKeyCount++;
				m_stills.push_back(std::make_unique<Key>(tileSize,currentPosition, Manage::getTexture(O_KEY)));
				break;
			}
			case PRESENT:
			{
				//m_presentCount++;
				fillPresents(tileSize, currentPosition);


				break;
			}
			case DOOR:
			{
				m_stills.push_back(std::make_unique<Door>(tileSize,currentPosition, Manage::getTexture(O_DOOR)));
				break;
			}

			case CAT:
			{
				sf::Vector2f tempSize;   //make cats size a bit smaller so can pass in narrow spaces
				tempSize.x = tileSize.x / 1.2;
				tempSize.y = tileSize.y / 1.2;

				m_controller->addCat(tempSize,currentPosition);
				break;
			}

			case MOUSE:
			{
				sf::Vector2f tempSize;     //make mouse size a bit smaller so can pass in narrow spaces
				tempSize.x= tileSize.x / 1.2;
				tempSize.y= tileSize.y / 1.2;

				m_controller->saveMouse(tempSize,currentPosition);
				break;
			}

			default:
				break;
			}
		}
	}	
}

void Board::checkCollisions(const std::unique_ptr<Mouse>& mouse, const std::vector <std::unique_ptr <Cat>>& cats)
{
	if (!inBounds(mouse->getGlobalBounds()))	//hendle mouse and board collision
		mouseWithBoard(*mouse, *this);


	for (size_t i = 0; i < cats.size(); i++)	//cats and borad bounds collisions
	{
		if (!inBounds(cats[i]->getGlobalBounds()))
			catWithBoard(*cats[i], *this);
	}		

	for (auto& obj : m_stills)   //handle mouse collision
	{
		if (mouse->getGlobalBounds().intersects(obj->getGlobalBounds()))
		{
			processCollision(*mouse, *obj);
		}
	}

	for (auto& cat : cats)   //handle cats collision
	{
		for (auto& obj : m_stills)
		{
			if (cat->getGlobalBounds().intersects(obj->getGlobalBounds()))
			{
				processCollision(*cat, *obj);
			}
		}
	}

	for (auto& cat : cats)
	{
		if (cat->getGlobalBounds().intersects(mouse->getGlobalBounds()))
		{
			processCollision(*cat, *mouse);
		}
	}

	for (auto& present : m_presents)   //handle present collision
	{
		if (mouse->getGlobalBounds().intersects(present->getGlobalBounds()))
		{
			processCollision(*mouse, *present);

			if (Cat::isFrozen())
			{
				m_freezeTimer.restart();
			}
		}
	}

	m_stills.erase( std::remove_if(m_stills.begin(), m_stills.end(),    //erase object that has been eaten
			[](const auto& obj) { return obj->beenEaten(); }),	m_stills.end());

	m_presents.erase(std::remove_if(m_presents.begin(), m_presents.end(),    //erase object that has been eaten
		[](const auto& present) { return present->beenEaten(); }), m_presents.end());

	m_controller->removeCat();

	m_controller->resetMovingPos();
	//m_controller->freezeCat();

	if (m_freezeTimer.getElapsedTime().asSeconds()>=5.0f)
	{
		Cat::needFreeze(false);
	}

}


void Board::fillPresents(const sf::Vector2f &tileSize, const sf::Vector2f &currentPosition)
{
	if (!m_firstPresent)
	{
		m_presents.push_back(std::make_unique<KillCatPresent>(tileSize, currentPosition, Manage::getTexture(O_PRESENT)));
		m_firstPresent = true;
	}
	else
	{
		switch (m_presents.size() % 3)
		{
		case 0:
		{
			m_presents.push_back(std::make_unique<MoreLifePresent>(tileSize, currentPosition, Manage::getTexture(O_PRESENT)));
			break;
		}
		case 1:
		{
			m_presents.push_back(std::make_unique<FreezePresent>(tileSize, currentPosition, Manage::getTexture(O_PRESENT)));
			break;
		}
		case 2:
		{
			m_presents.push_back(std::make_unique<IncreaseTimePresent>(tileSize, currentPosition, Manage::getTexture(O_PRESENT)));
			break;
		}

		default:
			break;

		}
	}
}



int Board::getLevel() const
{
	return m_level;
}

void Board::draw( sf::RenderWindow & window) const
{
	for (auto& object : m_stills)
		object->draw(window);
}

void Board::drawPresents(sf::RenderWindow& window) const
{
	for (auto& present : m_presents)
		present->draw(window);
}


//function to check tif the board is in bounds of window
//Manage::setObjSize(the size that will fits)

sf::FloatRect Board::getGlobalBounds() const
{
	//sf::Vector2f boardStartPoint = { m_position.x - float(0.5) * m_width,
								//	m_position.y - float(0.5) * m_height };

	return sf::FloatRect(1.f * 20, 1.f *20, BOARD_WIDTH, BOARD_HEIGHT);
}

bool Board::inBounds(sf::FloatRect rect) const
{
	auto bounds = this->getGlobalBounds();
	bool topLeft = bounds.contains(rect.left, rect.top);
	bool bottomLeft = bounds.contains(rect.left, rect.top + rect.height);
	bool topRight = bounds.contains(rect.left + rect.width, rect.top);
	bool bottomRight = bounds.contains(rect.left + rect.width, rect.top + rect.height);

	return (topLeft && topRight && bottomLeft && bottomRight);
}

void Board:: printBoardData(sf::RenderWindow& window)
{
	sf::Text text;
	int down = 140;

	std::string str= std::to_string(m_level);
	text = make(str, Manage::getFont(), down);
	
	window.draw(text);

	str = std::to_string(m_keyCount);
	down += 280;
	text= make(str, Manage::getFont(), down);
	window.draw(text);
}


sf::Text Board::make(const std::string& str, const sf::Font* font, int down)
{
	sf::Text text(str, *font);
	text.setPosition({ 1550, down*1.f });
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(80);

	return text;
}
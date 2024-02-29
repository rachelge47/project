#include "Board.h"
#include "GameControl.h"
#include "collisions.h"


Board::Board()
	:m_level(0), m_firstPresent(false)
{}

//initiat static members
int Board::m_initCheeseCount=0;
int Board::m_cheeseCount=0;
int Board::m_keyCount=0;
int Board::m_initKeyCount=0;


void Board::loadFromFile(std::ifstream& boardFile)
{	
	if (!boardFile.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		exit(EXIT_FAILURE);
	}
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

void Board::startOver(bool toDo)    //do it if time is up
{
	m_startOver = toDo;
}


void Board::getStills(std::ifstream& boardFile)
{
	std::vector<std::string> fileContent;

	if (m_startOver)
	{
		resetFileAndContent(boardFile, fileContent);
	}

	m_filePos = boardFile.tellg();   //save the position in the file
	std::getline(boardFile, m_initLevelTime);

	parseFileContent(boardFile, fileContent);

	calculateTileAndBoardSize(fileContent);

	sf::Vector2f currentPosition(CUR_POS);

	for (int i = 0; i < fileContent.size(); i++)
	{
		for (int j = 0; j < fileContent[i].size(); j++)
		{
			currentPosition.x = CUR_POS.x + (j * m_tileSize.x);
			currentPosition.y = CUR_POS.y + (i * m_tileSize.y);

			createBoardObject(fileContent[i][j], m_tileSize, currentPosition);
		}
	}
}

void Board::resetFileAndContent(std::ifstream& boardFile, std::vector<std::string>& fileContent)
{
	boardFile.clear();
	fileContent.clear();
	boardFile.seekg(m_filePos);   //reset the file pointer to the beginning of the level
}

void Board::parseFileContent(std::ifstream& boardFile, std::vector<std::string>& fileContent)
{
	std::string line;
	while (std::getline(boardFile, line) && !line.empty())
	{
		fileContent.push_back(line);
	}
}

void Board::calculateTileAndBoardSize(const std::vector<std::string>& fileContent)
{
	size_t rows = fileContent.size();
	size_t cols = fileContent[0].size();

	float tileWidth = (BOARD_WIDTH) / cols*1.f;  
	float tileHeight = (BOARD_HEIGHT) / rows*1.f;

	m_tileSize = { tileWidth, tileHeight };   //calculate the tile size to the board size and the rows and cols
	m_boardSize = { tileWidth * cols, tileHeight * rows };
}

//create vector of stills objects
void Board::createBoardObject(char symbol, const sf::Vector2f& tileSize, const sf::Vector2f& position)
{
	switch (symbol)
	{
	case WALL:
		m_stills.push_back(std::make_unique<Wall>(tileSize, position, Manage::getInstance().getTexture(O_WALL)));
		break;
	case CHEESE:
		m_initCheeseCount++;
		m_cheeseCount++;
		m_stills.push_back(std::make_unique<Cheese>(tileSize, position, Manage::getInstance().getTexture(O_CHEESE)));
		break;
	case KEY:
		m_initKeyCount++;
		m_stills.push_back(std::make_unique<Key>(tileSize, position, Manage::getInstance().getTexture(O_KEY)));
		break;
	case PRESENT:
		fillPresents(tileSize, position);
		break;
	case DOOR:
		m_stills.push_back(std::make_unique<Door>(tileSize, position, Manage::getInstance().getTexture(O_DOOR)));
		break;
	case CAT:
	{
		sf::Vector2f tempSize;   //make cats size a bit smaller so can pass in narrow spaces
		tempSize.x = tileSize.x / 1.4f;
		tempSize.y = tileSize.y / 1.4f;

		m_controller->addCat(tempSize, position);
		break;
	}
	case MOUSE:
	{
		sf::Vector2f tempSize;     //make mouse size a bit smaller so can pass in narrow spaces
		tempSize.x = tileSize.x / 1.4f;
		tempSize.y = tileSize.y / 1.4f;

		m_controller->saveMouse(tempSize, position);
		break;
	}
	default:
		break;
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

	for (auto& cat : cats)   //handle cats collision with stills
	{
		for (auto& obj : m_stills)
		{
			if (cat->getGlobalBounds().intersects(obj->getGlobalBounds()))
			{
				processCollision(*cat, *obj);
			}
		}
	}

	for (auto& cat : cats)     //handle cats collision with mouse
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

			if (Cat::isFrozen())   //if need to freeze cat, reset clock
			{
				m_freezeTimer.restart();
				m_controller->makeCatBlue(true);
			}
		}
	}

	m_stills.erase( std::remove_if(m_stills.begin(), m_stills.end(),    //erase object that has been eaten
			[](const auto& obj) { return obj->beenEaten(); }),	m_stills.end());

	m_presents.erase(std::remove_if(m_presents.begin(), m_presents.end(),    //erase presents that has been eaten
		[](const auto& present) { return present->beenEaten(); }), m_presents.end());

	m_controller->removeCat();  //check if need to remove cat

	m_controller->resetMovingPos();  //check if need to move mouse and cat to init position becouse of mouse cat collision

	if (m_freezeTimer.getElapsedTime().asSeconds()>=TIME)
	{
		Cat::needFreeze(false);
		m_controller->makeCatBlue(false);
	}

}

//fill present vector of different kinds of present
void Board::fillPresents(const sf::Vector2f &tileSize, const sf::Vector2f &currentPosition)
{
	if (!m_firstPresent)   //first present in vector is kiil cat
	{
		m_presents.push_back(std::make_unique<KillCatPresent>(tileSize, currentPosition, Manage::getInstance().getTexture(O_PRESENT)));
		m_firstPresent = true;
	}
	else
	{
		switch (m_presents.size() % 3)
		{
		case 0:  //third present in vector is more life
		{
			m_presents.push_back(std::make_unique<MoreLifePresent>(tileSize, currentPosition, Manage::getInstance().getTexture(O_PRESENT)));
			break;
		}
		case 1: //second present in vector is freeze cats
		{
			m_presents.push_back(std::make_unique<FreezePresent>(tileSize, currentPosition, Manage::getInstance().getTexture(O_PRESENT)));
			break;
		}
		case 2: //forth present in vector is increace time
		{
			m_presents.push_back(std::make_unique<IncreaseTimePresent>(tileSize, currentPosition, Manage::getInstance().getTexture(O_PRESENT)));
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


sf::FloatRect Board::getGlobalBounds() const
{
	return sf::FloatRect(START_POINT.x, START_POINT.y, BOARD_WIDTH, BOARD_HEIGHT);
}


bool Board::inBounds(sf::FloatRect rect) const  //check if object is in board bounds
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
	float down = DOWN_B;

	std::string str= std::to_string(m_level);
	text = make(str, Manage::getInstance().getFont(), down);
	
	window.draw(text);

	str = std::to_string(m_keyCount);
	down += DOWN_B*2;
	text= make(str, Manage::getInstance().getFont(), down);
	window.draw(text);
}

//function to make text
sf::Text Board::make(const std::string& str, const sf::Font* font, float down)
{
	sf::Text text(str, *font);
	text.setPosition({ POS_X, down });
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(TEXT_SIZE);

	return text;
}
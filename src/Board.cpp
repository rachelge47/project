#include "Board.h"
#include "GameControl.h"
#include "collisions.h"


Board::Board()
	:m_level(0)
{}


int Board::m_cheeseCount;
int Board::m_keyCount;
int Board::m_presentCount;
int Board::m_initKeyCount;
int Board::m_initCheeseCount;


void Board::loadFromFile()
{	
	auto boardFile = std::ifstream("Board.txt");

	if (!boardFile.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	getStills(boardFile);

	//boardFile.clear();  // Clear any error flags
	
	
}


void Board::getStills(std::ifstream& boardFile)
{
	std::string line;

	std::vector<std::string> fileContent;

	//contain the board to know num of rows and cols
	for (auto line = std::string(); std::getline(boardFile, line) && !line.empty();)
	{
		fileContent.push_back(line);
	}

	int rows = fileContent.size();
	int cols= fileContent[0].size();
	
	//calculate the tiles size Depends on the size of window
	float tileWidth = (WIDTH - 200 )/ cols;
	float tileHeight = (LENGTH - 100) / rows;
	
	sf::Vector2f tileSize = { tileWidth,tileHeight };
	//

	sf::Vector2f currentPosition(20, 20);

	for (int i = 0; i < fileContent.size(); i++)
	{
		for (int j = 0; j < fileContent[i].size(); j++)
		{
			//std::cout << line[j] << std::endl;

		
			currentPosition.x = 20 + (j * tileWidth);
			currentPosition.y = 20 + (i * tileHeight);
			// 
			//currentPosition.x = 250 + (j * 50);
			//currentPosition.y = 20 + (i * 50);

			switch (/*line[j]*/fileContent[i][j])
			{
			case WALL:
			{
				m_stills.push_back(std::make_unique<Wall>(tileSize,currentPosition, Manage::getTexture(O_WALL)));
				break;
			}
			case CHEESE:
			{
				m_initCheeseCount++;
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
				m_presentCount++;
				m_stills.push_back(std::make_unique<Present>(tileSize,currentPosition, Manage::getTexture(O_PRESENT)));
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

				GameControl::getInstance()->addCat(tempSize,currentPosition);
				break;
			}

			case MOUSE:
			{
				sf::Vector2f tempSize;     //make mouse size a bit smaller so can pass in narrow spaces
				tempSize.x= tileSize.x / 1.2;
				tempSize.y= tileSize.y / 1.2;

				GameControl::getInstance()->saveMouse(tempSize,currentPosition);
				break;
			}

			default:
				break;
			}
		}
	}	
}



void Board::checkCollisions(const std::unique_ptr<Mouse>& mouse, const std::vector <std::unique_ptr <Cat>>& cats , const sf::Time& deltaTime)
{
	for (auto& obj : m_stills)   //handle mouse collision
	{
		if (mouse->getGlobalBounds().intersects(obj->getGlobalBounds()))
		{
			processCollision(*mouse, *obj, deltaTime);
		}
	}

	for (auto& cat : cats)   //handle cats collision
	{
		for (auto& obj : m_stills)
		{
			if (cat->getGlobalBounds().intersects(obj->getGlobalBounds()))
			{
				processCollision(*cat, *obj, deltaTime);
			}
		}
	}
	
	m_stills.erase( std::remove_if(m_stills.begin(), m_stills.end(),    //erase object that has been eaten
			[](const auto& obj) { return obj->beenEaten(); }),	m_stills.end());
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



//function to check tif the board is in bounds of window
//Manage::setObjSize(the size that will fits)
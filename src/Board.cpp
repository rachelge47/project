#include "Board.h"
#include "GameControl.h"

Board::Board()
	:m_level(0)
{}


int Board::m_cheeseCount;
int Board::m_keyCount;
int Board::m_presentCount;


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
				m_cheeseCount++;
				m_stills.push_back(std::make_unique<Cheese>(tileSize,currentPosition, Manage::getTexture(O_CHEESE)));
				break;
			}
			case KEY:
			{
				m_keyCount++;
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
				GameControl::getInstance()->addCat(tileSize,currentPosition);
				break;
			}

			case MOUSE:
			{
				GameControl::getInstance()->saveMouse(tileSize,currentPosition);
				break;
			}

			default:
				break;
			}
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



//function to check tif the board is in bounds of window
//Manage::setObjSize(the size that will fits)
#include "Board.h"
#include "GameControl.h"

Board::Board()
	:m_level(0)
{}


void Board::loadFromFile()
{	
	auto boardFile = std::ifstream("Board.txt");

	if (!boardFile.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	getStills(boardFile);
	
}

void Board::getStills(std::ifstream& boardFile)
{
	std::string line;
	sf::Vector2f currentPosition(20, 20);

	for (int i = 0; std::getline(boardFile, line) && !line.empty(); ++i)
	{
		for (int j = 0; j < line.size(); ++j)
		{
			std::cout << line[j] << std::endl;

		
			currentPosition.x = 250 + (j * 50);
			currentPosition.y = 20 + (i * 50);

			switch (line[j])
			{
			case WALL:
			{
				m_stills.push_back(std::make_unique<Wall>(currentPosition, Manage::getTexture(O_WALL)));
				break;
			}
			case CHEESE:
			{
				m_stills.push_back(std::make_unique<Cheese>(currentPosition, Manage::getTexture(O_CHEESE)));
				break;
			}
			case KEY:
			{
				m_stills.push_back(std::make_unique<Key>(currentPosition, Manage::getTexture(O_KEY)));
				break;
			}
			case PRESENT:
			{
				m_stills.push_back(std::make_unique<Present>(currentPosition, Manage::getTexture(O_PRESENT)));
				break;
			}
			case DOOR:
			{
				m_stills.push_back(std::make_unique<Door>(currentPosition, Manage::getTexture(O_DOOR)));
				break;
			}

			case CAT:
			{
				GameControl::getInstance()->addCat(currentPosition);
			}

			case MOUSE:
			{
				GameControl::getInstance()->saveMouse(currentPosition);
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
#include "Board.h"
#include "GameControl.h"

Board::Board()
	:m_level(0)
{
}


void Board::loadFromFile()
{	
	auto boardFile = std::ifstream("C:/Users/Cheko/source/repos/project.c/resources/Board.txt");

	if (!boardFile.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::string line;
	/*while (std::getline(boardFile, line) && !line.empty())
	{
		for (auto& ch : line)
		{*/

	for (size_t i = 0; std::getline(boardFile, line) && !line.empty(); ++i)
	{
		for (size_t j = 0; j < line.size(); ++j)
		{
			std::cout << line[j]<< std::endl;
			
			sf::Vector2f currentPosition(j * 60, i * 60);

			switch (line[j])
			{
			case WALL:
			{
				m_stills.push_back(std::make_unique<Wall>(currentPosition, Manage::getTexture()[O_WALL]));
				break;
			}
			case CHEESE:
			{
				m_stills.push_back(std::make_unique<Cheese>(currentPosition, Manage::getTexture()[O_CHEESE]));
				break;
			}
			case KEY:
			{
				m_stills.push_back(std::make_unique<Key>(currentPosition, Manage::getTexture()[O_KEY]));
				break;
			}
			case PRESENT:
			{
				m_stills.push_back(std::make_unique<Present>(currentPosition, Manage::getTexture()[O_PRESENT]));
				break;
			}
			case DOOR:
			{
				m_stills.push_back(std::make_unique<Door>(currentPosition, Manage::getTexture()[O_DOOR]));
				break;
			}
			
			case CAT:
			{
				//create cat vector and get cat func. 
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

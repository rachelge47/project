#include "Board.h"
#include "GameControl.h"

Board::Board()
	:m_level(0)
{}


void Board::loadFromFile()
{
	std::ifstream boardFile("Board.txt");

	if (!(boardFile.is_open()))
	{
		std::cout << "cannot open file";
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
			sf::Vector2f currentPosition(j * 60, i * 60);

			switch (line[j])
			{
			case WALL:
			{
				m_stills.push_back(std::make_unique<Wall>(currentPosition));
				break;
			}
			case CHEESE:
			{
				m_stills.push_back(std::make_unique<Cheese>(currentPosition));
				break;
			}
			case KEY:
			{
				m_stills.push_back(std::make_unique<Key>(currentPosition));
				break;
			}
			case PRESENT:
			{
				m_stills.push_back(std::make_unique<Present>(currentPosition));
				break;
			}
			case DOOR:
			{
				m_stills.push_back(std::make_unique<Door>(currentPosition));
				break;
			}
			
			//case CAT:
			//{
			//	//create cat vector and get cat func. 
			////	GameControl::getInstance()->addCat(position);

			//}

			/*case MOUSE:
			{
				GameControl::getInstance()->saveMouse(position);
			}*/

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

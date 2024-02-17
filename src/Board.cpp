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

	while (std::getline(boardFile, line) && !line.empty())
	{
		for (auto& ch : line)
		{
			//std::unique_ptr<StillObject> newObj = nullptr;

			switch (ch)
			{
			case WALL:
			{
				m_stills.push_back(std::make_unique<Wall>());
				break;
			}
			case CHEESE:
			{
				m_stills.push_back(std::make_unique<Cheese>());
				break;
			}
			case KEY:
			{
				m_stills.push_back(std::make_unique<Key>());
				break;
			}
			case PRESENT:
			{
				m_stills.push_back(std::make_unique<Present>());
				break;
			}
			case DOOR:
			{
				m_stills.push_back(std::make_unique<Door>());
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

void Board::draw(const sf::RenderWindow & window)
{
	//draws the board
}

#include "Cat.h"

bool Cat::m_catDead = false;
bool Cat::m_cantMove = false;


//set the cat direction based on mouse loc an calct it to the smallest distance between them
sf::Vector2f Cat::catMovment(const sf::Vector2f& mouseLoc)
{
	sf::Vector2f catLoc= m_object.getPosition();

		//go left
		double mini_dist = distance(mouseLoc, { catLoc.x - 1, catLoc.y });
		sf::Vector2f newPos = { -1, 0 };

		//go right
		if (mini_dist > distance(mouseLoc, { catLoc.x+1 ,catLoc.y }))
		{
			mini_dist = distance(mouseLoc, { catLoc.x + 1 ,catLoc.y });
			newPos = { 1,0 };
		}

		//go up
		if (mini_dist > distance(mouseLoc, { catLoc.x, catLoc.y - 1 }))
		{
			mini_dist = distance(mouseLoc, { catLoc.x, catLoc.y - 1 });
			newPos = { 0, -1 };
		}

		//go down
		if (mini_dist > distance(mouseLoc, { catLoc.x, catLoc.y + 1 }))
		{
			mini_dist = distance(mouseLoc, { catLoc.x, catLoc.y + 1 });
			newPos = { 0,1 };
		}

		if (m_cantMove)
		{
			return { 0,0 };
		}
	
	return newPos;
}


double Cat::distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return std::hypot(v1.x - v2.x, v1.y - v2.y);
}


void Cat::makeBlue(bool stillFrozen)
{
	if (stillFrozen)
		m_object.setFillColor(sf::Color::Blue);
	
	else
		m_object.setFillColor(sf::Color::White);

}
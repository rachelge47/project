#include "Cat.h"

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
	
	return newPos;
}


double Cat::distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return std::hypot(v1.x - v2.x, v1.y - v2.y);
}

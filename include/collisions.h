#pragma once

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "GameObject.h"
#include "Manage.h"
#include "Mouse.h"
#include "Cat.h"
#include "StillObject.h"

//this namespace handles all collisions creating double v-table
namespace {
    float getOverLap(sf::Vector2f direction, sf::FloatRect rect1, sf::FloatRect rect2);
    sf::Vector2f overLapDirection(float overLap, sf::FloatRect rect1, sf::FloatRect rect2);


    void MouseWithWall(GameObject& mouse, GameObject& wall, const sf::Time& deltaTime)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Wall& c_wall= dynamic_cast <Wall&> (wall);

        auto MouseBounds = c_mouse.getGlobalBounds();
        auto WallBounds = c_wall.getGlobalBounds();

        auto reverseDirection = c_mouse.getDirection() * -1.f;


        auto overLap = getOverLap(c_mouse.getDirection(), MouseBounds, WallBounds);  //explain

        //handles the 'narrow aisles' cases 
        if (overLap < 15.f && overLap > 0.f)
        {
            sf::Vector2f direction = overLapDirection(overLap, MouseBounds, WallBounds);

            //'fixes' mouse to enter to the narrow aisle
            while (c_mouse.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
            {
                c_mouse.setDirection(direction* 0.1f);
                c_mouse.move(deltaTime);
            }
        }
        else
        {

            //moves back till gets out of wall bounds
            while (c_mouse.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
            {
                c_mouse.setDirection(reverseDirection * 0.1f);
                c_mouse.move(deltaTime);
            }
       }
    }


    float getOverLap(sf::Vector2f direction, sf::FloatRect rect1, sf::FloatRect rect2)
    {
        auto leftCorner = std::abs(rect1.left + rect1.width - rect2.left);
        auto rightCorner = std::abs(rect1.left - (rect2.left + rect2.width));

        // Assuming RIGHT, LEFT, UP, DOWN are defined constants
        if (direction == RIGHT || direction == LEFT)
            return std::min(std::abs(rect1.top + rect1.height - rect2.top), std::abs(rect1.top - (rect2.top + rect2.height)));
        else if (direction == UP || direction == DOWN)
            return std::min(rightCorner, leftCorner);

        // Add an appropriate return value in case none of the conditions are satisfied
        return 0.0f;
    }

    sf::Vector2f overLapDirection(float overLap, sf::FloatRect rect1, sf::FloatRect rect2)
    {
        if (overLap == std::abs(rect1.left + rect1.width - rect2.left))
            return LEFT;
        else if (overLap == std::abs(rect1.left - (rect2.left + rect2.width)))
            return RIGHT;
        else if (overLap == std::abs(rect1.top - (rect2.top + rect2.height)))
            return DOWN;
        else if (overLap == std::abs(rect1.top + rect1.height - rect2.top))
            return UP;

        // Add a default return value in case none of the conditions are satisfied
        return sf::Vector2f(0.0f, 0.0f);
    }

    void MouseWithDoor(GameObject& mouse, GameObject& door, const sf::Time& deltaTime)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Door& c_door = dynamic_cast <Door&> (door);

        auto MouseBounds = c_mouse.getGlobalBounds();
        auto DoorBounds = c_door.getGlobalBounds();

    }



    void CatWithWall(GameObject& cat, GameObject& wall, const sf::Time& deltaTime)
    {
        Cat& c_cat = dynamic_cast <Cat&> (cat);
        Wall& c_wall = dynamic_cast <Wall&> (wall);

        auto CatBounds = c_cat.getGlobalBounds();
        auto WallBounds = c_wall.getGlobalBounds();

        auto reverseDirection = c_cat.getDirection() * -1.f;

        //moves back till gets out of wall bounds
        while (c_cat.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
        {
            c_cat.setDirection(reverseDirection * 0.1f);
            c_cat.move(deltaTime);
        }
    }
  
    

    

    using collisionFunc = void (*) (GameObject& object1, GameObject& object2, const sf::Time& deltaTime);
    using CollisionMap = std::unordered_map<std::string, collisionFunc>;


    std::unique_ptr<CollisionMap> CreateMap() {
        std::unique_ptr<CollisionMap> cm = std::make_unique<CollisionMap>();

        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Wall).name())] = MouseWithWall;
       // (*cm)[std::string(typeid(MovingObject).name()) + std::string(typeid(Wall).name())] = MovingObjectWithWall;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Door).name())] = MouseWithDoor;
        //(*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Key).name())] = MouseWithKey;
        //(*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Present).name())] = MouseWithPresnt;
        //(*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Cheese).name())] = MouseWithCeese;

        //(*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Cat).name())] = MouseWithCat;
        //(*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Mouse).name())] = CatWithMouse; //?

        (*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Wall).name())] = CatWithWall;
        //(*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Door).name())] = CatWithDoor;

        return cm;
    }

    collisionFunc lookup(const std::string& object1, const std::string& object2)
    {
        static std::unique_ptr<CollisionMap> map = CreateMap();
        std::string name = object1 + object2;
        auto itr = map->find(object1 + object2);
        if (itr == map->end())
            return nullptr;

        return itr->second;
    }


    void processCollision(GameObject& object1, GameObject& object2, const sf::Time& deltaTime)
    {
        collisionFunc p2f = lookup(typeid(object1).name(),
            typeid(object2).name());
        if (p2f)
            p2f(object1, object2, deltaTime);
    }
}
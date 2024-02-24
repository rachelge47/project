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
#include "Board.h"

//this namespace handles all collisions creating double v-table
namespace {
   
    int keysCount = 0;
    //Board board;
    
    void MouseWithWall(GameObject& mouse, GameObject& wall, const sf::Time& deltaTime)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Wall& c_wall= dynamic_cast <Wall&> (wall);

        auto reverseDirection = c_mouse.getDirection() * -1.f;

        //moves back till gets out of wall bounds
        while (c_mouse.getGlobalBounds().intersects(c_wall.getGlobalBounds()))
        {
            c_mouse.setDirection(reverseDirection * 0.1f);
            c_mouse.move(deltaTime);
        }  
    }


    void MouseWithDoor(GameObject& mouse, GameObject& door, const sf::Time& deltaTime)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Door& c_door = dynamic_cast <Door&> (door);

        if (Board::getKeyCount() > 0)
        {
            c_door.gotEaten();

            Board::setKeyCount(-1);
           // keysCount -= 1;
            c_mouse.addPoints(2);
        }

        else
        {
            int doorWidth = c_door.getSize();
            sf::Vector2f wallSize(static_cast<float>(doorWidth), static_cast<float>(doorWidth));

            auto wall = Wall(wallSize, c_door.getPosition(), Manage::getTexture(O_WALL));

            MouseWithWall(mouse, wall, deltaTime);
        }
    }

    void MouseWithKey(GameObject& mouse, GameObject& key, const sf::Time& deltaTime)
    {
        Key& c_key = dynamic_cast <Key&> (key);

        Board::setKeyCount(1);
       //keysCout+=1;
        c_key.gotEaten();
    }

    void MouseWithCheese(GameObject& mouse, GameObject& cheese, const sf::Time& deltaTime)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Cheese& c_cheese = dynamic_cast <Cheese&> (cheese);
       
        c_cheese.gotEaten();
        Board::setCheeseCount(1);
        c_mouse.addPoints(10);
        
    }

    void MouseWithPresent(GameObject& mouse, GameObject& present, const sf::Time& deltaTime)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Present& c_present = dynamic_cast <Present&> (present);

        c_present.gotEaten();
        c_mouse.addPoints(5);

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
  
    void CatWithDoor(GameObject& cat, GameObject& door, const sf::Time& deltaTime)
    {
        Door& c_door = dynamic_cast <Door&> (door);
     
        int doorWidth = c_door.getSize();
        sf::Vector2f wallSize(static_cast<float>(doorWidth), static_cast<float>(doorWidth));

        auto wall = Wall(wallSize, c_door.getPosition(), Manage::getTexture(O_WALL));

        CatWithWall(cat, wall, deltaTime);
    }

    

    using collisionFunc = void (*) (GameObject& object1, GameObject& object2, const sf::Time& deltaTime);
    using CollisionMap = std::unordered_map<std::string, collisionFunc>;


    std::unique_ptr<CollisionMap> CreateMap() {
        std::unique_ptr<CollisionMap> cm = std::make_unique<CollisionMap>();

        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Wall).name())] = MouseWithWall;
       // (*cm)[std::string(typeid(MovingObject).name()) + std::string(typeid(Wall).name())] = MovingObjectWithWall;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Door).name())] = MouseWithDoor;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Key).name())] = MouseWithKey;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Present).name())] = MouseWithPresent;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Cheese).name())] = MouseWithCheese;

        //(*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Cat).name())] = MouseWithCat;
        //(*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Mouse).name())] = CatWithMouse; //?

        (*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Wall).name())] = CatWithWall;
        (*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Door).name())] = CatWithDoor;

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
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
#include "Present.h"


//this namespace handles all collisions creating double v-table
namespace {
     
    void MouseWithWall(GameObject& mouse, GameObject& wall)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);

        c_mouse.setPos();
    }

    void mouseWithBoard(GameObject& mouse, const Board& board)
    {
        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        c_mouse.setPos();
    }


    void catWithBoard(GameObject& cat, const Board& board)
    {
        Cat& c_cat = dynamic_cast <Cat&> (cat);

        c_cat.setPos();
    }


    void MouseWithDoor(GameObject& mouse, GameObject& door)
    {

        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Door& c_door = dynamic_cast <Door&> (door);

        if (Board::getKeyCount() > 0)  //if the mose has a key, open the door
        {
            Manage::getInstance().getSound(O_OPENDOOR);

            c_door.gotEaten();

            Board::setKeyCount(-1);
            c_mouse.addPoints(2);
        }

        else   //without key, treat door like wall
        {
            int doorWidth = c_door.getSize();
            sf::Vector2f wallSize(static_cast<float>(doorWidth), static_cast<float>(doorWidth));

            auto wall = Wall(wallSize, c_door.getPosition(), Manage::getInstance().getTexture(O_WALL));

            MouseWithWall(mouse, wall);
        }
    }

    void MouseWithKey(GameObject& mouse, GameObject& key)
    {
        Key& c_key = dynamic_cast <Key&> (key);

        Board::setKeyCount(1);
        c_key.gotEaten();
        Manage::getInstance().getSound(O_EATCHEESE);
    }

    void MouseWithCheese(GameObject& mouse, GameObject& cheese)
    {
        if (Board::getCheeseCount() == 1)
        {
            Manage::getInstance().getSound(O_WON);
        }
        else
            Manage::getInstance().getSound(O_EATCHEESE);

        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        Cheese& c_cheese = dynamic_cast <Cheese&> (cheese);
       
        c_cheese.gotEaten();
        Board::setCheeseCount(-1);
        c_mouse.addPoints(10);
    }

    void MouseWithMoreLifePresent(GameObject& mouse, GameObject& present)
    {
        Manage::getInstance().getSound(O_PRESENT);

        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        MoreLifePresent& c_present = dynamic_cast <MoreLifePresent&> (present);

        c_present.gotEaten();
        c_mouse.addPoints(5);
        c_mouse.addLife(1);
    }

    void MouseWithKillCatPresent(GameObject& mouse, GameObject& present)
    {
        Manage::getInstance().getSound(O_PRESENT);

        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        KillCatPresent& c_present = dynamic_cast <KillCatPresent&> (present);

        c_present.gotEaten();
        c_mouse.addPoints(5);
        Cat::catNeedToDie();
    }

    void MouseWithTimePresent(GameObject& mouse, GameObject& present)
    {
        Manage::getInstance().getSound(O_PRESENT);

        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        IncreaseTimePresent& c_present = dynamic_cast <IncreaseTimePresent&> (present);

        c_present.gotEaten();
        c_mouse.addPoints(5);

        Data::needAddTime(); 
    }

    void MouseWithFreezePresent(GameObject& mouse, GameObject& present)
    {
        Manage::getInstance().getSound(O_PRESENT);

        Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);
        FreezePresent& c_present = dynamic_cast <FreezePresent&> (present);

        c_present.gotEaten();
        c_mouse.addPoints(5);

        Cat::needFreeze(true);
    }
    

    void CatWithMouse(GameObject& cat, GameObject& mouse)
    {
         Mouse& c_mouse = dynamic_cast <Mouse&> (mouse);

         if (c_mouse.getLife() == 1)
         {
             Manage::getInstance().getSound(O_GAMEOVER);
         }
         else
         {
             Manage::getInstance().getSound(O_CATMOUSE);
         }

         c_mouse.addLife(-1);
         c_mouse.mouseGotEaten(true);   
    }


    void CatWithWall(GameObject& cat, GameObject& wall)
    {
        Cat& c_cat = dynamic_cast <Cat&> (cat);       
        c_cat.setPos();
    }
  
    void CatWithDoor(GameObject& cat, GameObject& door)
    {
        Door& c_door = dynamic_cast <Door&> (door);
     
        int doorWidth = c_door.getSize();
        sf::Vector2f wallSize(static_cast<float>(doorWidth), static_cast<float>(doorWidth));

        auto wall = Wall(wallSize, c_door.getPosition(), Manage::getInstance().getTexture(O_WALL));

        CatWithWall(cat, wall);  //treat the door like a wall
    }


    using collisionFunc = void (*) (GameObject& object1, GameObject& object2);
    using CollisionMap = std::unordered_map<std::string, collisionFunc>;

    //v-table
    std::unique_ptr<CollisionMap> CreateMap() {
        std::unique_ptr<CollisionMap> cm = std::make_unique<CollisionMap>();

        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Wall).name())] = MouseWithWall;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Door).name())] = MouseWithDoor;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Key).name())] = MouseWithKey;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(IncreaseTimePresent).name())] = MouseWithTimePresent;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(KillCatPresent).name())] = MouseWithKillCatPresent;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(FreezePresent).name())] = MouseWithFreezePresent;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(MoreLifePresent).name())] = MouseWithMoreLifePresent;
        (*cm)[std::string(typeid(Mouse).name()) + std::string(typeid(Cheese).name())] = MouseWithCheese;

        (*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Mouse).name())] = CatWithMouse;

        (*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Wall).name())] = CatWithWall;
        (*cm)[std::string(typeid(Cat).name()) + std::string(typeid(Door).name())] = CatWithDoor;

        return cm;
    }

    //function to return which the name of the objects prosses collisions resived
    collisionFunc lookup(const std::string& object1, const std::string& object2)  
    {
        static std::unique_ptr<CollisionMap> map = CreateMap();
        std::string name = object1 + object2;
        auto itr = map->find(object1 + object2);
        if (itr == map->end())
            return nullptr;

        return itr->second;
    }

   
    void processCollision(GameObject& object1, GameObject& object2)
    {
        collisionFunc p2f = lookup(typeid(object1).name(),
            typeid(object2).name());
        if (p2f)
            p2f(object1, object2);
    }
}
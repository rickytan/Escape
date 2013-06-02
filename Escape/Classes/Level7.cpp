//
//  Level7.cpp
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#include "Level7.h"
#include "Room.h"

CCScene* Level7::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(Level7::create());
    return scene;
}

bool Level7::init()
{
    if (!CCLayer::init())
        return false;
    
    Room *middle = RoomMonkey::create();
    
    addChild(middle);
    
    middle->show();
    
    return true;
}
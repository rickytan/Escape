//
//  CoffeCup.cpp
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#include "CoffeCup.h"

bool CoffeCup::init()
{
    if (!CCSprite::initWithFile("coffecup.png"))
        return false;
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    return true;
}

bool CoffeCup::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
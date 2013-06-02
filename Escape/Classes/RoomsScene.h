//
//  RoomsScene.h
//  Escape
//
//  Created by ricky on 12-12-11.
//
//

#ifndef __Escape__RoomsScene__
#define __Escape__RoomsScene__

#include <iostream>
#include "cocos2d.h"
#include "Prop.h"

USING_NS_CC;

class Rooms : public CCLayer
{
private:

    Prop                * coffeCup;
    
    CCNode              * selectedNode;
    
    void addCoffeCup();
    void removeCoffeCup();
    
    void gotoRoom(CCScene *room);
    
    void onLeftDoor(CCObject *sender);
    void onRightDoor(CCObject *sender);
    void onMiddleDoor(CCObject *sender);
    
    void onBag(CCObject *sender);
    
    void onEnterTransitionDidFinish();
    void onExit();
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
public:
    virtual bool init();
    static CCScene *scene();
    
    CREATE_FUNC(Rooms);
};



#endif /* defined(__Escape__RoomsScene__) */

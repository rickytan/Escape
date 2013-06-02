//
//  RoomsScene.cpp
//  Escape
//
//  Created by ricky on 12-12-11.
//
//

#include "RoomsScene.h"
#include "SimpleAudioEngine.h"
#include "Collections.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene *Rooms::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(Rooms::create());
    return scene;
}

bool Rooms::init()
{
    if (!CCLayer::init())
        return false;
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCPoint c = ccpMult(ccpFromSize(s), 0.5);
    
    CCLayer *roomBgLayer = CCLayer::create();
    addChild(roomBgLayer,-1);
    
    CCSprite *bg = CCSprite::create("background.png");
    bg->setPosition(ccp(s.width/2, s.height/2));
    roomBgLayer->addChild(bg,-1);
    
    CCMenuItemImage *leftItem = CCMenuItemImage::create("doorl.png", NULL, this, menu_selector(Rooms::onLeftDoor));
    CCMenuItemImage *middleItem = CCMenuItemImage::create("doorm.png", NULL, this, menu_selector(Rooms::onMiddleDoor));
    CCMenuItemImage *rightItem = CCMenuItemImage::create("doorr.png", NULL, this, menu_selector(Rooms::onRightDoor));
    
    CCMenu *menu = CCMenu::create(leftItem, middleItem, rightItem, NULL);
    menu->alignItemsHorizontallyWithPadding(80.0);
    roomBgLayer->addChild(menu);
    
    coffeCup = Prop::createWithFileAndInitScale("coffecup.png", 0.25);
    coffeCup->setPosition(ccp(s.width/2, 60.0));
    addChild(coffeCup);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("zipper.m4a");
    
    //setTouchEnabled(true);
    
    return true;
}

void Rooms::onEnterTransitionDidFinish()
{
    Collections::sharedCollections()->displayInLayer(this);
    
    CCLayer::onEnterTransitionDidFinish();
}

void Rooms::onExit()
{
    Collections::sharedCollections()->removeDisplay();
    CCLayer::onExit();
}

void Rooms::gotoRoom(cocos2d::CCScene *room)
{
    
}

void Rooms::onLeftDoor(cocos2d::CCObject *sender)
{

    
}

void Rooms::onMiddleDoor(cocos2d::CCObject *sender)
{
    
}

void Rooms::onRightDoor(cocos2d::CCObject *sender)
{
    
}

void Rooms::onBag(cocos2d::CCObject *sender)
{
    
}

void Rooms::addCoffeCup()
{
  
    //Collections::sharedCollections()->addItem(item);
}

void Rooms::removeCoffeCup()
{
    SimpleAudioEngine::sharedEngine()->playEffect("zipper.m4a");
    coffeCup->removeFromParentAndCleanup(true);
    coffeCup = NULL;
}

void Rooms::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    
}

void Rooms::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint p = touch->getLocation();
    if (coffeCup && coffeCup->boundingBox().containsPoint(p)) {
        addCoffeCup();
    }
}


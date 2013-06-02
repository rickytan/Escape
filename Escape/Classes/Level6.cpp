//
//  Level6.cpp
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#include "Level6.h"
#include "Room.h"

CCScene* Level6::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(Level6::create());
    return scene;
}

bool Level6::init()
{
    if (!CCLayer::init())
        return false;

    collectionBox = CollectionBox::createWithProps(CCArray::create());
    collectionBox->setRules(new GameRules);
    collectionBox->setVisible(false);
    addChild(collectionBox, 2);
    
    collectionBag = CCMenuItemImage::create("bag.png", NULL, this,menu_selector(Level6::onBagPressed));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    collectionBag->setPosition(ccp(size.width - collectionBag->getContentSize().width/2,
                                   collectionBag->getContentSize().height/2));
    collectionBag->setScale(0.0);
    
    CCMenu *menu = CCMenu::createWithItem(collectionBag);
    menu->setPosition(CCPointZero);
    
    CCLayer *menuLayer = CCLayer::create();
    addChild(menuLayer, 3);
    menuLayer->addChild(menu);
    
    RoomPasscode2 *middle = RoomPasscode2::create();
    RoomTaiji *left = RoomTaiji::create();
    RoomSwitch *right = RoomSwitch::create();
    
    left->setRoomPasscode(middle);
    left->setRoomSwitch(right);
    
    right->setRoomTaiji(left);
    
    middle->setPropDidPickTarget(this, (SEL_roomPickProp)&Level6::onPickProp);
    left->setPropDidPickTarget(this, (SEL_roomPickProp)&Level6::onPickProp);
    right->setPropDidPickTarget(this, (SEL_roomPickProp)&Level6::onPickProp);
    
    
    addChild(middle);
    addChild(left);
    addChild(right);
    
    middle->setLeftRoom(left);
    middle->setRightRoom(right);
    
    middle->show();
    
    return true;
}

bool Taiji::init()
{
    if (!CCLayer::init())
        return false;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    setPosition(ccp(size.width/2, size.height/2));
    
    blackHalf = CCSprite::create("taijiB.png");
    whiteHalf = CCSprite::create("taijiW.png");
    
    blackDot = CCSprite::create("Bpoint.png");
    whiteDot = CCSprite::create("Wpoint.png");
    
    blackDot->setPosition(ccp(46, 82));
    blackDot->setVisible(false);
    whiteDot->setPosition(ccp(50, 30));
    whiteDot->setVisible(false);
    
    blackHalf->addChild(whiteDot);
    whiteHalf->addChild(blackDot);

    blackHalf->setPosition(ccp(-14, 0));
    whiteHalf->setPosition(ccp(14,-5));
    
    addChild(blackHalf);
    addChild(whiteHalf);
    
    setTouchEnabled(true);
    
    return true;
}
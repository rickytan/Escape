//
//  Level5.cpp
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#include "Level5.h"
#include "Room.h"

CCScene* Level5::scene()
{
    CCScene *s = CCScene::create();
    s->addChild(Level5::create());
    return s;
}

bool Level5::init()
{
    if (!CCLayer::init())
        return false;
    
    
    collectionBox = CollectionBox::createWithProps(CCArray::create());
    collectionBox->setVisible(false);
    Level5Rule *rule = new Level5Rule;
    collectionBox->setRules(rule);
    addChild(collectionBox, 2);
    
    collectionBag = CCMenuItemImage::create("bag.png", NULL, this,menu_selector(Level5::onBagPressed));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    collectionBag->setPosition(ccp(size.width - collectionBag->getContentSize().width/2,
                                   collectionBag->getContentSize().height/2));
    collectionBag->setScale(0.0);
    
    CCMenu *menu = CCMenu::createWithItem(collectionBag);
    menu->setPosition(CCPointZero);
    
    CCLayer *menuLayer = CCLayer::create();
    addChild(menuLayer, 3);
    menuLayer->addChild(menu);
    
    
    
    RoomPassword *middle = RoomPassword::create();
    Room *left = RoomTorch::create();
    RoomNewpaper *right = RoomNewpaper::create();
    
    rule->setRoomPassword(middle);
    rule->setRoomNewpaper(right);
    
    middle->setPropDidPickTarget(this, (SEL_roomPickProp)&Level5::onPickProp);
    left->setPropDidPickTarget(this, (SEL_roomPickProp)&Level5::onPickProp);
    right->setPropDidPickTarget(this, (SEL_roomPickProp)&Level5::onPickProp);
    
    addChild(middle);
    addChild(left);
    addChild(right);
    
    middle->setLeftRoom(left);
    middle->setRightRoom(right);
    
    middle->show();
    
    return true;
}

void Level5Rule::dragOut(Prop *p)
{
    roomnewspaper->turnOnLight();
    p->setVisible(false);
}

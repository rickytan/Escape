//
//  Level4.cpp
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#include "Level4.h"
#include "Room.h"

CCScene* Level4::scene()
{
    CCScene *s = CCScene::create();
    s->addChild(Level4::create());
    return s;
}

bool Level4::init()
{
    if (!CCLayer::init())
        return false;
    
    
    collectionBox = CollectionBox::createWithProps(CCArray::create());
    collectionBox->setVisible(false);
    Level4Rule *rule = new Level4Rule;
    collectionBox->setRules(rule);
    addChild(collectionBox, 2);
    
    collectionBag = CCMenuItemImage::create("bag.png", NULL, this,menu_selector(Level4::onBagPressed));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    collectionBag->setPosition(ccp(size.width - collectionBag->getContentSize().width/2,
                                   collectionBag->getContentSize().height/2));
    collectionBag->setScale(0.0);
    
    CCMenu *menu = CCMenu::createWithItem(collectionBag);
    menu->setPosition(CCPointZero);
    
    CCLayer *menuLayer = CCLayer::create();
    addChild(menuLayer, 3);
    menuLayer->addChild(menu);
    
    
    
    RoomPasscode *middle = RoomPasscode::create();
    Room *left = RoomCD::create();
    Room *right = RoomFackman::create();
    
    rule->setRoom(middle);
    
    middle->setPropDidPickTarget(this, (SEL_roomPickProp)&Level4::onPickProp);
    left->setPropDidPickTarget(this, (SEL_roomPickProp)&Level4::onPickProp);
    right->setPropDidPickTarget(this, (SEL_roomPickProp)&Level4::onPickProp);
    
    addChild(middle);
    addChild(left);
    addChild(right);
    
    middle->setLeftRoom(left);
    middle->setRightRoom(right);
    
    middle->show();
    
    return true;
}

Prop* Level4Rule::merge(Prop *p1, Prop *p2)
{
    if ((p1->getType() == kProp_Type_Tag_CD&&p2->getType() == kProp_Type_Tag_Fakeman)||
        (p2->getType() == kProp_Type_Tag_CD&&p1->getType() == kProp_Type_Tag_Fakeman))
    {
        if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("dream-heaven.mp3",false);
        room->showCodeInput();
        passed = true;
        return NULL;
//        return (p1->getType() == kProp_Type_Tag_Fakeman)?p1:p2;
    }
    
    return NULL;
}

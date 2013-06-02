//
//  Level3.cpp
//  Escape
//
//  Created by ricky on 12-12-17.
//
//

#include "Level3.h"
#include "Room.h"


CCScene* Level3::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(create());
    return scene;
}

bool Level3::init()
{
    if (!CCLayer::init())
        return false;
    
    
    collectionBox = CollectionBox::createWithProps(CCArray::create());
    collectionBox->setVisible(false);
    Level3Rule *rule = new Level3Rule;
    collectionBox->setRules(rule);
    addChild(collectionBox, 2);
    
    collectionBag = CCMenuItemImage::create("bag.png", NULL, this,menu_selector(Level3::onBagPressed));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    collectionBag->setPosition(ccp(size.width - collectionBag->getContentSize().width/2,
                                   collectionBag->getContentSize().height/2));
    collectionBag->setScale(0.0);
    
    CCMenu *menu = CCMenu::createWithItem(collectionBag);
    menu->setPosition(CCPointZero);
    
    CCLayer *menuLayer = CCLayer::create();
    addChild(menuLayer, 3);
    menuLayer->addChild(menu);
    
    
    
    RoomOperator *middle = RoomOperator::create();
    Room *left = RoomCodeBox::create();
    Room *right = RoomShip::create();
    
    rule->setRoom(middle);
    
    middle->setPropDidPickTarget(this, (SEL_roomPickProp)&Level3::onPickProp);
    left->setPropDidPickTarget(this, (SEL_roomPickProp)&Level3::onPickProp);
    right->setPropDidPickTarget(this, (SEL_roomPickProp)&Level3::onPickProp);
    
    addChild(middle);
    addChild(left);
    addChild(right);
    
    middle->setLeftRoom(left);
    middle->setRightRoom(right);
    
    middle->show();
    

    return true;
}


bool Level3Rule::canDragOut(Prop *p) {
    return p->getType() == kProp_Type_Tag_Wheel && room->isVisible();
}

void Level3Rule::dragOut(Prop *p) {
    room->installWheel(p);
}
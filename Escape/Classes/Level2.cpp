//
//  Level1.cpp
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#include "Level2.h"

CCScene* Level2::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(create());
    return scene;
}

bool Level2::init()
{
    if (!CCLayer::init())
        return false;
    
    collectionBox = CollectionBox::createWithProps(CCArray::create());
    collectionBox->setVisible(false);
    Level2Rule *rule = new Level2Rule;
    collectionBox->setRules(rule);
    addChild(collectionBox, 2);
    
    collectionBag = CCMenuItemImage::create("bag.png", NULL, this,menu_selector(Level2::onBagPressed));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    collectionBag->setPosition(ccp(size.width - collectionBag->getContentSize().width/2,
                                   collectionBag->getContentSize().height/2));
    collectionBag->setScale(0.0);
    
    CCMenu *menu = CCMenu::createWithItem(collectionBag);
    menu->setPosition(CCPointZero);
    
    CCLayer *menuLayer = CCLayer::create();
    addChild(menuLayer, 3);
    menuLayer->addChild(menu);
    
    
    
    RoomCoffecup *middle = RoomCoffecup::create();
    Room *left = RoomBean::create();
    Room *right = RoomCoffeMachine::create();
    
    rule->setRoom(middle);
    
    middle->setPropDidPickTarget(this, (SEL_roomPickProp)&Level2::onPickProp);
    left->setPropDidPickTarget(this, (SEL_roomPickProp)&Level2::onPickProp);
    right->setPropDidPickTarget(this, (SEL_roomPickProp)&Level2::onPickProp);
    
    addChild(middle);
    addChild(left);
    addChild(right);
    
    middle->setLeftRoom(left);
    middle->setRightRoom(right);
    
    middle->show();
    
    
    
    return true;
}


Prop* Level2Rule::merge(Prop *p1, Prop *p2) {
    if ((p1->getType() == kProp_Type_Tag_CoffeBean&&p2->getType() == kProp_Type_Tag_CoffeMachine)||
        (p2->getType() == kProp_Type_Tag_CoffeBean&&p1->getType() == kProp_Type_Tag_CoffeMachine))
    {
        isBeanInMathine = true;
        SimpleAudioEngine::sharedEngine()->playEffect("coffe-boil.m4a");
        return (p1->getType() == kProp_Type_Tag_CoffeMachine)?p1:p2;
    }
    if (isBeanInMathine &&
        ((p1->getType() == kProp_Type_Tag_CoffeCup&&p2->getType() == kProp_Type_Tag_CoffeMachine)||
         (p2->getType() == kProp_Type_Tag_CoffeCup&&p1->getType() == kProp_Type_Tag_CoffeMachine)))
    {
        passed = true;
        Prop *p = Prop::createWithFileAndInitScale("ccupwithlogo.png", 0.35);
        p->setDescription("我好像喝过这里的冬享咖啡,但必须加三份糖");
        room->showCodeInput();
        return p;
    }
    return NULL;
}
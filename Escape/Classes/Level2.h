//
//  Level1.h
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#ifndef __Escape__Level1__
#define __Escape__Level1__

#include <iostream>
#include "cocos2d.h"
#include "Room.h"
#include "CollectionBox.h"
#include "Collections.h"
#include "GameRules.h"

USING_NS_CC;

class Level2 : public CCLayer
{
private:
    CollectionBox           * collectionBox;
    CCMenuItemImage         * collectionBag;
    
    Level2():collectionBag(NULL),collectionBox(NULL)
    {}
    
    void onBagPressed(CCObject *sender) {
        collectionBag->runAction(CCSequence::create
                                 (
                                  CCEaseInOut::create(CCScaleTo::create(0.2, 0.7), 2),
                                  CCEaseElasticOut::create(CCScaleTo::create(0.3, 0.5), 2),
                                  NULL
                                  ));
        collectionBox->show();
    }
    
    void onPickProp(Prop *p) {
        collectionBag->runAction(CCSequence::create
                                 (
                                  CCEaseInOut::create(CCScaleTo::create(0.2, 0.7), 2),
                                  CCEaseElasticOut::create(CCScaleTo::create(0.3, 0.5), 2),
                                  NULL
                                  ));
        if (collectionBox->isVisible()) {
            collectionBox->addPros(p);
        }
        else {
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            collectionBox->setPosition(ccp(0,-size.height));
            
            CCMoveTo *move = CCMoveTo::create(0.6, CCPointZero);
            CCActionInterval *back = CCEaseBackOut::create(move);
            CCCallFuncO *call = CCCallFuncO::create(collectionBox, callfuncO_selector(CollectionBox::addPros), p);
            collectionBox->runAction(CCSequence::create(CCShow::create(),back,call,NULL));
            collectionBox->setTouchEnabled(true);
        }
    }
    
    virtual void onEnterTransitionDidFinish() {
        CCScaleTo *scale = CCScaleTo::create(1.0,.5);
        CCAction *back = CCEaseBackOut::create(scale);
        collectionBag->runAction(back);
        
        CCLayer::onEnterTransitionDidFinish();
    }
    
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Level2);
};

class RoomCoffecup;
class Level2Rule : public GameRules
{
private:
    bool                isBeanInMathine;
    bool                passed;
    
    CC_SYNTHESIZE(RoomCoffecup*, room, Room);
    
public:
    Level2Rule():isBeanInMathine(false),passed(false){
        SimpleAudioEngine::sharedEngine()->preloadEffect("coffe-boil.m4a");
    }
    ~Level2Rule(){}
    
    virtual bool canMerge(Prop *p1, Prop *p2) {
        if ((p1->getType() == kProp_Type_Tag_CoffeBean&&p2->getType() == kProp_Type_Tag_CoffeMachine)||
            (p2->getType() == kProp_Type_Tag_CoffeBean&&p1->getType() == kProp_Type_Tag_CoffeMachine))
        {
            return true;
        }
        if (isBeanInMathine &&
            ((p1->getType() == kProp_Type_Tag_CoffeCup&&p2->getType() == kProp_Type_Tag_CoffeMachine)||
             (p2->getType() == kProp_Type_Tag_CoffeCup&&p1->getType() == kProp_Type_Tag_CoffeMachine)))
        {
            return true;
        }
        
        return false;
    }
    virtual CCString* whyCannotMerge(Prop *p1, Prop *p2) {
        return CCString::createWithFormat("");
    }
    virtual Prop* merge(Prop *p1, Prop *p2);
    virtual bool isPassed() { return passed; }
};

#endif /* defined(__Escape__Level1__) */

//
//  Level3.h
//  Escape
//
//  Created by ricky on 12-12-17.
//
//

#ifndef __Escape__Level3__
#define __Escape__Level3__

#include <iostream>
#include "cocos2d.h"
#include "CollectionBox.h"

USING_NS_CC;

class Level3 : public CCLayer
{
private:
    CollectionBox           * collectionBox;
    CCMenuItemImage         * collectionBag;
    
    Level3():collectionBag(NULL),collectionBox(NULL)
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
    CREATE_FUNC(Level3);
    
    void installWheel() {
        
    }
};

class RoomOperator;

class Level3Rule : public GameRules
{
private:
    bool                isBeanInMathine;
    bool                passed;
public:
    Level3Rule():isBeanInMathine(false),passed(false){};
    ~Level3Rule(){}
    
    CC_SYNTHESIZE(RoomOperator*, room, Room);
    
    virtual bool canMerge(Prop *p1, Prop *p2) {        
        return false;
    }
    virtual CCString* whyCannotMerge(Prop *p1, Prop *p2) {
        return CCString::createWithFormat("");
    }
    virtual Prop* merge(Prop *p1, Prop *p2) {
        return NULL;
    }
    virtual bool isPassed() { return passed; }
    virtual bool canDragOut(Prop *p);
    virtual void dragOut(Prop *p);
};

#endif /* defined(__Escape__Level3__) */

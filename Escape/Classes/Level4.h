//
//  Level4.h
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#ifndef __Escape__Level4__
#define __Escape__Level4__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CollectionBox.h"
#include "Collections.h"

using namespace cocos2d;
using namespace CocosDenshion;

class Level4 : public CCLayer
{
private:
    CollectionBox           * collectionBox;
    CCMenuItemImage         * collectionBag;
    
    
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
    CREATE_FUNC(Level4);
};

class RoomPasscode;

class Level4Rule : public GameRules
{
private:
    bool                passed;
    
    CC_SYNTHESIZE(RoomPasscode*, room, Room);
    
public:
    Level4Rule():passed(false) {
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("dream-heaven.mp3");
    }
    ~Level4Rule(){}
    
    
    virtual bool canMerge(Prop *p1, Prop *p2) {
        if ((p1->getType() == kProp_Type_Tag_CD&&p2->getType() == kProp_Type_Tag_Fakeman)||
            (p2->getType() == kProp_Type_Tag_CD&&p1->getType() == kProp_Type_Tag_Fakeman))
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

#endif /* defined(__Escape__Level4__) */

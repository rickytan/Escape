//
//  Level4.h
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#ifndef __Escape__Level5__
#define __Escape__Level5__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CollectionBox.h"
#include "Collections.h"

using namespace cocos2d;
using namespace CocosDenshion;

class Level5 : public CCLayer
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
    CREATE_FUNC(Level5);
};

class RoomPassword;
class RoomNewpaper;

class Level5Rule : public GameRules
{
private:
    bool                passed;
    
    CC_SYNTHESIZE(RoomPassword*, roompassword, RoomPassword);
    CC_SYNTHESIZE(RoomNewpaper*, roomnewspaper, RoomNewpaper);
    
public:
    Level5Rule():passed(false) {
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("dream-heaven.mp3");
    }
    ~Level5Rule(){}
    
    
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
    virtual bool canDragOut(Prop *p) {
        return p->getType() == kProp_Type_Tag_Torch;
    }
    virtual void dragOut(Prop *p);
};

#endif /* defined(__Escape__Level5__) */

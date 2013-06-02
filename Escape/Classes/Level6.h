//
//  Level6.h
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#ifndef __Escape__Level6__
#define __Escape__Level6__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CollectionBox.h"
#include "Collections.h"

using namespace cocos2d;
using namespace CocosDenshion;

class Level6 : public CCLayer
{
private:
    CollectionBox           * collectionBox;
    CCMenuItemImage         * collectionBag;
    
    Level6():collectionBag(NULL),collectionBox(NULL)
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
    
    CREATE_FUNC(Level6);
};

class Taiji : public CCLayer
{
    CCSprite    * blackHalf;
    CCSprite    * whiteHalf;
    CCSprite    * blackDot;
    CCSprite    * whiteDot;
    
    bool         black,white;
    bool         opened;
    
    void split() {
        setTouchEnabled(false);
        opened = true;
        
        blackHalf->runAction(CCSequence::create(CCDelayTime::create(0.3),CCEaseInOut::create(CCMoveBy::create(0.6, ccp(-80,0)), 2),NULL));
        whiteHalf->runAction(CCSequence::create(CCDelayTime::create(0.3),CCEaseInOut::create(CCMoveBy::create(0.6, ccp(80,0)), 2),NULL));
    }
    virtual void onBlack(CCObject *sender) {
        if (white)
            return;
        white = true;
        whiteDot->setOpacity(0x0);
        whiteDot->runAction(CCSequence::create
                            (
                             CCShow::create(),
                             CCFadeIn::create(0.3),
                             NULL
                             ));
        if (black) {
            split();
        }
    }
    virtual void onWhite(CCObject *sender) {
        if (black)
            return;
        black = true;
        blackDot->runAction(CCSequence::create
                            (
                             CCShow::create(),
                             CCFadeIn::create(0.3),
                             NULL
                            ));
        if (white)
            split();
    }
    
    virtual void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
    }
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
        CCNode *parent = getParent();
        while (parent) {
            if (!parent->isVisible())
                return false;
            parent = parent->getParent();
        }
        CCPoint p = pTouch->getLocation();
        p = convertToNodeSpace(p);
        if (blackHalf->boundingBox().containsPoint(p) ||
            whiteHalf->boundingBox().containsPoint(p))
        {
            float bd = ccpDistance(convertToNodeSpace(blackHalf->convertToWorldSpace(whiteDot->getPosition())), p);
            float wd = ccpDistance(convertToNodeSpace(whiteHalf->convertToWorldSpace(blackDot->getPosition())), p);
            if (bd <= wd) {
                onBlack(NULL);
            }
            else {
                onWhite(NULL);
            }
            return true;
        }
        return false;
    }
    
public:
    Taiji():black(false),white(false),opened(false){}
    virtual ~Taiji(){}
    
    virtual bool init();
    
    CREATE_FUNC(Taiji);
    
    bool isOpend() { return opened; }
};

class RoomSwitch;
class RoomTaiji;

class Level6Rule : public GameRules
{
private:
    bool                passed;
    
    CC_SYNTHESIZE(RoomTaiji*, roomTaiji, RoomTaiji);
    CC_SYNTHESIZE(RoomSwitch*, roomSwitch, RoomSwitch);
    
public:
    Level6Rule():passed(false) {
    }
    ~Level6Rule(){}
    
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

};


#endif /* defined(__Escape__Level6__) */

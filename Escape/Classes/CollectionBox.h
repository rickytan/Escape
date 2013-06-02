//
//  CollectionBox.h
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#ifndef __Escape__CollectionBox__
#define __Escape__CollectionBox__

#include <iostream>
#include "cocos2d.h"
#include "Prop.h"
#include "SimpleAudioEngine.h"
#include "GameRules.h"

USING_NS_CC;
using namespace CocosDenshion;


enum {
    kPropDetail_Child_Tag = 100
};

class CollectionBox : public CCLayer
{
    CCArray                 * props;
    Prop                    * selectedProp;
    Prop                    * lastDrop;
    CCPoint                   lastLocation;
    
    CCSprite                * boxBackground;
    
    
    bool                      touchMoved;
    
    CollectionBox():props(NULL),selectedProp(NULL),lastLocation(CCPointZero),boxBackground(NULL),rules(NULL),touchMoved(false){}
    
    Prop* propWithTouch(CCTouch *touch);
    void showProp(Prop *p) {
        boxBackground->setVisible(false);
        
        if (p->getType() != kProp_Type_Tag_Newspaper) {
            PropDetail *detail = PropDetail::createWithProp((Prop*)p->copy());
            detail->setTag(kPropDetail_Child_Tag);
            addChild(detail,1);
        }
        else {
            Prop *p = Prop::createWithFileAndInitScale("paper.jpg", 1.0);
            p->setDescription("行报");
            PropDetail *detail = PropDetail::createWithProp(p);
            detail->setTag(kPropDetail_Child_Tag);
            addChild(detail,1);
        }
    }
    
    void relayoutProps() {
        CCObject *obj;
        CCARRAY_FOREACH(this->props, obj) {
            CCNode *node = (CCNode*)obj;
            CCPoint position = expactedPostionForProp((Prop*)node);
            node->runAction(CCEaseInOut::create(CCMoveTo::create(0.3, position), 2));
        }
    }
    
    void playSound() {
        SimpleAudioEngine::sharedEngine()->playEffect("zipper.m4a");
    }
    void hideProp() {
        removeChildByTag(kPropDetail_Child_Tag, true);
        boxBackground->setVisible(true);
    }
    
    bool isShownDetail() {
        return getChildByTag(kPropDetail_Child_Tag) != NULL;
    }
    
    CCPoint expactedPostionForProp(Prop *prop) {
        CCPoint p;
        p.y = boxBackground->getContentSize().height/2;
        p.x = 10;
        CCObject *obj = NULL;
        Prop *theProp = NULL;
        CCARRAY_FOREACH(this->props, obj) {
            theProp = (Prop*)obj;
            if (theProp == prop) {
                p.x += prop->getContentSize().width * prop->getScaleX()/2;
                return p;
            }
            p.x += theProp->getContentSize().width * theProp->getScaleX() + 10;
        }
        p.x += prop->getContentSize().width * prop->getScaleX()/2;
        //p.x = boxBackground->getContentSize().width - p.x;
        return p;
    }
    
    
    virtual void registerWithTouchDispatcher();
    
    void hideCallback() {
        setVisible(false);
    }
    
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void release();
    
    CC_SYNTHESIZE(GameRules*, rules, Rules);
    
public:
    static CollectionBox* createWithProps(CCArray *props);
    bool initWithProps(CCArray *props);
    
    void addPros(Prop *p);
    void show() {
        if (isVisible())
            return;
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        setPosition(ccp(0,-size.height));
        
        CCMoveTo *move = CCMoveTo::create(0.6, CCPointZero);
        CCActionInterval *back = CCEaseBackOut::create(move);
        runAction(CCSequence::create(CCShow::create(),back,NULL));
        setTouchEnabled(true);
    }
    void hide() {
        if (!isVisible())
            return;
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        CCMoveTo *move = CCMoveTo::create(0.6, ccp(0,-size.height));
        CCActionInterval *back = CCEaseBackIn::create(move);
        runAction(CCSequence::create(back, CCHide::create(),NULL));
    }
};

#endif /* defined(__Escape__CollectionBox__) */

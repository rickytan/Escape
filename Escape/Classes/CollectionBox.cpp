//
//  CollectionBox.cpp
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#include "CollectionBox.h"

CollectionBox* CollectionBox::createWithProps(cocos2d::CCArray *props)
{
    CollectionBox *b = new CollectionBox;
    if (b->initWithProps(props)) {
        b->autorelease();
    }
    else {
        delete b;
        b = NULL;
    }
    return b;
}

void CollectionBox::release()
{
    this->props->release();
    CCLayer::release();
}

bool CollectionBox::initWithProps(cocos2d::CCArray *props)
{
    if (!CCLayer::init())
        return false;
    
    this->props = new CCArray;
    this->props->initWithArray(props);
    
    this->selectedProp = NULL;
    this->lastLocation = CCPointZero;
    
    this->setPosition(CCPointZero);
    this->setAnchorPoint(CCPointZero);
    
    boxBackground = CCSprite::create("subtitlebar.png");
    boxBackground->setScale(0.8);
    boxBackground->setPosition(ccp(10,10));
    boxBackground->setAnchorPoint(CCPointZero);
    
    CCObject *obj = NULL;
    
    CCARRAY_FOREACH(this->props, obj) {
        Prop *sprite = (Prop*)obj;
        sprite->reset();
        sprite->setPosition(expactedPostionForProp(sprite));
        boxBackground->addChild(sprite);
    }
    
    this->addChild(boxBackground);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("zipper.m4a");
    
    return true;
}

void CollectionBox::addPros(Prop *p)
{
    if (!p)
        return;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint point = convertToWorldSpace(p->getPosition());
    point = boxBackground->convertToNodeSpace(point);
    p->retain();
    p->removeFromParentAndCleanup(false);
    p->setPosition(point);
    boxBackground->addChild(p);
    p->release();
    
    CCPoint c = expactedPostionForProp(p);
    ccBezierConfig bc = {
        c,
        ccp((point.x+c.x)/2,size.height/2),
        ccp(point.x/4+c.x*3/4,size.height/2)
    };
    CCBezierTo *bezier = CCBezierTo::create(1.5, bc);
    CCEaseInOut *ease = CCEaseInOut::create(bezier, 2.3);
    CCCallFuncO *call = CCCallFuncO::create(props, callfuncO_selector(CCArray::addObject), p);
    CCCallFunc *playsound = CCCallFunc::create(this, callfunc_selector(CollectionBox::playSound));
    CCActionInterval *scale = CCScaleTo::create(1.5, 0.35);
    //CCCallFuncN *call = CCCallFuncN::create(this, callfuncN_selector(Collections::removeSpriteCallback));
    p->setInitScale(0.35);
    p->runAction(CCSequence::create(CCSpawn::create(ease,scale,NULL),call,playsound, NULL));
}

Prop* CollectionBox::propWithTouch(cocos2d::CCTouch *touch)
{
    Prop *item = NULL;
    CCObject *obj = NULL;
    CCPoint point = boxBackground->convertToNodeSpace(touch->getLocation());
    CCARRAY_FOREACH(this->props, obj) {
        item = (Prop*)obj;
        if (item == selectedProp)
            continue;
        if (item->boundingBox().containsPoint(point)) {
            return item;
        }
    }
    return NULL;
}


void CollectionBox::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
}

bool CollectionBox::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (!isVisible())
        return false;
    
    if (isShownDetail()) {
        hideProp();
        return true;
    }
    
    touchMoved = false;
    
    if (boxBackground->boundingBox().containsPoint(pTouch->getLocation())) {
        selectedProp = propWithTouch(pTouch);
        if (selectedProp){
            selectedProp->selecte();
            lastLocation = selectedProp->getPosition();
            CCLOG("location:%f,%f",lastLocation.x,lastLocation.y);
        }
    }
    else {
        hide();
    }
    lastDrop = NULL;
    
    return true;
}

void CollectionBox::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    touchMoved = true;
    
    if (selectedProp) {
        selectedProp->setPosition(boxBackground->convertToNodeSpace(pTouch->getLocation()));
        
        Prop *drop = propWithTouch(pTouch);
        if (drop) {
            if (rules->canMerge(drop, selectedProp)) {
                drop->showLight(true);
                selectedProp->showLight(true);
            }
        }
        else
            selectedProp->showLight(false);
        
        if (lastDrop != drop) {
            if (lastDrop)
                lastDrop->showLight(false);
        }
        lastDrop = drop;
    }
}

void CollectionBox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!selectedProp)
        return;
    selectedProp->unselecte();
    
    if (!touchMoved && !rules->pickProp(selectedProp)) {
        showProp(selectedProp);
    }
    else if (!boxBackground->boundingBox().containsPoint(pTouch->getLocation()) &&
             rules->canDragOut(selectedProp)) {
        hide();
        rules->dragOut(selectedProp);
        if (!selectedProp->isVisible()) {
            selectedProp->removeFromParentAndCleanup(true);
            this->props->removeObject(selectedProp);
            relayoutProps();
        }
    }
    else {
        Prop *drop = propWithTouch(pTouch);
        if (drop) {
            if (rules->canMerge(drop, selectedProp)) {
                drop->showLight(false);
                selectedProp->showLight(false);
                Prop *p = rules->merge(drop, selectedProp);
                if (p) {
                    p->setPosition(drop->getPosition());
                    unsigned int idx = this->props->indexOfObject(drop);
                    this->props->replaceObjectAtIndex(idx, p);
                    this->props->removeObject(selectedProp);
                    boxBackground->removeChild(drop, true);
                    boxBackground->removeChild(selectedProp, true);
                    boxBackground->addChild(p);
                    relayoutProps();
                    goto EXIT;
                }
            }
        }
        
        CCMoveTo *move = CCMoveTo::create(0.3, lastLocation);
        CCEaseOut *ease = CCEaseOut::create(move, 1.5);
        selectedProp->runAction(ease);
    }
    
EXIT:
    selectedProp = NULL;
}

void CollectionBox::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (selectedProp)
        selectedProp->unselecte();
    selectedProp = NULL;
}
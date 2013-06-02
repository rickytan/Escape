//
//  Collections.cpp
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#include "Collections.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

static Collections *theInstance = NULL;

static struct {
    float growAnimationTime = 0.3;
    float scaleRate = 1.25;
}CONFIG;

Collections *Collections::sharedCollections()
{
    if (!theInstance) {
        theInstance = new Collections;
        if (!theInstance->init()) {
            delete theInstance;
            theInstance = NULL;
        }
    }
    return theInstance;
}


Collections::Collections()
:displayLayer(NULL)
,isShownCollections(false)
,collectionBag(CCMenuItemImage::create("bag.png", NULL,this,menu_selector(Collections::onBag)))
,collectionDisplayBox(NULL)
,collectionDisplayMode(kCollectionDisplayNone)
{

}

Collections::~Collections()
{
    items->release();
    items = NULL;
    delete theInstance;
    theInstance = NULL;
}

bool Collections::init()
{
    if (!CCLayer::init())
        return false;
    
    items = CCArray::createWithCapacity(10);
    items->retain();
    
    CCMenu *menu = CCMenu::createWithItem(collectionBag);
    menu->setPosition(CCPointZero);
    addChild(menu);
    
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("zipper.m4a");
    
    return true;
}

void Collections::growSprite(cocos2d::CCSprite *sprite)
{
    
}

void Collections::shrinkSprite(cocos2d::CCSprite *sprite)
{
    
}

void Collections::onBag(cocos2d::CCObject *sender)
{
    if (isShownCollections) {
        hideCollections();
        isShownCollections = false;
    }
    else {
        showCollections();
        isShownCollections = true;
    }
}

void Collections::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

bool Collections::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (collectionDisplayMode == kCollectionDisplayBagOnly) {
        if (collectionBag->boundingBox().containsPoint(pTouch->getLocation())) {
            selectedSprite = collectionBag;
        }
    }

    //growSprite(selectedSprite);
    
    if (isShownCollections)
        return false;
    
    return true;
}
/*
void Collections::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSprite *sprite = NULL;
    if (collectionDisplayMode == kCollectionDisplayBagOnly) {
        if (collectionBag->boundingBox().containsPoint(pTouch->getLocation())) {
            sprite = collectionBag;
        }
    }
    
    if (sprite != selectedSprite) {
        shrinkSprite(selectedSprite);
        selectedSprite = sprite;
        growSprite(selectedSprite);
    }
}

void Collections::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    shrinkSprite(selectedSprite);
    
    if (selectedSprite == collectionBag) {
        showCollections();
    }
    else {
        
    }
    
    selectedSprite = NULL;
}

void Collections::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    shrinkSprite(selectedSprite);
    
    selectedSprite = NULL;
}
*/
void Collections::restore()
{
    collectionBag->setVisible(false);
}

void Collections::displayInLayer(cocos2d::CCLayer *layer)
{
    displayLayer = layer;
    collectionDisplayMode = kCollectionDisplayBagOnly;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    collectionBag->setPosition(ccp(size.width - collectionBag->getContentSize().width/2,
                                   collectionBag->getContentSize().height/2));
    collectionBag->setScale(0.0);
    collectionBag->setVisible(true);
    
    CCScaleTo *scale = CCScaleTo::create(1.0,.5);
    CCAction *back = CCEaseBackOut::create(scale);
    collectionBag->runAction(back);
    
    setTouchEnabled(true);
    
    displayLayer->addChild(this, 100);
}

void Collections::removeDisplay()
{
    setTouchEnabled(false);
    displayLayer = NULL;
    this->removeFromParentAndCleanup(false);
}

void Collections::showCollections()
{
    if (collectionDisplayBox)
        return;
    
    collectionDisplayBox = CollectionBox::createWithProps(items);
    
    
    collectionDisplayMode = kCollectionDisplayItems;
}

void Collections::hideCollections()
{

   
}

void Collections::clearUpCallback(cocos2d::CCNode *node)
{
    node->removeFromParentAndCleanup(true);
}

void Collections::showItem(Prop *item)
{
    
}

void Collections::showItemAtIndex(int idx)
{
    showItem((Prop*)items->objectAtIndex(idx));
}

void Collections::removeSpriteCallback(CCNode *sprite)
{
    this->items->addObject(sprite);
    
    sprite->setPosition(CCPointZero);
    sprite->removeFromParentAndCleanup(false);
    SimpleAudioEngine::sharedEngine()->playEffect("zipper.m4a");
}

void Collections::addItem(Prop *item)
{
    CCSprite *sprite = (CCSprite*)item;

    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint p = collectionBag->getPosition();

    CCPoint c = sprite->getPosition();
    ccBezierConfig bc = {
        p,
        ccp((p.x+c.x)/2,size.height/2),
        ccp(p.x/4+c.x*3/4,size.height/2)
    };
    CCBezierTo *bezier = CCBezierTo::create(1.5, bc);
    CCEaseInOut *ease = CCEaseInOut::create(bezier, 2.3);
    CCActionInterval *scale = CCScaleBy::create(1.5, 0.6);
    CCCallFuncN *call = CCCallFuncN::create(this, callfuncN_selector(Collections::removeSpriteCallback));
    
    sprite->runAction(CCSpawn::createWithTwoActions(CCSequence::createWithTwoActions(ease, call),
                                                    scale));
    
    if (isShownCollections) {
        
    }
}
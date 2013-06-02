//
//  Collections.h
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#ifndef __Escape__Collections__
#define __Escape__Collections__

#include "cocos2d.h"
#include "CollectionBox.h"
#include "Prop.h"

USING_NS_CC;

class Collections : public CCLayer
{
private:
    CCArray                 * items;
    CCLayer                 * displayLayer;
    bool                      isShownCollections;
    CCMenuItemImage         * collectionBag;
    CCNode                  * selectedSprite;
    CollectionBox           * collectionDisplayBox;
    enum {
        kCollectionDisplayNone = 0,
        kCollectionDisplayBagOnly,
        kCollectionDisplayItems,
        kCollectionDisplayItemDetail
    }collectionDisplayMode;
    
    struct {
        unsigned int isGrowing:1;
        unsigned int isShrinking:1;
    } animatingFlags;
    
    Collections();
    bool init();
    void restore();
    
    void removeSpriteCallback(CCNode *sprite);
    void clearUpCallback(CCNode *node);
    
    void onBag(CCObject *sender);
    
    void growSprite(CCSprite *sprite);
    void shrinkSprite(CCSprite *sprite);
    
    void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    /*
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
     */
public:
    ~Collections();
    void displayInLayer(CCLayer* layer);
    void removeDisplay();
    void showCollections();
    void hideCollections();
    void showItem(Prop *p);
    void showItemAtIndex(int idx);
    void addItem(Prop *p);
    static Collections *sharedCollections(void);
};

#endif /* defined(__Escape__Collections__) */

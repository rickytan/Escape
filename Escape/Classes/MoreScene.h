//
//  MoreScene.h
//  Escape
//
//  Created by ricky on 12-12-24.
//
//

#ifndef __Escape__MoreScene__
#define __Escape__MoreScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class More : public CCLayer
{

    virtual void onStartPlay(CCObject *sender);
    
    virtual void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    }
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
        CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInL>(1.2);
        return true;
    }
    
public:
    virtual bool init();
    static CCScene *scene();
    CREATE_FUNC(More);
};

#endif /* defined(__Escape__MoreScene__) */

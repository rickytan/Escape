//
//  End.h
//  Escape
//
//  Created by ricky on 12-12-19.
//
//

#ifndef __Escape__End__
#define __Escape__End__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class End : public CCLayer
{
    CCSprite                * bgimage;
    
    enum {
        kEndStateSlide1,
        kEndStateEndText
    } state;
    
    int                       textIndex;
    CCLayer                 * scriptLayer;
    CCSprite                * subtitleBar;
    CCLabelTTF              * scriptText;
    CCLabelTTF              * endingText;
    
    CCString                * endingString;
    int                       endingStringIndex;
    
    CCSprite                * blackman;
    
    void showText();
    void showSlide();
    void loadSlide();
    void showSlideText();
    void showSlide1();
    void loadSlide1();
    void showEndingText();
    void showEndingText1();
    
    void enableTouch() {
        setTouchEnabled(true);
    }

    virtual void onEnterTransitionDidFinish();
    virtual void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    }
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
        switch (state) {
            case kEndStateSlide1:
                bgimage->runAction(CCSequence::create
                                   (
                                    CCFadeOut::create(0.6),
                                    CCHide::create(),
                                    CCCallFunc::create(this, callfunc_selector(End::showEndingText)),
                                    NULL
                                    ));
                setTouchEnabled(false);
                break;
            case kEndStateEndText:
                
                CCDirector::sharedDirector()->popToRootScene();
                break;
            default:
                break;
        }
        return true;
    }
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
        setTouchEnabled(false);
    }
    
public:
    virtual bool init();
    static CCScene* scene();
    
    CREATE_FUNC(End);
};

#endif /* defined(__Escape__End__) */

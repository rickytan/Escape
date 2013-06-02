//
//  MainMenuScene.h
//  Escape
//
//  Created by ricky on 12-12-6.
//
//

#ifndef __Escape__MainMenuScene__
#define __Escape__MainMenuScene__

#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public cocos2d::CCLayer
{
private:
    //CCMenu              * menu;
    CCSprite              * cube;
    CCSprite              * logo;
    
    // a selector callback
    void menuContinueCallback(CCObject* pSender);
    void menuMoreCallback(CCObject* sender);
    void menuNewCallback(CCObject* sender);
    
    void showBgAndMenu();
    
    void playCube();
    void playLogo();
    
    virtual void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    }
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
        cube->stopAllActions();
        cube->setVisible(false);
        showBgAndMenu();
        return true;
    }
    
public:
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainMenu);
};

#endif /* defined(__Escape__MainMenuScene__) */

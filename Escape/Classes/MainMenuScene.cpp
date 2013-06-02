//
//  MainMenuScene.cpp
//  Escape
//
//  Created by ricky on 12-12-6.
//
//

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "StarterScene.h"
#include "MoreScene.h"
#include "End.h"
#include "Level6.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene *MainMenu::scene()
{
    CCScene *s = CCScene::create();
    MainMenu *menu = MainMenu::create();
    s->addChild(menu);
    return s;
}

bool MainMenu::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("logo-anim0.plist");
    cache->addSpriteFramesWithFile("logo-anim1.plist");
    cache->addSpriteFramesWithFile("logo-anim2.plist");
    cache->addSpriteFramesWithFile("cube-anim0.plist");
    cache->addSpriteFramesWithFile("cube-anim1.plist");
    
    playLogo();
    
    return true;
}

void MainMenu::menuNewCallback(cocos2d::CCObject *sender)
{
    CCTransitionScene *tran = CCTransitionCrossFade::create(1.2, Starter::scene());
    CCDirector::sharedDirector()->pushScene(tran);
}

void MainMenu::menuContinueCallback(cocos2d::CCObject *sender)
{
    
}

void MainMenu::menuMoreCallback(cocos2d::CCObject *sender)
{
    //CCApplication::sharedApplication()->openURL("http://tougi.taobao.com/");
    CCDirector::sharedDirector()->pushScene(CCTransitionSlideInR::create(1.2, More::scene()));
}

void MainMenu::showBgAndMenu()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCPoint c = ccpMult(ccpFromSize(s), 0.5);

    
    CCSprite *bg = CCSprite::create("openingbackground.png");
    bg->setPosition(c);
    bg->setOpacity(0);
    addChild(bg, -1);
    
    bg->runAction(CCFadeIn::create(0.3));
    /*
     CCMenuItemImage *cont = CCMenuItemImage::create("continue-b.png", "continue.png");
     cont->setTarget(this, menu_selector(MainMenu::menuContinueCallback));
     */
    CCMenuItemImage *more = CCMenuItemImage::create("more.png", "more-b.png");
    more->setTarget(this, menu_selector(MainMenu::menuMoreCallback));
    
    CCMenuItemImage *newgame = CCMenuItemImage::create("newgame.png", "newgame-b.png");
    newgame->setTarget(this, menu_selector(MainMenu::menuNewCallback));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu *menu = CCMenu::create(newgame,more,NULL);
    menu->alignItemsVerticallyWithPadding(10);
    menu->setPosition(ccp(size.width/2, size.height/2-50));
    
    this->addChild(menu);
    
    setTouchEnabled(false);
}


void MainMenu::playLogo()
{
    float animInterval = 0.05f;
    
    CCArray *frames = CCArray::createWithCapacity(100);
    char filename[64] = {0};
    for (int i=1; i<=100; ++i) {
        sprintf(filename, "logo%04d.png",i);
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename));
    }
    
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(frames);
    anim->setDelayPerUnit(animInterval);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    logo = CCSprite::createWithSpriteFrameName("logo0001.png");
    logo->setPosition(ccp(size.width/2,size.height/2));
    addChild(logo);
    
    logo->runAction(CCSequence::create
                    (
                     CCAnimate::create(anim),
                     CCFadeOut::create(0.3),
                     CCHide::create(),
                     CCCallFunc::create(this, callfunc_selector(MainMenu::playCube)),
                     NULL
                    ));
}

void MainMenu::playCube()
{
    logo->removeFromParentAndCleanup(true);
    logo = NULL;
    
    
    float animInterval = 0.04f;
    
    setTouchEnabled(true);
    
    CCArray *frames = CCArray::createWithCapacity(145);
    char filename[64] = {0};
    for (int i=1; i<=145; ++i) {
        sprintf(filename, "CUBE%04d.png",i);
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename));
    }
    
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(frames);
    anim->setDelayPerUnit(animInterval);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    cube = CCSprite::createWithSpriteFrameName("CUBE0001.png");
    cube->setPosition(ccp(size.width/2,size.height/2));
    addChild(cube);
    
    cube->runAction(CCSequence::create
                    (
                     CCAnimate::create(anim),
                     CCCallFunc::create(this, callfunc_selector(MainMenu::showBgAndMenu)),
                     CCFadeOut::create(0.3),
                     CCHide::create(),
                     NULL
                     ));
}
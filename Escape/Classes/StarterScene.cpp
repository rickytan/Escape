//
//  StarterScene.cpp
//  Escape
//
//  Created by ricky on 12-12-9.
//
//

#include "StarterScene.h"
#include "SimpleAudioEngine.h"
#include "Level1.h"
#include "MissionTransactionScene.h"


using namespace cocos2d;
using namespace CocosDenshion;

static struct {
    float delay_time = 1.5f;
    float fade_time = 0.2f;
    string font_name = "Thonburi";
    float font_size = 16.0f;
    float text_margin = 6.0f;
    string subtitles[4] = {
        "这是哪里？？我为什么会在这里？？？",
        "",
        "电话按键音。。。。。滴。。。。。滴。。。。。。。",
        "求你们帮帮我，我被困这里，可能只有你们能够帮到我，求求你们！"
    };
}APP_CONFIG;

CCScene *Starter::scene()
{
    CCScene *scene = CCScene::create();
    Starter *starter = Starter::create();
    scene->addChild(starter);
    return scene;
}

bool Starter:: init()
{
    if (!CCLayer::init())
        return false;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    bgLayer = CCLayer::create();
    this->addChild(bgLayer, -1);
    
    scriptLayer = CCLayer::create();
    this->addChild(scriptLayer, 1);
    
    subtitleBar = CCSprite::create("subtitlebar.png");
    subtitleBar->setAnchorPoint(ccp(0.5, 0));
    subtitleBar->setPosition(ccp(size.width/2, 0));
    subtitleBar->setVisible(false);
    scriptLayer->addChild(subtitleBar);
    
    scriptText = CCLabelTTF::create("", APP_CONFIG.font_name.c_str(), APP_CONFIG.font_size);
    scriptText->setAnchorPoint(ccp(0, 1));
    scriptText->setDimensions(CCSizeMake(subtitleBar->boundingBox().size.width - APP_CONFIG.text_margin*2,
                                         subtitleBar->boundingBox().size.height - APP_CONFIG.text_margin*2));
    scriptText->setHorizontalAlignment(kCCTextAlignmentLeft);
    scriptText->setPosition(ccp(APP_CONFIG.text_margin,
                                subtitleBar->boundingBox().size.height - APP_CONFIG.text_margin));

    subtitleBar->addChild(scriptText);
    
    bgImage = NULL;
    
    currentPage = 0;
    
    //setTouchEnabled(true);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("phone-dial.m4a");
    SimpleAudioEngine::sharedEngine()->preloadEffect("phone-wait.m4a");

    return true;
}

void Starter::onEnterTransitionDidFinish()
{
    CCDelayTime *delay = CCDelayTime::create(1.0);
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(Starter::showCurrentPage));
    CCDelayTime *delay1 = CCDelayTime::create(4.0);
    CCCallFunc *call1 = CCCallFunc::create(this, callfunc_selector(Starter::nextPage));
    
    runAction(CCSequence::create(delay, call,CCRepeat::create(CCSequence::create(delay1,call1,NULL), 4),NULL));
}

void Starter::showCurrentPage()
{
    showPage(currentPage);
}

void Starter::showPage(int page)
{
    if (bgImage) {
        bgImage->runAction(CCFadeOut::create(APP_CONFIG.fade_time));
    }
    
    bgImage = CCSprite::create(CCString::createWithFormat("prologue%d.jpg",page+1)->getCString());
    bgImage->runAction(CCFadeIn::create(APP_CONFIG.fade_time));
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    bgImage->setPosition(ccp(size.width/2, size.height/2));
    
    bgLayer->addChild(bgImage);
    
    if (page == 1)
        subtitleBar->setVisible(false);
    else {
        scriptText->setString(APP_CONFIG.subtitles[page].c_str());
        scriptText->setOpacity(0);
        scriptText->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(APP_CONFIG.delay_time),
                                                               CCFadeIn::create(APP_CONFIG.fade_time)));
        subtitleBar->setVisible(true);
        subtitleBar->setOpacity(0);
        subtitleBar->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(APP_CONFIG.delay_time),
                                                                CCFadeIn::create(APP_CONFIG.fade_time)));
    }
    
    if (page == 2) {
        CCDelayTime *delay = CCDelayTime::create(0.5f);
        CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(Starter::playDial));
        this->runAction(CCSequence::createWithTwoActions(delay, call));
    }
}

void Starter::nextPage()
{
    ++currentPage;
    if (currentPage < 4)
        showPage(currentPage);
    else {
        CCTransitionScene *flip = CCTransitionCrossFade::create(0.6, MissionTransaction::sceneWithTextandNextScene("第一关", Level1::scene()));
        CCDirector::sharedDirector()->replaceScene(flip);
    }
}

void Starter::playDial()
{
    SimpleAudioEngine::sharedEngine()->playEffect("phone-dial.m4a");
    
    CCDelayTime *delay = CCDelayTime::create(2.0f);
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(Starter::playWait));
    this->runAction(CCSequence::createWithTwoActions(delay, call));
}

void Starter::playWait()
{
    SimpleAudioEngine::sharedEngine()->playEffect("phone-wait.m4a");
}

void Starter::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    this->stopAllActions();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void Starter::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    nextPage();
}
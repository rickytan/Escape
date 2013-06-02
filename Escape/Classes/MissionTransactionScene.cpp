//
//  MissionTransactionScene.cpp
//  Escape
//
//  Created by ricky on 12-12-11.
//
//

#include "MissionTransactionScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

CCScene* MissionTransaction::sceneWithTextandNextScene(std::string text, cocos2d::CCScene *nextScene)
{
    CCScene *scene = CCScene::create();
    MissionTransaction *m = MissionTransaction::createWithText(text);
    m->setNextScene(nextScene);
    scene->addChild(m);
    return scene;
}

MissionTransaction* MissionTransaction::createWithText(const char *text)
{
    MissionTransaction* mission = new MissionTransaction;
    if (mission && mission->initWithText(text)) {
        mission->autorelease();
        return mission;
    }
    else {
        delete mission;
        mission = NULL;
        return NULL;
    }
}

MissionTransaction* MissionTransaction::createWithText(cocos2d::CCString *text)
{
    return createWithText(text->getCString());
}

MissionTransaction* MissionTransaction::createWithText(std::string text)
{
    return createWithText(text.c_str());
}

MissionTransaction::MissionTransaction()
:nextScene(NULL)
,textLabel(NULL)
{
}

MissionTransaction::~MissionTransaction()
{

}

bool MissionTransaction::initWithText(const char *text)
{
    if (!CCLayerColor::init())
        return false;

    this->setColor(ccRED);

        
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLayer *bg = CCLayer::create();
    bg->setPosition(ccp(s.width/2, s.height/2));
    addChild(bg);
    
    textLabel = CCLabelTTF::create(text, "Fixedsys.ttf", 64);
    textLabel->setPosition(ccp(s.width, 0));
    
    bg->addChild(textLabel);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("foot.m4a");
    
    return true;
}

void MissionTransaction::onEnterTransitionDidFinish()
{
    CCLayerColor::onEnterTransitionDidFinish();
    
    SimpleAudioEngine::sharedEngine()->playEffect("foot.m4a");
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCMoveTo *moveCenter = CCMoveTo::create(1.2, ccp(0, 0));
    CCActionEase *easeIn = CCEaseElasticOut::create(moveCenter);
    CCDelayTime *delay = CCDelayTime::create(0.8);
    CCMoveTo *moveOut = CCMoveTo::create(1.2, ccp(-s.width, 0));
    CCActionEase *easeOut = CCEaseBackIn::create(moveOut);
    CCEaseIn *ease = CCEaseIn::create(easeOut, 3);
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(MissionTransaction::gotoNextScene));
    
    textLabel->runAction(CCSequence::create(easeIn,delay,ease,call,NULL));
}

void MissionTransaction::gotoNextScene()
{
    CCTransitionScene *tran = CCTransitionFade::create(0.6, nextScene);
    CCDirector::sharedDirector()->replaceScene(tran);
}

void MissionTransaction::setNextScene(cocos2d::CCScene *scene)
{
    if (nextScene)
        nextScene->release();
    nextScene = scene;
    nextScene->retain();
}
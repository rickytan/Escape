//
//  SafeBoxScene.cpp
//  Escape
//
//  Created by ricky on 12-12-10.
//
//

#include "Level1.h"
#include "Level2.h"
#include "SimpleAudioEngine.h"
#include "MissionTransactionScene.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


CCScene *Level1::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(Level1::create());
    return scene;
}

bool Level1::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *bg = CCSprite::create("safe.png");
    bg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bg);
    
    mapImage = CCSprite::create("map.png");
    mapImage->setVisible(false);
    CCPoint center = ccpMult(ccpFromSize(size), 0.5);
    mapImage->setPosition(center);
    this->addChild(mapImage);
    
    CCMenuItemImage *mapItem = CCMenuItemImage::create("normal.png", NULL);
    //mapItem->setContentSize(CCSizeMake(120, 80));
    mapItem->setPosition(ccp(-64,6));
    mapItem->setScale(1.7);
    mapItem->setTarget(this, menu_selector(Level1::onMap));
    
    CCMenuItemImage *codeItem = CCMenuItemImage::create("normal.png", NULL);
    //codeItem->setContentSize(CCSizeMake(80, 80));
    codeItem->setPosition(ccp(66,4));
    codeItem->setScaleX(1.5);
    codeItem->setScaleY(2.0);
    codeItem->setTarget(this, menu_selector(Level1::onCode));
    
    menu = CCMenu::create(mapItem, codeItem, NULL);
    this->addChild(menu);
    
    setTouchEnabled(true);
    
    return true;
}


void Level1::onCode(cocos2d::CCObject *sender)
{
    CCScene *transition = CCTransitionCrossFade::create(0.6, CodeInput::scene());
    CCDirector::sharedDirector()->pushScene(transition);
}

void Level1::onMap(cocos2d::CCObject *sender)
{
    if (mapImage->isVisible())
        return;
    
    menu->setEnabled(false);
    showMap();
}

void Level1::showMap()
{
    mapImage->setScale(0.2);
    mapImage->setOpacity(0xff);
    
    CCScaleTo *scale = CCScaleTo::create(1.0, 1.0);
    CCEaseElasticOut *elastic = CCEaseElasticOut::create(scale);
    
    mapImage->runAction(CCSequence::create
                        (
                         CCShow::create(),
                         elastic,
                         NULL
                         ));
}

void Level1::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (!mapImage->isVisible())
        return;
    menu->setEnabled(true);
    mapImage->runAction(CCSequence::create
                        (
                         CCFadeOut::create(0.35),
                         CCHide::create(),
                         NULL
                         ));
}


CCScene* CodeInput::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(CodeInput::create());
    return scene;
}

bool CodeInput::init()
{
    if (!CCLayer::init())
        return false;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *codelock = CCSprite::create("codelock.png");
    codelock->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(codelock);
    
    CCPoint loc[] = {
        CCPoint(-69,42),
        CCPoint(0,42),
        CCPoint(65,42),
        CCPoint(-69,2),
        CCPoint(0,2),
        CCPoint(65,2),
        CCPoint(-69,-38),
        CCPoint(0,-38),
        CCPoint(65,-38),
        CCPoint(-69,-78),
        CCPoint(0,-78),
        CCPoint(65,-78)
    };
    CCArray *array = CCArray::createWithCapacity(12);
    for (int i=0; i<12; ++i) {
        CCMenuItemImage *item = CCMenuItemImage::create("normal.png", "highlight.png");
        item->setTarget(this, menu_selector(CodeInput::onButton));
        item->setPosition(loc[i]);
        item->setTag(i);
        array->addObject(item);
    }
    
    CCMenu *menu = CCMenu::createWithArray(array);
    this->addChild(menu);
    
    codeLabel = CCLabelTTF::create("", "Fixedsys.ttf", 28);
    codeLabel->setHorizontalAlignment(kCCTextAlignmentRight);
    codeLabel->setAnchorPoint(ccp(1, 0.5));
    codeLabel->setPosition(ccp(size.width/2 + 244.0/2, size.height - 71));
    codeLabel->setColor(ccGREEN);
    this->addChild(codeLabel);
    
    codeString = "";
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("code-button.m4a");
    
    return true;
}


void CodeInput::playButtonSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("code-button.m4a");
}

void CodeInput::confirm()
{
    if ("20110920" == codeString) {
        CCLOG("Yes, code passed!");
        CCTransitionScene *tran = CCTransitionCrossFade::create(0.6, MissionTransaction::sceneWithTextandNextScene("第二关", Level2::scene()));
        CCDirector::sharedDirector()->replaceScene(tran);
    }
    else {
        isBlinking = true;
        CCBlink *blink = CCBlink::create(.6, 3);
        CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(CodeInput::clearCode));
        codeLabel->runAction(CCSequence::createWithTwoActions(blink, call));
    }
}

void CodeInput::clearCode()
{
    isBlinking = false;
    codeString = "";
    updateCodeLabel();
}

void CodeInput::updateCodeLabel()
{
    codeLabel->setString(codeString.c_str());
}

void CodeInput::onButton(cocos2d::CCObject *sender)
{
    if (isBlinking)
        return;
    
    
    playButtonSound();
    
    
    CCNode *item = (CCNode*)sender;
    switch (item->getTag()) {
        case 9:     // back
            CCDirector::sharedDirector()->popScene();
            break;
        case 10:    // 0
            if (codeString.length() >= 16)
                break;
            codeString += '0';
            updateCodeLabel();
            break;
        case 11:
            confirm();
            break;
        case 0:case 1:case 2:case 3:case 4:
        case 5:case 6:case 7:case 8:
            if (codeString.length() >= 16)
                break;
            codeString += ('1'+item->getTag());
            updateCodeLabel();
            break;
        default:
            break;
    }
}



CCScene* WordInput::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(WordInput::create());
    return scene;
}

bool WordInput::init()
{
    if (!CCLayer::init())
        return false;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *codelock = CCSprite::create("A-Zcodeenter.png");
    codelock->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(codelock);
    
    int row[] = {10,9,7};
    float leading[] = {0,18,0};
    char buttons[] = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m',0x0,0x1};
    int count = 0;
    CCArray *array = CCArray::createWithCapacity(28);
    for (int i=0; i<3; ++i) {
        for (int j=0; j<row[i]; ++j) {
            CCMenuItemImage *item = CCMenuItemImage::create("A-Znormal.png", "A-Zhighlight.png");
            item->setTarget(this, menu_selector(WordInput::onButton));
            item->setPosition(ccp(35.2*j + 16 + leading[i], 160 - (37.0*i + 18)));
            item->setTag(buttons[count++]);
            array->addObject(item);
        }
    }
    
    CCMenuItemImage *item = CCMenuItemImage::create("A-Znormal.png", "A-Zhighlight.png");
    item->setTarget(this, menu_selector(WordInput::onButton));
    item->setPosition(ccp(35.2*7 + 16 + 10, 160 - (38.0*2 + 16)));
    item->setScaleX(1.6);
    item->setTag(buttons[count++]);
    array->addObject(item);
    
    item = CCMenuItemImage::create("A-Znormal.png", "A-Zhighlight.png");
    item->setTarget(this, menu_selector(WordInput::onButton));
    item->setPosition(ccp(35.2*7 + 16 + 61, 160 - (38.0*2 + 16)));
    item->setScaleX(1.6);
    item->setTag(buttons[count++]);
    array->addObject(item);
    
    
    CCMenu *menu = CCMenu::createWithArray(array);
    menu->setPosition(ccp(63.5,34));
    this->addChild(menu);
    
    codeLabel = CCLabelTTF::create("", "Fixedsys.ttf", 28);
    codeLabel->setHorizontalAlignment(kCCTextAlignmentRight);
    codeLabel->setAnchorPoint(ccp(1, 0.5));
    codeLabel->setPosition(ccp(size.width/2 + 144, size.height - 100));
    codeLabel->setColor(ccGREEN);
    this->addChild(codeLabel);
    
    codeString = "";
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("code-button.m4a");
    
    return true;
}


void WordInput::playButtonSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("code-button.m4a");
}

void WordInput::confirm()
{
    
    isBlinking = true;
    CCBlink *blink = CCBlink::create(.6, 3);
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(WordInput::clearCode));
    codeLabel->runAction(CCSequence::createWithTwoActions(blink, call));
}

void WordInput::clearCode()
{
    isBlinking = false;
    codeString = "";
    updateCodeLabel();
}

void WordInput::updateCodeLabel()
{
    codeLabel->setString(codeString.c_str());
}

void WordInput::onButton(cocos2d::CCObject *sender)
{
    if (isBlinking)
        return;
    
    
    playButtonSound();
    
    
    CCNode *item = (CCNode*)sender;
    switch (item->getTag()) {
        case 0:     // back
            CCDirector::sharedDirector()->popScene();
            break;
        case 1:    // enter
            confirm();
            break;
        default:
        {
            if (item->getTag() >= 'a' && item->getTag() <= 'z') {
                codeString += (char)item->getTag();
                updateCodeLabel();
            }
        }
            break;
    }
}

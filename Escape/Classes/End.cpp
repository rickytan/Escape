//
//  End.cpp
//  Escape
//
//  Created by ricky on 12-12-19.
//
//

#include "End.h"

using namespace std;

static struct {
    float delay_time = 1.5f;
    float fade_time = 0.2f;
    string font_name = "Fixedsys.ttf";
    float font_size = 20.0f;
    float text_margin = 6.0f;
    string subtitles[4] = {
        "我终于出来了！！！",
        "等等…………",
        "不~~~~！！！！！！"
    };
}APP_CONFIG;

CCScene* End::scene()
{
    CCScene *s = CCScene::create();
    s->addChild(End::create());
    return s;
}

bool End::init()
{
    if (!CCLayer::init())
        return false;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    bgimage = CCSprite::create("end.png");
    bgimage->setPosition(ccp(size.width/2, size.height/2));
    bgimage->setOpacity(0);
    addChild(bgimage,-1);
    
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
    
    return true;
}

void End::onEnterTransitionDidFinish()
{
    bgimage->runAction(CCFadeIn::create(0.3));
    
    
    textIndex = 0;
    runAction(CCSequence::create(CCRepeat::create(
                                                  CCSequence::create
                                                  (
                                                   CCCallFunc::create(this,callfunc_selector(End::showText)),
                                                   CCDelayTime::create(3.0),
                                                   NULL
                                                  ),3),
                                 CCCallFunc::create(this, callfunc_selector(End::showSlide)),
                                 NULL));
}

void End::showText()
{
    
    scriptText->setString(APP_CONFIG.subtitles[textIndex++].c_str());
    scriptText->setOpacity(0);
    scriptText->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(APP_CONFIG.delay_time),
                                                           CCFadeIn::create(APP_CONFIG.fade_time)));
    subtitleBar->setVisible(true);
    subtitleBar->setOpacity(0);
    subtitleBar->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(APP_CONFIG.delay_time),
                                                            CCFadeIn::create(APP_CONFIG.fade_time)));
    
}

void End::showSlide()
{
    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(0, 0, 0, 0));
    addChild(colorLayer,2);
    
    colorLayer->runAction(CCSequence::create
                          (
                           CCFadeIn::create(0.6),
                           CCCallFunc::create(this, callfunc_selector(End::loadSlide)),
                           CCFadeOut::create(0.6),
                           CCHide::create(),
                           CCCallFunc::create(this, callfunc_selector(End::showSlideText)),
                           NULL
                          ));
}

void End::loadSlide()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("endslide.png");
    bgimage->setTexture(texture);
    
    blackman = CCSprite::create("blackman.png");
    blackman->setPosition(ccp(size.width/2, size.height/2));
    addChild(blackman);
    scriptText->setOpacity(0);
    subtitleBar->setVisible(true);
    subtitleBar->setOpacity(0);
}

void End::showSlideText()
{
    
    scriptText->setString("我知道我在哪里了，这里是EXIT-Club总部，快来救我！");
    scriptText->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(APP_CONFIG.delay_time),
                                                           CCFadeIn::create(APP_CONFIG.fade_time)));
    subtitleBar->runAction(CCSequence::create(CCDelayTime::create(APP_CONFIG.delay_time),
                                              CCFadeIn::create(APP_CONFIG.fade_time),
                                              CCDelayTime::create(3.0),
                                              CCCallFunc::create(this, callfunc_selector(End::showSlide1)),
                                              NULL
                                              ));
}

void End::showSlide1()
{

    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(0, 0, 0, 0));
    addChild(colorLayer,2);
    
    colorLayer->runAction(CCSequence::create
                          (
                           CCFadeIn::create(0.6),
                           CCCallFunc::create(this, callfunc_selector(End::loadSlide1)),
                           CCFadeOut::create(0.6),
                           CCDelayTime::create(4.0),
                           CCHide::create(),
                           CCCallFunc::create(this, callfunc_selector(End::enableTouch)),
                           NULL
                          ));
}

void End::loadSlide1()
{
    blackman->setVisible(false);
    scriptText->setVisible(false);
    subtitleBar->setVisible(false);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("endslide2.png");
    bgimage->setTexture(texture);
    
    state = kEndStateSlide1;

}

void End::showEndingText()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    endingText = CCLabelTTF::create("THE END\n\n请来EXIT-Club\n改革月报9F领取奖品", "Thonburi", 36);
    endingText->setPosition(ccp(size.width/2,size.height/2));
    endingText->setDimensions(CCSizeMake(size.width - 60, size.height - 30));
    endingText->setHorizontalAlignment(kCCTextAlignmentCenter);
    endingText->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    
    scriptLayer->addChild(endingText,1);
    
    
    endingString = CCString::createWithFormat("代号X报告：\n       第一部分测试已经结束，所有实验对象通过测试，等待组织进一步指示！");
    endingString->retain();
    endingStringIndex = 0;
    
    runAction(CCSequence::create(CCDelayTime::create(2.4),CCCallFunc::create(this, callfunc_selector(End::showEndingText1)),NULL));
}

void End::showEndingText1()
{
    if (endingStringIndex == endingString->length()) {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *tobecontinued = CCLabelTTF::create("To Be Continued", "Thonburi", 36);
        tobecontinued->setAnchorPoint(ccp(1.0, 0.0));
        tobecontinued->setPosition(ccp(size.width, 0));
        tobecontinued->setOpacity(0);
        scriptLayer->addChild(tobecontinued,1);
        tobecontinued->runAction(CCFadeIn::create(0.3));
        state = kEndStateEndText;
        setTouchEnabled(true);
        return;
    }
    
    char text[256] = {0};
    unsigned char t = (endingString->getCString())[endingStringIndex];
    if ((t & 0xf0) == 0xf0)
        endingStringIndex += 4;
    else if ((t & 0xe0) == 0xe0)
        endingStringIndex += 3;
    else if ((t & 0xc0) == 0xc0)
        endingStringIndex += 2;
    else
        endingStringIndex += 1;
    strncpy(text, endingString->getCString(), endingStringIndex);
    text[endingStringIndex] = '\0';
    
    endingText->setString(text);
    endingText->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    endingText->setHorizontalAlignment(kCCTextAlignmentLeft);
    
    
    runAction(CCSequence::create(CCDelayTime::create(0.25),CCCallFunc::create(this, callfunc_selector(End::showEndingText1)),NULL));
}


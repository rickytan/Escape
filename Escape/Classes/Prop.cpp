//
//  Prop.cpp
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#include "Prop.h"
#include "Collections.h"

static const float GROW_SCALE_RATE = 1.25;
static const float GROW_DURIATION = 0.3;

enum {
    kProp_Selection_Animation_Tag = 101
};

Prop::Prop()
:collected(false)
,initScale(1.0)
,selected(false)
,description(NULL)
,spriteFile(NULL)
{
}

Prop::~Prop()
{
}

Prop* Prop::createWithFileAndInitScale(const char *file, float scale = 1.0)
{
    Prop *p = new Prop;
    if (p->initWithFileAndInitScale(file,scale)) {
        p->autorelease();
    }
    else {
        delete p;
        p = NULL;
    }
    return p;
}

bool Prop::initWithFileAndInitScale(const char *file, float scale = 1.0)
{
    if (!CCSprite::initWithFile(file))
        return false;
    light = CCSprite::create("light.png");
    light->setVisible(false);
    light->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
    this->addChild(light);
    
    spriteFile = CCString::createWithFormat(file);
    spriteFile->retain();
    initScale = scale;
    setScale(scale);
    return true;
}

bool Prop::isCollected()
{
    return collected;
}

void Prop::setCollected(bool val)
{
    collected = val;
}

void Prop::reset()
{
    this->showLight(false);
    this->setScale(initScale);
    this->setPosition(CCPointZero);
    this->setAnchorPoint(ccp(0.5,0.5));
}

void Prop::setDescription(cocos2d::CCString *text)
{
    if (description) {
        description->release();
    }
    description = text;
    description->retain();
}

void Prop::setDescription(const std::string &text)
{
    setDescription(text.c_str());
}

void Prop::setDescription(const char *text)
{
    if (description) {
        description->release();
    }
    description = CCString::createWithFormat(text);
    description->retain();
}

const char* Prop::getDescription()
{
    return description?description->getCString():"";
}

void Prop::showLight(bool show)
{
    light->setVisible(show);
}

void Prop::selecte()
{
    selected = true;
    getParent()->reorderChild(this, 2);

    stopActionByTag(kProp_Selection_Animation_Tag);

    CCActionInterval *scale = CCScaleTo::create(GROW_DURIATION, GROW_SCALE_RATE*initScale);
    CCActionInterval *back = CCEaseInOut::create(scale,1.5);
    back->setTag(kProp_Selection_Animation_Tag);
    runAction(back);
}

void Prop::unselecte()
{
    selected = false;
    getParent()->reorderChild(this, 0);
    
    stopActionByTag(kProp_Selection_Animation_Tag);
    
    CCActionInterval *scale = CCScaleTo::create(GROW_DURIATION, 1.0*initScale);
    CCActionInterval *back = CCEaseInOut::create(scale,1.5);
    runAction(back);
}

PropDetail* PropDetail::createWithProp(Prop *prod)
{
    PropDetail *pd = new PropDetail;
    pd->displayProp = prod;
    if (pd->init()) {
        pd->autorelease();
    }
    else {
        delete pd;
        pd = NULL;
    }
    return pd;
}

bool PropDetail::init()
{
    ccColor4B color = {0,0,0,128};
    if (!CCLayerColor::initWithColor(color))
        return false;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *textBg = CCSprite::create("textbg.png");
    textBg->setPosition(ccp(size.width/2, 40));
    addChild(textBg, -1);
    
    CCLabelTTF *label = CCLabelTTF::create(displayProp->getDescription(), "Fixedsys.ttf", 20);
    label->setHorizontalAlignment(kCCTextAlignmentCenter);
    label->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    label->setDimensions(CCSizeMake(textBg->getContentSize().width*textBg->getScaleX(),
                                    textBg->getContentSize().height*textBg->getScaleY()));
    label->setPosition(textBg->getPosition());
    addChild(label,3);
    
    return true;
}

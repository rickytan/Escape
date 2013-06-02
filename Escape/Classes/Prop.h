//
//  Prop.h
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#ifndef __Escape__Prop__
#define __Escape__Prop__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;


typedef enum {
    kProp_Type_Tag_CoffeBean = 200,
    kProp_Type_Tag_CoffeMachine,
    kProp_Type_Tag_CoffeCup,
    kProp_Type_Tag_Wheel,
    kProp_Type_Tag_Torch,
    kProp_Type_Tag_Fakeman,
    kProp_Type_Tag_CD,
    kProp_Type_Tag_Newspaper,
    kProp_Type_Tag_Stone
}PropType;

class Prop : public CCSprite
{
private:
    bool                      collected;
    bool                      selected;

    CCString                * spriteFile;
    CCString                * description;
    CCSprite                * light;
    Prop                    * reliedProp;
    

    
   /*
    virtual void setScale(float s) {
        CCSprite::setScale(s*initScale);
    }
    
    virtual void setScaleX(float sx) {
        CCSprite::setScaleX(sx*initScale);
    }

    
    virtual void setScaleY(float sy) {
        CCSprite::setScaleY(sy*initScale);
    }*/
    
    CC_SYNTHESIZE(PropType, proptype, Type);
    CC_SYNTHESIZE(float, initScale, InitScale);

public:
    Prop();
    ~Prop();
    
    Prop* copyWithZone(cocos2d::CCZone *pZone) {
        Prop *copy = Prop::createWithFileAndInitScale(spriteFile->getCString(), initScale);
        copy->setDescription(description);
        return copy;
    }
    static Prop* createWithFileAndInitScale(const char file[],float scale);
    bool initWithFileAndInitScale(const char file[],float scale);
    virtual void setDescription(CCString *text);
    virtual void setDescription(const std::string &text);
    virtual void setDescription(const char text[]);
    virtual const char *getDescription(void);

    virtual void reset();
    
    virtual void relyOn(Prop *prop) { reliedProp = prop; }
    virtual Prop* getReliedProp() { return reliedProp; }
    
    virtual void showLight(bool show);
    
    virtual void selecte();
    virtual void unselecte();
    
    virtual bool isCollected();
    virtual void setCollected(bool val);
};

class PropDetail : public CCLayerColor
{
private:
    Prop                * displayProp;
    
    void onEnter() {
        CCLayerColor::onEnter();
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        displayProp->setInitScale(1.0);
        displayProp->setScale(0.0);
        displayProp->setPosition(ccp(size.width/2, size.height-displayProp->getContentSize().height/2-15));
        displayProp->runAction(CCEaseBackOut::create(CCScaleTo::create(0.6, 1.0)));
        addChild(displayProp);
    }
    
public:

    
    virtual bool init();
    static PropDetail* createWithProp(Prop *);
};

#endif /* defined(__Escape__Prop__) */

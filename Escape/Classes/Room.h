//
//  Room.h
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#ifndef __Escape__Room__
#define __Escape__Room__

#include <iostream>
#include "cocos2d.h"
#include "Prop.h"
#include "SimpleAudioEngine.h"
#include "MissionTransactionScene.h"
#include "Level1.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "End.h"

USING_NS_CC;

using namespace CocosDenshion;

static const float ANIMATE_DURIATION = 1.0;
static const int ROOM_PROP_TAG = 55;

typedef void(CCObject::* SEL_roomPickProp)(Prop *p);

class Room : public CCLayer
{
private:
    
    void gotoLeftCallback() {
        hide();
        leftRoom->showFromLeft();
    }
    void gotRightCallback() {
        hide();
        rightRoom->showFromRight();
    }
    
    void handleShown() {
        menu->setEnabled(true);
    }
    
    void handleHidden() {
        
    }
    
    
protected:
    Room            * leftRoom;
    Room            * rightRoom;
    
    CCMenu          * menu;
    Prop            * prop;
    
    CCObject            * target;
    SEL_roomPickProp      selector;
    
    
    Room():leftRoom(NULL),rightRoom(NULL){
        this->setVisible(false);
    }
    
    void removeNodeCallback(CCNode *node) {
        node->removeFromParentAndCleanup(true);
    }
    
    
    virtual void onLeftDoor(CCObject *sender) {
        if (leftRoom) {
            menu->setEnabled(false);
            CCNode *n = (CCNode*)sender;
            n->runAction(CCFadeOut::create(0.3));
            CCAction *action = CCSequence::create
            (
             CCDelayTime::create(0.3),
             CCCallFunc::create(this, callfunc_selector(Room::gotoLeftCallback)),
             NULL
             );
            this->runAction(action);
            SimpleAudioEngine::sharedEngine()->playEffect("ele-door.m4a");
        }
    }
    virtual void onRightDoor(CCObject *sender) {
        if (rightRoom) {
            menu->setEnabled(false);
            CCNode *n = (CCNode*)sender;
            n->runAction(CCFadeOut::create(0.3));
            CCAction *action = CCSequence::create
            (
             CCDelayTime::create(0.3),
             CCCallFunc::create(this, callfunc_selector(Room::gotRightCallback)),
             NULL
             );
            this->runAction(action);
            SimpleAudioEngine::sharedEngine()->playEffect("ele-door.m4a");
        }
    }
    virtual void onMiddleDoor(CCObject *sender){}
    /*
     virtual void onEnterTransitionDidFinish();
     virtual void onExit();
     */
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        CCNode *n = getChildByTag(ROOM_PROP_TAG);
        if (n) {
            if (n->boundingBox().containsPoint(touch->getLocation())) {
                if (target && selector) {
                    (target->*selector)((Prop*)n);
                }
            }
        }
    }
public:
    virtual bool init();
    static CCScene *scene();
    
    CREATE_FUNC(Room);
    
    void setLeftRoom(Room* room);
    void setRightRoom(Room* room);
    
    void setPropDidPickTarget(CCObject *target, SEL_roomPickProp selector) {
        this->target = target;
        this->selector = selector;
    }
    
    Prop *getProp() {return prop;}
    
    void showFromLeft() {
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        show();
        menu->setEnabled(false);
        this->setPosition(ccp(-s.width, 0));
        CCMoveTo *move = CCMoveTo::create(ANIMATE_DURIATION, CCPointZero);
        CCActionInterval *ease = CCEaseInOut::create(move, 1.5);
        this->runAction(CCSequence::createWithTwoActions(ease, CCCallFunc::create(this, callfunc_selector(Room::handleShown))));
    }
    void showFromRight() {
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        show();
        menu->setEnabled(false);
        this->setPosition(ccp(s.width, 0));
        CCMoveTo *move = CCMoveTo::create(ANIMATE_DURIATION, CCPointZero);
        CCActionInterval *ease = CCEaseInOut::create(move, 1.5);
        this->runAction(CCSequence::createWithTwoActions(ease, CCCallFunc::create(this, callfunc_selector(Room::handleShown))));
    }
    void show() {
        this->getParent()->reorderChild(this, 0);
        CCMenuItemImage *n;
        CCObject *obj = NULL;
        CCARRAY_FOREACH(menu->getChildren(), obj) {
            n = (CCMenuItemImage*)obj;
            n->setOpacity(255);
            n->setVisible(true);
        }
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        
        CCLayerColor *l = CCLayerColor::create((ccColor4B){0,0,0,1});
        l->setTouchEnabled(true);
        this->addChild(l,2);
        CCAction *action = CCSequence::create
        (
         CCFadeOut::create(ANIMATE_DURIATION),
         CCCallFuncN::create(this, callfuncN_selector(Room::removeNodeCallback)),
         NULL
         );
        l->runAction(action);
        
        this->setVisible(true);
    }
    void hide() {
        
        this->getParent()->reorderChild(this, -1);
        CCLayerColor *l = CCLayerColor::create((ccColor4B){0,0,0,1});
        l->setTouchEnabled(true);
        this->addChild(l,2);
        CCAction *action = CCSequence::create
        (
         CCFadeIn::create(ANIMATE_DURIATION/2),
         CCCallFuncN::create(this, callfuncN_selector(Room::removeNodeCallback)),
         CCCallFuncO::create(this, callfuncO_selector(Room::setVisible), (CCObject*)false),
         NULL
         );
        l->runAction(action);
    }
};

class RoomCoffecup : public Room
{
    Prop                * codeInput;
    
    class PasscodeInput : public CodeInput
    {
        virtual void confirm() {
            if ("920" == codeString) {
                CCLOG("Yes, code passed!");
                CCTransitionScene *tran = CCTransitionCrossFade::create(0.6, MissionTransaction::sceneWithTextandNextScene("第三关", Level3::scene()));
                CCDirector::sharedDirector()->replaceScene(tran);
            }
            else {
                isBlinking = true;
                CCBlink *blink = CCBlink::create(.6, 3);
                CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(CodeInput::clearCode));
                codeLabel->runAction(CCSequence::createWithTwoActions(blink, call));
            }
        }
    public:
        CREATE_FUNC(PasscodeInput);
        static CCScene* scene() {
            CCScene *s = CCScene::create();
            s->addChild(PasscodeInput::create());
            return s;
        }
    };
protected:
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        if (codeInput->isVisible()) {
            if (codeInput->boundingBox().containsPoint(touch->getLocation())) {
                CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.6, PasscodeInput::scene()));
                return;
            }
        }
        Room::ccTouchesEnded(pTouches, pEvent);
    }

public:
    virtual bool init();
    static CCScene *scene();
    
    CREATE_FUNC(RoomCoffecup);
    
    void showCodeInput() {
        if (codeInput->isVisible())
            return;
        codeInput->setOpacity(0x0);
        codeInput->runAction(CCSequence::create
                     (
                      CCShow::create(),
                      CCFadeIn::create(0.6),
                      NULL
                      ));
    }
};

class RoomCoffeMachine : public Room
{
public:
    virtual bool init();
    static CCScene *scene();
    
    CREATE_FUNC(RoomCoffeMachine);
};

class RoomBean : public Room
{
protected:
    
public:
    virtual bool init();
    static CCScene *scene();
    
    CREATE_FUNC(RoomBean);
};

class RoomOperator : public Room
{
    CCSprite            * textbg;
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        CCNode *n = getChildByTag(ROOM_PROP_TAG);
        if (n) {
            if (n->boundingBox().containsPoint(touch->getLocation())) {
                if (!textbg->isVisible()) {
                    textbg->setOpacity(0);
                    textbg->runAction(CCSequence::create
                                      (
                                       CCShow::create(),
                                       CCFadeIn::create(0.3),
                                       CCDelayTime::create(2),
                                       CCFadeOut::create(0.3),
                                       CCHide::create(),
                                       NULL
                                      ));
                }
            }
        }
    }
    
    void playSound() {
        SimpleAudioEngine::sharedEngine()->playEffect("install-wheel.m4a");
    }
    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomOperator);
    
    void installWheel(Prop *wheel) {
        menu->setEnabled(false);
        wheel->retain();
        wheel->removeFromParentAndCleanup(false);
        addChild(wheel,2);
        wheel->runAction(CCSequence::create
                         (
                          CCEaseIn::create(CCMoveTo::create(0.5,ccpAdd(prop->getPosition(),
                                                                       ccp(0,20))), 2),
                          CCCallFunc::create(this, callfunc_selector(RoomOperator::playSound)),
                          CCEaseInOut::create(CCRotateTo::create(0.1, -10),1.2),
                          CCRepeat::create(CCSequence::create
                                           (
                                            CCEaseInOut::create(CCRotateTo::create(0.15, 15),1.2),
                                            CCEaseInOut::create(CCRotateTo::create(0.1, -10),2),
                                            CCDelayTime::create(0.4),
                                            NULL), 3),
                          CCEaseInOut::create(CCRotateTo::create(0.1, 0),1.2),
                          CCCallFuncO::create(CCDirector::sharedDirector(), callfuncO_selector( CCDirector::replaceScene),MissionTransaction::sceneWithTextandNextScene("第四关", Level4::scene())),
                          NULL
                         ));
    }
};

class RoomCodeBox : public Room
{
    class CodeBox : public CCLayer
    {
    private:
        CCSprite            * codeboxbg;
        bool                  state[8];
        
        CodeBox():codeboxbg(NULL) {
            for (int i=0; i<8; ++i) {
                state[i] = false;
            }
        }
        virtual ~CodeBox(){}
        
        void checkCode () {
            if (isCodeCorrect()) {
                CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionCrossFade>(0.5);
            }
        }
        
        void registerWithTouchDispatcher() {
            CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        }
        
        bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
            return !codeboxbg->boundingBox().containsPoint(pTouch->getLocation());
        }
        
        void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
            
        }
        
        void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
            if (!codeboxbg->boundingBox().containsPoint(pTouch->getLocation())) {
                CCDirector::sharedDirector()->popScene();
            }
        }
        
        void onBoxButton(CCObject *sender) {
            SimpleAudioEngine::sharedEngine()->playEffect("button-control.m4a");
            CCMenuItemToggle *toggle = (CCMenuItemToggle*)sender;
            state[toggle->getTag()] = toggle->getSelectedIndex() == 1;
            
            checkCode();
        }

    public:
        virtual bool init() {
            if (!CCLayer::init())
                return false;
            
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            
            codeboxbg = CCSprite::create("3buttoncontrolface.png");
            codeboxbg->setPosition(ccp(size.width/2, size.height/2));
            addChild(codeboxbg, -1);
            
            float margin = 8.0;
            float side = 52.0;
            CCPoint pos[] = {
                ccp(164 - side*3/2 - margin*1,98 + side/2),
                ccp(164 - side*1/2           ,98 + side/2),
                ccp(164 + side*1/2 + margin*1,98 + side/2),
                ccp(164 + side*3/2 + margin*2,98 + side/2),
                ccp(164 - side*3/2 - margin*1,98 - side/2 - 20),
                ccp(164 - side*1/2           ,98 - side/2 - 20),
                ccp(164 + side*1/2 + margin*1,98 - side/2 - 20),
                ccp(164 + side*3/2 + margin*2,98 - side/2 - 20)
            };
            
            CCArray *items = CCArray::createWithCapacity(8);
            
            for (int i=0; i<8; ++i) {
                CCMenuItemToggle *menuItem = CCMenuItemToggle::createWithTarget(this, menu_selector(CodeBox::onBoxButton), CCMenuItemImage::create("3buttonnormal.png",NULL),CCMenuItemImage::create("3buttonhighlight.png",NULL),NULL);
                menuItem->setPosition(pos[i]);
                //menuItem->setScale(1.1);
                menuItem->setTag(i);
                items->addObject(menuItem);
            }
            CCSize bgSize = codeboxbg->getContentSize();
            CCMenu *menu = CCMenu::createWithArray(items);
            menu->setPosition(ccp(73,71));
            addChild(menu ,1);
            
            setTouchEnabled(true);
            
            SimpleAudioEngine::sharedEngine()->preloadEffect("button-control.m4a");
            return true;
        }
        static CCScene* scene() {
            CCScene *scene = CCScene::create();
            scene->addChild(CodeBox::create());
            return scene;
        }
        CREATE_FUNC(CodeBox);
        
        bool isCodeCorrect() {
            return state[0] && state[3] && state[5] && state[6] &&
            !state[1] &&!state[2] &&!state[4] &&!state[7];
        }
    };
    
    Prop                * closedCodeBox;
    Prop                * openedCodeBox;
    bool                  boxOpened;
    bool                  wheelCollected;
    CodeBox             * codeBox;
    
    RoomCodeBox():closedCodeBox(NULL),openedCodeBox(NULL),boxOpened(false),wheelCollected(false),codeBox(NULL){}
    virtual ~RoomCodeBox(){}
    
    void setBoxOpend(bool opend) {
        boxOpened = opend;
        closedCodeBox->setVisible(!boxOpened);
        openedCodeBox->setVisible(boxOpened);
    }
    virtual void onEnterTransitionDidFinish() {
        if (codeBox) {
            setBoxOpend(codeBox->isCodeCorrect());
        }
        codeBox = NULL;
    }
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        if (boxOpened) {
            if (openedCodeBox->boundingBox().containsPoint(touch->getLocation())) {
                if (!wheelCollected) {
                    wheelCollected = true;
                    Prop *wheel = Prop::createWithFileAndInitScale("3wheel.png", 0.25);
                    wheel->setPosition(openedCodeBox->getPosition());
                    wheel->setType(kProp_Type_Tag_Wheel);
                    wheel->setDescription("这是一个船的方向盘，可以安装在驾驶台上");
                    addChild(wheel,2);
                    (target->*selector)(wheel);
                }
            }
        }
        else {
            if (closedCodeBox->boundingBox().containsPoint(touch->getLocation())) {
                codeBox = CodeBox::create();
                CCScene *scene = CCScene::create();
                scene->addChild(codeBox);
                CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.6, scene));
            }
        }
    }
    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomCodeBox);
};

class RoomShip : public Room
{
    CCSprite        * textbg;
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        CCNode *n = getChildByTag(ROOM_PROP_TAG);
        if (n) {
            if (n->boundingBox().containsPoint(touch->getLocation())) {
                if (!textbg->isVisible()) {
                    textbg->setOpacity(0);
                    textbg->runAction(CCSequence::create
                                      (
                                       CCShow::create(),
                                       CCFadeIn::create(0.3),
                                       CCDelayTime::create(2),
                                       CCFadeOut::create(0.3),
                                       CCHide::create(),
                                       NULL
                                       ));
                }
            }
        }
    }

public:
    virtual bool init();
    
    CREATE_FUNC(RoomShip);
};

class RoomPassword : public Room
{
    class PasswordInput : public WordInput
    {
        virtual void confirm() {
            if ("exitclub" == codeString) {
                CCLOG("Yes, code passed!");
                CCTransitionScene *tran = CCTransitionCrossFade::create(0.6, MissionTransaction::sceneWithTextandNextScene("第六关", Level6::scene()));
                CCDirector::sharedDirector()->replaceScene(tran);
                return;
            }
            WordInput::confirm();
        }
    public:
        CREATE_FUNC(PasswordInput);
        static CCScene* scene() {
            CCScene *s = CCScene::create();
            s->addChild(PasswordInput::create());
            return s;
        }
    };
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        CCNode *n = getChildByTag(ROOM_PROP_TAG);
        if (n) {
            if (n->boundingBox().containsPoint(touch->getLocation())) {
                CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.6, PasswordInput::scene()));
            }
        }
    }
    
    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomPassword);
    
    void showCodeInput() {
        CCSprite *n = (CCSprite*)getChildByTag(ROOM_PROP_TAG);
        if (n->isVisible())
            return;
        n->setOpacity(0x0);
        n->runAction(CCSequence::create
                     (
                      CCShow::create(),
                      CCFadeIn::create(0.6),
                      NULL
                      ));
    }
};

class RoomPasscode : public Room
{
    class PasscodeInput : public CodeInput
    {
        virtual void confirm() {
            if ("524" == codeString) {
                CCLOG("Yes, code passed!");
                SimpleAudioEngine::sharedEngine()->stopAllEffects();
                SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                CCTransitionScene *tran = CCTransitionCrossFade::create(0.6, MissionTransaction::sceneWithTextandNextScene("第五关", Level5::scene()));
                CCDirector::sharedDirector()->replaceScene(tran);
            }
            else {
                isBlinking = true;
                CCBlink *blink = CCBlink::create(.6, 3);
                CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(CodeInput::clearCode));
                codeLabel->runAction(CCSequence::createWithTwoActions(blink, call));
            }
        }
    public:
        CREATE_FUNC(PasscodeInput);
        static CCScene* scene() {
            CCScene *s = CCScene::create();
            s->addChild(PasscodeInput::create());
            return s;
        }
    };
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        CCNode *n = getChildByTag(ROOM_PROP_TAG);
        if (n && n->isVisible()) {
            if (n->boundingBox().containsPoint(touch->getLocation())) {
                CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.6, PasscodeInput::scene()));
            }
        }
    }
    
    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomPasscode);
    
    void showCodeInput() {
        CCSprite *n = (CCSprite*)getChildByTag(ROOM_PROP_TAG);
        if (n->isVisible())
            return;
        n->setOpacity(0x0);
        n->runAction(CCSequence::create
                     (
                      CCShow::create(),
                      CCFadeIn::create(0.6),
                      NULL
                     ));
    }
};

class RoomFackman : public Room
{
public:
    virtual bool init();
    
    CREATE_FUNC(RoomFackman);
};

class RoomCD : public Room
{
public:
    virtual bool init();
    
    CREATE_FUNC(RoomCD);
};

class RoomTorch : public Room
{
    
    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomTorch);
};

class RoomNewpaper : public Room
{
    CCLayerColor        * maskLayer;
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (maskLayer->isVisible())
            return;
        Room::ccTouchesEnded(pTouches, pEvent);
    }
    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomNewpaper);
    
    void turnOnLight() {
        if (!maskLayer->isVisible())
            return;
        maskLayer->runAction(CCSequence::create
                             (
                              CCFadeOut::create(0.6),
                              CCHide::create(),
                              NULL
                             ));
    }
};


class RoomPasscode2 : public Room
{
    Prop                    * codeinput;
    
    class PasscodeInput : public CodeInput
    {
        virtual void confirm() {
            if ("15" == codeString) {
                CCLOG("Yes, code passed!");
                CCTransitionScene *tran = CCTransitionCrossFade::create(0.6, MissionTransaction::sceneWithTextandNextScene("第七关", Level7::scene()));
                CCDirector::sharedDirector()->replaceScene(tran);
            }
            else {
                isBlinking = true;
                CCBlink *blink = CCBlink::create(.6, 3);
                CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(CodeInput::clearCode));
                codeLabel->runAction(CCSequence::createWithTwoActions(blink, call));
            }
        }
    public:
        CREATE_FUNC(PasscodeInput);
        static CCScene* scene() {
            CCScene *s = CCScene::create();
            s->addChild(PasscodeInput::create());
            return s;
        }
    };
    
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        if (codeinput && codeinput->isVisible()) {
            if (codeinput->boundingBox().containsPoint(touch->getLocation())) {
                CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.6, PasscodeInput::scene()));
            }
        }
        Room::ccTouchesEnded(pTouches, pEvent);
    }
    
    friend RoomSwitch;
    friend RoomTaiji;
public:
    virtual bool init();
    
    CREATE_FUNC(RoomPasscode2);
    
    void showCodeInput() {
        if (codeinput->isVisible())
            return;
        codeinput->setOpacity(0x0);
        codeinput->runAction(CCSequence::create
                     (
                      CCShow::create(),
                      CCFadeIn::create(0.6),
                      NULL
                      ));
    }
};

class RoomSwitch;

class RoomTaiji : public Room
{
    Taiji           * taiji;
    Prop            * sundial;
    Prop            * sundialshadow;
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
    virtual void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
    }
    
    CC_SYNTHESIZE(RoomSwitch*, roomSwitch, RoomSwitch);
    CC_SYNTHESIZE(RoomPasscode2*, roomPasscode, RoomPasscode);
    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomTaiji);
    
    bool isTaijiOpend() { return taiji->isOpend(); }
    void showSunShadow(bool show) { sundial->setVisible(!show); sundialshadow->setVisible(show); }
};

class RoomSwitch : public Room
{
    CCMenuItemToggle        * toggleSwitch;
    CCSprite                * textbg;
    CCLabelTTF              * label;
    
    virtual void onSwitch(CCObject *sender) {
        if (roomTaiji && !roomTaiji->isTaijiOpend()) {
            toggleSwitch->setSelectedIndex(0);
            if (!textbg->isVisible()) {
                label->setString("不能使用");
                textbg->setOpacity(0);
                textbg->runAction(CCSequence::create
                                  (
                                   CCShow::create(),
                                   CCFadeIn::create(0.3),
                                   CCDelayTime::create(2),
                                   CCFadeOut::create(0.3),
                                   CCHide::create(),
                                   NULL
                                   ));
            }
        }
        else {
            if (roomTaiji) roomTaiji->showSunShadow(true);
            ((CCMenu*)toggleSwitch->getParent())->setEnabled(false);
            if (!textbg->isVisible()) {
                label->setString("有什么东西被触发了");
                textbg->setOpacity(0);
                textbg->runAction(CCSequence::create
                                  (
                                   CCShow::create(),
                                   CCFadeIn::create(0.3),
                                   CCDelayTime::create(2),
                                   CCFadeOut::create(0.3),
                                   CCHide::create(),
                                   NULL
                                   ));
            }
            SimpleAudioEngine::sharedEngine()->playEffect("switch.m4a");
        }
    }
    CC_SYNTHESIZE(RoomTaiji*, roomTaiji, RoomTaiji);
    
public:
    RoomSwitch(){
        SimpleAudioEngine::sharedEngine()->preloadEffect("switch.m4a");
    }
    virtual bool init();
    
    CREATE_FUNC(RoomSwitch);
    bool isSwitchOn() {
        return toggleSwitch->getSelectedIndex() == 1;
    }
};


class RoomMonkey : public Room
{
    Prop                * codeInput;
    Prop                * monkey;
    CCSprite            * hand;
    
    class PasswordInput : public WordInput
    {
        virtual void confirm() {
            if ("nic" == codeString) {
                CCLOG("Yes, code passed!");
                CCTransitionScene *tran = CCTransitionCrossFade::create(0.6, End::scene());
                CCDirector::sharedDirector()->replaceScene(tran);
                return;
            }
            WordInput::confirm();
        }
    public:
        CREATE_FUNC(PasswordInput);
        static CCScene* scene() {
            CCScene *s = CCScene::create();
            s->addChild(PasswordInput::create());
            return s;
        }
    };

    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
        if (!this->isVisible())
            return;
        static PropDetail *detail = NULL;
        
        if (detail) {
            monkey->setVisible(true);
            detail->removeFromParentAndCleanup(true);
            detail = NULL;
            return;
        }
        CCTouch *touch = (CCTouch*) pTouches->anyObject();
        
        if (monkey->boundingBox().containsPoint(touch->getLocation())) {
            Prop *p = Prop::createWithFileAndInitScale("monkeybody.png", 1.0);
            p->setDescription("我似乎记得这个调皮的小家伙叫做......");
            
            CCSprite *h = CCSprite::create("hand.png");
            h->setAnchorPoint(ccp(0.5, 0.15));
            h->setPosition(ccp(34*4,26*4));
            p->addChild(h,-1);
            
            detail = PropDetail::createWithProp(p);
            addChild(detail,2);
            
            monkey->setVisible(false);
        }
        else if (codeInput->boundingBox().containsPoint(touch->getLocation())) {
            CCDirector::sharedDirector()->pushScene(CCTransitionCrossFade::create(0.6, PasswordInput::scene()));
        }
    }

    
public:
    virtual bool init();
    
    CREATE_FUNC(RoomMonkey);
};

#endif /* defined(__Escape__Room__) */

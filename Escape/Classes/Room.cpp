//
//  Room.cpp
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#include "Room.h"
#include "Prop.h"
#include "Collections.h"
#include "CollectionBox.h"

using namespace cocos2d;
using namespace CocosDenshion;


CCScene *Room::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(Room::create());
    return scene;
}

bool Room::init()
{
    if (!CCLayer::init())
        return false;
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCPoint c = ccpMult(ccpFromSize(s), 0.5);
    
    CCLayer *roomBgLayer = CCLayer::create();
    addChild(roomBgLayer,-1);
    
    CCSprite *bg = CCSprite::create("background.png");
    bg->setPosition(ccp(s.width/2, s.height/2));
    roomBgLayer->addChild(bg,-1);
    
    CCMenuItemImage *leftItem = CCMenuItemImage::create("doorl.png", NULL, this, menu_selector(Room::onLeftDoor));
    CCMenuItemImage *middleItem = CCMenuItemImage::create("doorm.png", NULL, this, menu_selector(Room::onMiddleDoor));
    CCMenuItemImage *rightItem = CCMenuItemImage::create("doorr.png", NULL, this, menu_selector(Room::onRightDoor));
    
    menu = CCMenu::create(leftItem, middleItem, rightItem, NULL);
    menu->alignItemsHorizontallyWithPadding(80.0);
    roomBgLayer->addChild(menu);
    
    setTouchEnabled(true);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("ele-door.m4a");
    
    return true;
}

void Room::setLeftRoom(Room *room)
{
    leftRoom = room;
    room->rightRoom = this;
}

void Room::setRightRoom(Room *room)
{
    rightRoom = room;
    room->leftRoom = this;
}

CCScene *RoomBean::scene()
{
    CCScene *scene = CCScene::create();
    scene->addChild(create());
    return scene;
}

bool RoomCoffecup::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("coffecup.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("这是一个装咖啡的杯子");
    prop->setType(kProp_Type_Tag_CoffeCup);
    
    this->addChild(prop,1);
    
    codeInput = Prop::createWithFileAndInitScale("codelock.png", 0.15);
    codeInput->setPosition(ccp(s.width/2+60, s.height/2));
    codeInput->setDescription("");
    codeInput->setVisible(false);
    this->addChild(codeInput,1);
    
    return true;
}


bool RoomCoffeMachine::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("cmachine.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("很烫,需要有东西装");
    prop->setType(kProp_Type_Tag_CoffeMachine);
    
    this->addChild(prop,1);
    
    return true;
}

bool RoomBean::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("cbean.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("放到咖啡机中就可以得到一杯香甜的咖啡了！");
    prop->setType(kProp_Type_Tag_CoffeBean);
    
    this->addChild(prop,1);
    
    return true;
}

bool RoomOperator::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("3wheelstation.png", 1.0);
    prop->setPosition(ccp(s.width/2, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("无法使用，好像少了什么东西");
    
    this->addChild(prop,1);
    
    textbg = CCSprite::create("textbg.png");
    textbg->setPosition(ccp(s.width/2, 40));
    textbg->setVisible(false);
    addChild(textbg,1);
    
    CCLabelTTF *label = CCLabelTTF::create(prop->getDescription(), "Fixedsys.ttf", 16);
    label->setDimensions(textbg->getContentSize());
    label->setHorizontalAlignment(kCCTextAlignmentCenter);
    label->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    label->setPosition(ccp(textbg->getContentSize().width/2,
                           textbg->getContentSize().height/2));
    textbg->addChild(label);
    
    SimpleAudioEngine::sharedEngine()->preloadEffect("install-wheel.m4a");
    return true;
}

bool RoomCodeBox::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    closedCodeBox = Prop::createWithFileAndInitScale("3buttoncontrolclose.png", 1.0);
    closedCodeBox->setPosition(ccp(s.width/2, 60.0));
    closedCodeBox->setDescription("");
    closedCodeBox->setType(kProp_Type_Tag_CoffeBean);
    closedCodeBox->setVisible(!boxOpened);
    
    openedCodeBox = Prop::createWithFileAndInitScale("3buttoncontrolopen.png", 1.0);
    openedCodeBox->setPosition(ccp(s.width/2, 60.0));
    openedCodeBox->setDescription("");
    openedCodeBox->setType(kProp_Type_Tag_CoffeBean);
    openedCodeBox->setVisible(boxOpened);
    
    
    this->addChild(closedCodeBox,1);
    this->addChild(openedCodeBox,1);
    
    return true;
}


bool RoomShip::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("3boat.png", 0.35);
    prop->setPosition(ccp(s.width/2 + 60, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("杭州水上巴士留念");
    prop->setType(kProp_Type_Tag_CoffeBean);
    
    this->addChild(prop,1);
    
    textbg = CCSprite::create("textbg.png");
    textbg->setPosition(ccp(s.width/2, 40));
    textbg->setVisible(false);
    addChild(textbg,1);
    
    CCLabelTTF *label = CCLabelTTF::create(prop->getDescription(), "Fixedsys.ttf", 16);
    label->setDimensions(textbg->getContentSize());
    label->setHorizontalAlignment(kCCTextAlignmentCenter);
    label->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    label->setPosition(ccp(textbg->getContentSize().width/2,
                           textbg->getContentSize().height/2));
    textbg->addChild(label);
    
    return true;
}

bool RoomPassword::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("A-Zcodeenter.png", 0.12);
    prop->setPosition(ccp(s.width/2 + 60, s.height/2));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("");
    
    this->addChild(prop,1);
    
    return true;
}

bool RoomPasscode::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("codelock.png", 0.15);
    prop->setPosition(ccp(s.width/2+60, s.height/2));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("");
    prop->setVisible(false);
    this->addChild(prop,1);
    
    return true;
}

bool RoomCD::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("disc.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("唛歌时尚KTV");
    prop->setType(kProp_Type_Tag_CD);
    
    this->addChild(prop,1);
    
    return true;
}

bool RoomFackman::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("fakeman.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("好像可以放什么进去");
    prop->setType(kProp_Type_Tag_Fakeman);
    
    this->addChild(prop,1);
    
    return true;
}

bool RoomTorch::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("tourch.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("这是一个手电筒");
    prop->setType(kProp_Type_Tag_Torch);
    
    this->addChild(prop,1);
    
    return true;
}

bool RoomNewpaper::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("newspaper.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("新闻");
    prop->setType(kProp_Type_Tag_Newspaper);
    
    this->addChild(prop,1);
    
    maskLayer = CCLayerColor::create(ccc4(0, 0, 0, 0xff));
    this->addChild(maskLayer,2);
    
    CCSprite *leftDoor = CCSprite::create("doorl.png");
    CCPoint p = menu->convertToWorldSpace(((CCMenuItem*)(menu->getChildren()->objectAtIndex(0)))->getPosition());
    leftDoor->setPosition(p);
    this->addChild(leftDoor,3);
    
    return true;
}

bool RoomTaiji::init()
{
    if (!Room::init())
        return false;
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    prop = Prop::createWithFileAndInitScale("sundial.png", 0.25);
    prop->setPosition(ccp(s.width/2, s.height/2));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("授时图：还不能看到时间啊……");
    
    sundial = prop;
    
    this->addChild(prop,1);
    
    sundialshadow = Prop::createWithFileAndInitScale("sundialwithshodow.png", 0.25);
    sundialshadow->setPosition(ccp(s.width/2, s.height/2));
    sundialshadow->setTag(ROOM_PROP_TAG);
    sundialshadow->setDescription("授时图：啊……已经能看到时间了！");
    sundialshadow->setVisible(false);
    
    this->addChild(sundialshadow,1);
    
    taiji = Taiji::create();
    
    addChild(taiji,2);
    
    return true;
}

bool RoomTaiji::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent)
{
    if (!this->isVisible())
        return false;
    if (!isTaijiOpend())
        return false;
    
    static PropDetail *detail = NULL;
    
    if (detail) {
        detail->removeFromParentAndCleanup(true);
        detail = NULL;
        return true;
    }
    CCNode *n = getChildByTag(ROOM_PROP_TAG);
    if (n) {
        if (n->boundingBox().containsPoint(touch->getLocation())) {
            if (roomSwitch && roomSwitch->isSwitchOn()) {
                Prop *p = Prop::createWithFileAndInitScale("sundialwithshodow.png", 1.0);
                p->setDescription("授时图：啊……已经能看到时间了！");
                detail = PropDetail::createWithProp(p);
                addChild(detail,5);
                
                if (roomPasscode) {
                    roomPasscode->showCodeInput();
                }
            }
            else {
                Prop *p = Prop::createWithFileAndInitScale("sundial.png", 1.0);
                p->setDescription("授时图：还不能看到时间啊……");
                detail = PropDetail::createWithProp(p);
                addChild(detail,5);
            }
            return true;
        }
    }
    return false;
    
}

bool RoomSwitch::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemToggle *item = CCMenuItemToggle::createWithTarget(this, menu_selector(RoomSwitch::onSwitch), CCMenuItemImage::create("off.png", NULL),CCMenuItemImage::create("on.png", NULL),NULL);
    item->setScale(0.35);
    CCMenu *menu = CCMenu::createWithItem(item);
    menu->setPosition(ccp(s.width/2, 60.0));
    //menu->setEnabled(false);
    
    toggleSwitch = item;
    
    addChild(menu);
    
    textbg = CCSprite::create("textbg.png");
    textbg->setPosition(ccp(s.width/2, 40));
    textbg->setVisible(false);
    addChild(textbg,1);
    
    label = CCLabelTTF::create("", "Fixedsys.ttf", 16);
    label->setDimensions(textbg->getContentSize());
    label->setHorizontalAlignment(kCCTextAlignmentCenter);
    label->setVerticalAlignment(kCCVerticalTextAlignmentTop);
    label->setPosition(ccp(textbg->getContentSize().width/2,
                           textbg->getContentSize().height/2));
    textbg->addChild(label);
    
    return true;
}


bool RoomPasscode2::init()
{
    if (!Room::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    codeinput = Prop::createWithFileAndInitScale("codelock.png", 0.15);
    codeinput->setPosition(ccp(s.width/2+60, s.height/2));
    codeinput->setDescription("");
    codeinput->setVisible(false);
    this->addChild(codeinput,1);
    
    prop = Prop::createWithFileAndInitScale("stone.png", 0.25);
    prop->setPosition(ccp(s.width/2, 60.0));
    prop->setTag(ROOM_PROP_TAG);
    prop->setDescription("授时图");
    prop->setType(kProp_Type_Tag_Stone);
    
    this->addChild(prop,1);

    
    return true;
}


bool RoomMonkey::init()
{
    if (!Room::init())
        return false;
    
    menu->setEnabled(false);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    
    monkey = Prop::createWithFileAndInitScale("monkeybody.png", 0.25);
    monkey->setPosition(ccp(s.width/2 + 75, 60.0));
    monkey->setDescription("我似乎记得这个调皮的小家伙叫做......");
    
    this->addChild(monkey,1);
    
    hand = CCSprite::create("hand.png");
    hand->setAnchorPoint(ccp(0.5, 0.15));
    hand->setPosition(ccp(34*4,26*4));
    monkey->addChild(hand,-1);
    
    CCAction *sequence = CCSequence::create(
                                            CCEaseInOut::create(CCRotateTo::create(0.3, -15),2),
                                            CCEaseInOut::create(CCRotateTo::create(0.3, 15),2),
                                            NULL);
    hand->runAction(CCRepeatForever::create((CCActionInterval*)sequence));
    
    codeInput = Prop::createWithFileAndInitScale("A-Zcodeenter.png", 0.12);
    codeInput->setPosition(ccp(s.width/2 + 60, s.height/2));
    codeInput->setDescription("");
    
    this->addChild(codeInput,1);
    
    return true;
}

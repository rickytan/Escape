//
//  MoreScene.cpp
//  Escape
//
//  Created by ricky on 12-12-24.
//
//

#include "MoreScene.h"
#include "StarterScene.h"

CCScene* More::scene()
{
    CCScene *s = CCScene::create();
    s->addChild(More::create());
    return s;
}

bool More::init()
{
    if (!CCLayer::init())
        return false;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bg = CCSprite::create("moredetail.png");
    bg->setPosition(ccp(s.width/2, s.height/2));
    addChild(bg,-1);
    
    CCMenuItemImage *item = CCMenuItemImage::create("enterEclub.png", "enterEclubpress.png",this,menu_selector(More::onStartPlay));
    item->setPosition(ccp(0,50));
    
    CCMenu *menu = CCMenu::createWithItem(item);
    addChild(menu);
    
    setTouchEnabled(true);
    
    return true;
}

void More::onStartPlay(cocos2d::CCObject *sender)
{
    CCApplication::sharedApplication()->openURL("http://tougi.taobao.com/");
}
//
//  EscapeAppDelegate.cpp
//  Escape
//
//  Created by ricky on 12-12-6.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "StarterScene.h"
#include "MissionTransactionScene.h"
#include "RoomsScene.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"


USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    TargetPlatform target = getTargetPlatform();
    switch (target) {
        case cocos2d::kTargetAndroid:
            CCFileUtils::sharedFileUtils()->setResourceDirectory("android");
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(720, 480, kResolutionExactFit);
            break;
        case cocos2d::kTargetIphone:
            if (pDirector->enableRetinaDisplay(true))
                CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
            else
                CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
            break;
        default:
            break;
    }

    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenu::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

//
//  SafeBoxScene.h
//  Escape
//
//  Created by ricky on 12-12-10.
//
//

#ifndef __Escape__SafeBoxScene__
#define __Escape__SafeBoxScene__

#include "cocos2d.h"
#include "CCControlExtensions.h"

using namespace cocos2d;
using namespace std;

class Level1 : public CCLayer
{
private:
    CCSprite            * mapImage;
    CCMenu              * menu;
    
    void onMap(CCObject *sender);
    void onCode(CCObject *sender);
    
    void showMap();
    void removeMap();
    
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    

public:
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Level1);
};

class CodeInput : public CCLayer
{
protected:
    std::string               codeString;
    CCLabelTTF              * codeLabel;
    
    bool                      isBlinking;
    
    void playButtonSound();
    
    void clearCode();
    virtual void confirm();
    void updateCodeLabel();
    
    void onButton(CCObject *sender);
    
public:

    
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(CodeInput);
};

class WordInput : public CCLayer
{
protected:
    std::string               codeString;
    CCLabelTTF              * codeLabel;
    
    bool                      isBlinking;
    
    void playButtonSound();
    
    void clearCode();
    virtual void confirm();
    void updateCodeLabel();
    
    void onButton(CCObject *sender);
    
public:
    
    
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(WordInput);
};

#endif /* defined(__Escape__SafeBoxScene__) */

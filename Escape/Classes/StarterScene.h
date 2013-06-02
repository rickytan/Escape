//
//  StarterScene.h
//  Escape
//
//  Created by ricky on 12-12-9.
//
//

#ifndef __Escape__StarterScene__
#define __Escape__StarterScene__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class Starter : public cocos2d::CCLayer
{
private:
    CCLayer                 * bgLayer;
    CCSprite                * bgImage;
    CCLayer                 * scriptLayer;
    CCSprite                * subtitleBar;
    CCLabelTTF              * scriptText;
    
    int                       currentPage;
    
    void showPage(int page);
    void nextPage();
    void showCurrentPage();
    void playDial();
    void playWait();

    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    void onEnterTransitionDidFinish();
public:
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Starter);
};

#endif /* defined(__Escape__StarterScene__) */

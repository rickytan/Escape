//
//  CoffeCup.h
//  Escape
//
//  Created by ricky on 12-12-15.
//
//

#ifndef __Escape__CoffeCup__
#define __Escape__CoffeCup__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CoffeCup : public CCSprite, public CCTouchDelegate
{
private:
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
public:

    bool init();
};
#endif /* defined(__Escape__CoffeCup__) */

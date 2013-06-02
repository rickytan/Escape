//
//  Level7.h
//  Escape
//
//  Created by ricky on 12-12-18.
//
//

#ifndef __Escape__Level7__
#define __Escape__Level7__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CollectionBox.h"
#include "Collections.h"

using namespace cocos2d;
using namespace CocosDenshion;

class Level7 : public CCLayer
{
private:
    
public:
    virtual bool init();
    static CCScene* scene();
    
    CREATE_FUNC(Level7);
};

#endif /* defined(__Escape__Level7__) */

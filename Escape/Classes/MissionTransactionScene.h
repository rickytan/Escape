//
//  MissionTransactionScene.h
//  Escape
//
//  Created by ricky on 12-12-11.
//
//

#ifndef __Escape__MissionTransactionScene__
#define __Escape__MissionTransactionScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MissionTransaction : public CCLayerColor
{
private:
    CCScene         * nextScene;
    CCLabelTTF      * textLabel;
    
    void gotoNextScene();

    void onEnterTransitionDidFinish();
    
public:
    static CCScene* sceneWithTextandNextScene(std::string text,CCScene *scene);
    static MissionTransaction* createWithText(CCString* text);
    static MissionTransaction* createWithText(const char text[]);
    static MissionTransaction* createWithText(std::string text);
    
    virtual bool initWithText(const char text[]);
    MissionTransaction();
    virtual ~MissionTransaction();
    
    void setNextScene(CCScene *scene);
};

#endif /* defined(__Escape__MissionTransactionScene__) */

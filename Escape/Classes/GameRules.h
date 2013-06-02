//
//  GameRules.h
//  Escape
//
//  Created by ricky on 12-12-17.
//
//

#ifndef __Escape__GameRules__
#define __Escape__GameRules__

#include <iostream>
#include "Prop.h"

class GameRules
{
public:
    virtual bool canMerge(Prop *p1, Prop *p2) { return false; }
    virtual CCString* whyCannotMerge(Prop *p1, Prop *p2) { return NULL; }
    virtual Prop* merge(Prop *p1, Prop *p2) { return NULL; }
    virtual bool isPassed() { return false; }
    virtual bool pickProp(Prop *p) { return false; }
    virtual bool canDragOut(Prop *p) { return false; }
    virtual void dragOut(Prop *p) {}
};

#endif /* defined(__Escape__GameRules__) */

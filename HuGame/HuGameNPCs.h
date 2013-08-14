//
//  HuGameNPCs.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#ifndef __HuGame__HuGameNPCs__
#define __HuGame__HuGameNPCs__

#include "cocos2d.h"

using namespace cocos2d;

class HuGameNPCs : cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuGameNPCs);

protected:
    CCArray* enemies;

private:
    CCPoint generateEnemyInitialPoint();


};

#endif /* defined(__HuGame__HuGameNPCs__) */

//
//  HuGameHud.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#ifndef __HuGame__HuGameHud__
#define __HuGame__HuGameHud__

#include "cocos2d.h"

using namespace cocos2d;

class HuGameHud : cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuGameHud);
    
    void clockTick(CCObject* pSender);
    

    
private:
    CCLabelTTF* labelClock;
    CCLabelTTF* labelCurrency;
    CCLabelTTF* labelHealth;
    CCLabelTTF* labelRound;
    CCLabelTTF* labelGameName;
    
    // the private variables
    int numClockTicks;

};


#endif /* defined(__HuGame__HuGameHud__) */

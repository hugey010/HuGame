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

class HuGameHud : cocos2d::CCLayer
{
public:
    virtual bool init();
    cocos2d::CCLabelTTF* labelClock;
    CREATE_FUNC(HuGameHud);
    
    void clockTick(CCObject* pSender);
    

    
private:
    cocos2d::CCLabelTTF* labelCurrency;
    cocos2d::CCLabelTTF* labelHealth;
    cocos2d::CCLabelTTF* labelRound;
    cocos2d::CCLabelTTF* labelGameName;
    
    // the private variables
    int numClockTicks;

};


#endif /* defined(__HuGame__HuGameHud__) */

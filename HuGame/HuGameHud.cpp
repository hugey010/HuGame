//
//  HuGameHud.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#include "HuGameHud.h"
#include "Constants.h"
#include <string>

using namespace cocos2d;

bool HuGameHud::init()
{
    CCString *clock = CCString::createWithFormat("Timeleft: %d", (int)ROUND_INTERVAL);
    this->labelClock = CCLabelTTF::create(clock->getCString(), HUD_FONT, HUD_FONT_SIZE);
    this->labelClock->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30));
    this->addChild(this->labelClock);

    
    this->schedule(schedule_selector(HuGameHud::clockTick), 1.0, kCCRepeatForever, 0);

    
    return true;
}

void HuGameHud::clockTick(CCObject *pSender)
{
    numClockTicks++;
    int timeleft = ROUND_INTERVAL - numClockTicks;
    timeleft = timeleft > 0 ? timeleft : 0;
    CCString *clock = CCString::createWithFormat("Timeleft: %d", timeleft);
    this->labelClock->setString(clock->getCString());
}
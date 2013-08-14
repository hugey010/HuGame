//
//  HuGameHud.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#include "HuGameHud.h"
#include "Constants.h"
#import "HuPlayer.h"

#include <string>

using namespace cocos2d;

bool HuGameHud::init()
{
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // clock label
    CCString *clock = CCString::createWithFormat("Timeleft: %ds", (int)ROUND_INTERVAL);
    this->labelClock = CCLabelTTF::create(clock->getCString(), HUD_FONT, HUD_FONT_SIZE);
    this->labelClock->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));
    this->addChild(this->labelClock);
    // clock timer
    this->schedule(schedule_selector(HuGameHud::clockTick), 1.0, kCCRepeatForever, 0);

    // health label
    HuPlayer *player = HuPlayer::getInstance();
    CCString *health = CCString::createWithFormat("Health: %d", player->health);
    this->labelHealth = CCLabelTTF::create(health->getCString(), HUD_FONT, HUD_FONT_SIZE);
    this->labelHealth->setPosition(ccp(80, SCREEN_HEIGHT - 50));
    this->addChild(this->labelHealth);
    
    CCString *level = CCString::createWithFormat("Level: %d", player->level);
    this->labelRound = CCLabelTTF::create(level->getCString(), HUD_FONT, HUD_FONT_SIZE);
    this->labelRound->setPosition(ccp(SCREEN_WIDTH - 80, SCREEN_HEIGHT - 50));
    this->addChild(this->labelRound);
    
    return true;
}

void HuGameHud::clockTick(CCObject *pSender)
{
    numClockTicks++;
    int timeleft = ROUND_INTERVAL - numClockTicks;
    timeleft = timeleft > 0 ? timeleft : 0;
    CCString *clock = CCString::createWithFormat("Timeleft: %ds", timeleft);
    this->labelClock->setString(clock->getCString());
}

//
//  HuGameFortress.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/4/13.
//
//

#include "HuGameFortress.h"
#include "Constants.h"
#import "HuPlayer.h"


using namespace cocos2d;

bool HuGameFortress::init()
{
    
    // the very center defense item. What would everyone want to defend??? //
    
    CCSprite *centerDefense = CCSprite::create("puppy.png");
    centerDefense->setPosition(ccp(SCREEN_WIDTH / 2, GROUND_END_Y / 2));
    this->addChild(centerDefense);
    
    return true;
}

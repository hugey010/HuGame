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
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // the very center defense item. What would everyone want to defend??? //
    CCSprite *centerDefense = CCSprite::create("puppy.png");
    centerDefense->setPosition(ccp(SCREEN_WIDTH / 2, GROUND_END_Y / 2));
    this->addChild(centerDefense);
    

    
    return true;
}

void HuGameFortress::handleBaseUpgrades() {
    HuPlayer *player = HuPlayer::getInstance();

    switch (player->defenseUpgradeLevel) {
        case DEFENSE_UPGRADE_1 : {
            CCSprite *spriteLeft = CCSprite::create("broken_fence_right.png");
            spriteLeft->setScale(0.7f);
            spriteLeft->setRotation(-40.0f);
            spriteLeft->setPosition(ccp(SCREEN_WIDTH / 2 - player->baseWidth / 2, GROUND_END_Y / 2));
            
            CCSprite *spriteRight = CCSprite::create("broken_fence_left.png");
            spriteRight->setScale(0.7f);
            spriteRight->setRotation(40.0f);
            spriteRight->setPosition(ccp(SCREEN_WIDTH / 2 + player->baseWidth / 2, GROUND_END_Y / 2));
            
            this->addChild(spriteRight);
            this->addChild(spriteLeft);
            
            break;
        }
        case DEFENSE_UPGRADE_2 : {
            break;
        }
        case DEFENSE_UPGRADE_3 : {
            break;
        }
        default : {
            // do nothing biotch
            break;
        }
    }
    

    
}

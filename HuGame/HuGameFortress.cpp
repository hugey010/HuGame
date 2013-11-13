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
    CCSprite *sprite;
    //sprite = CCSprite::create("broken-fence.png", CCRectMake(SCREEN_WIDTH / 2.0 - player->baseWidth / 2.0, 0, 30, SCREEN_HEIGHT));
    sprite = CCSprite::create("broken-fence.png");
    sprite->setPosition(ccp(SCREEN_WIDTH / 2, GROUND_END_Y / 2));

    switch (player->defenseUpgradeLevel) {
        case DEFENSE_UPGRADE_1 :
            
            break;
        case DEFENSE_UPGRADE_2 :
            break;
        case DEFENSE_UPGRADE_3 :
            break;
        default :
            break;
    }
    
    this->addChild(sprite);
    
    
}

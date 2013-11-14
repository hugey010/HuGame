//
//  Constants.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#ifndef HuGame_Constants_h
#define HuGame_Constants_h

#define CC_SHARED_DIRECTOR CCDirector::sharedDirector()

// Screen size
#define SCREEN_SIZE cocos2d::CCDirector::sharedDirector()->getWinSize()
#define SCREEN_WIDTH cocos2d::CCDirector::sharedDirector()->getWinSize().width
#define SCREEN_HEIGHT cocos2d::CCDirector::sharedDirector()->getWinSize().height

#define SCREEN_SIZE_PX cocos2d::CCDirector::sharedDirector()->getWinSizeInPixels()
#define SCREEN_WIDTH_PX cocos2d::CCDirector::sharedDirector()->getWinSizeInPixels().width
#define SCREEN_HEIGHT_PX cocos2d::CCDirector::sharedDirector()->getWinSizeInPixels().height

// INTERACTION DEFINITIONS
#define SWIPE_BASE_BUFFER (SCREEN_WIDTH / 4.5)


// MENU DEFINITIONS
#define MENU_FONT_SIZE (float)30.0
#define MENU_FONT_HEADER_SIZE (float)40.0
#define MENU_FONT "Helvetica"

// HUD DEFINITIONS
#define HUD_FONT "Helvetica"
#define HUD_FONT_SIZE (float)30.0

// GAME DEFINITIONS
#define ROUND_INTERVAL 15.0 // seconds, 2 minutes
#define GROUND_END_Y SCREEN_HEIGHT / 3

#define ENEMY_SPEED 300

// cost constants
#define COST_HEALTH 100
#define COST_CANNON 50
#define COST_SOLDIER 10
#define COST_FORTRESS_1 100
#define COST_FORTRESS_2 500
#define COST_FORTRESS_3 1000



enum ElementalDamageTypes {
    FrostDamage = 1,
    FireDamage = 2,
    LightningDamage = 3,
    PoisonDamage = 4,
    PhysicalDamage = 5
};



#endif

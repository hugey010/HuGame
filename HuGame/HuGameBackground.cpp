//
//  HuGameBackground.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/4/13.
//
//

#include "HuGameBackground.h"
#include "Constants.h"

using namespace cocos2d;

bool HuGameBackground::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLayerColor *ground = CCLayerColor::create(ccc4(205, 133, 63, 255));
    ground->setPosition(ccp(0, 0));
    ground->setContentSize(CCSizeMake(SCREEN_WIDTH, GROUND_END_Y));
    this->addChild(ground);
    
    CCLayerGradient *background = CCLayerGradient::create(ccc4(135, 206, 250, 200), ccc4(30, 130, 30, 1));
    background->setPosition(ccp(0, GROUND_END_Y));
    background->setContentSize(CCSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_END_Y));
 
    this->addChild(background);

    
    return true;
}
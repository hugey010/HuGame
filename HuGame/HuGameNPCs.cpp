//
//  HuGameNPCs.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#include "HuGameNPCs.h"
#include "Constants.h"
#include "HuPlayer.h"

using namespace cocos2d;

bool HuGameNPCs::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->enemies = CCArray::create();
    
    CCSprite *enemy = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("Player.png", CCRectMake(0, 0, 20, 20)));
    enemy->setPosition(this->generateEnemyInitialPoint());
    this->addChild(enemy);
    
    
    HuPlayer *player = HuPlayer::getInstance();
    
    
    int leftRight = (enemy->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (player->baseWidth / 2);
    float realFinalY = enemy->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
   
    CCFiniteTimeAction *move = CCMoveTo::create(5.0, realDestination);
    CCFiniteTimeAction *moveBack = CCMoveTo::create(2.0, ccp(0, SCREEN_HEIGHT - 10));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(moveBack);
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    enemy->runAction(actionSequence);

    this->enemies->addObject(enemy);
    

    return true;
}

CCPoint HuGameNPCs::generateEnemyInitialPoint()
{
    float x = 0;
    float y = 0;
    
    // decide if starting on left side or right side
    int leftRight = random() % 2;
    x = SCREEN_WIDTH * leftRight;
    
    y = random() % (int)GROUND_END_Y;
    
    return ccp(x, y);
}
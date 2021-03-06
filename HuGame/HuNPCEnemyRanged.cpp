//
//  HuNPCEnemyRanged.cpp
//  HuGame
//
//  Created by Tyler on 12/1/13.
//
//

#include "HuNPCEnemyRanged.h"
#include "HuPlayer.h"
#include "HuProjectile.h"

#define M_PI        3.14159265358979323846264338327950288   /* pi             */

using namespace cocos2d;

void HuNPCEnemyRanged::setupSprite() {
    sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("turtle_tank.png", CCRectMake(0, 0, 50, 50)));
    sprite->setPosition(HuNPCEnemyRanged::generateEnemyInitialPoint());
    layer->addChild(sprite);
    layer->addChild((CCNode*)this);
}

void HuNPCEnemyRanged::setupStats() {
    health = 200;
    givesCurrency = 5;
    dealsDamage = 3;
    
}

void HuNPCEnemyRanged::setupActions() {
    
    int leftRight = (sprite->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    sprite->setScaleX(leftRight * sprite->getScaleX());
    
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (SCREEN_WIDTH / 4);
    float realFinalY = sprite->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
    
    CCFiniteTimeAction *move = CCMoveTo::create(secondsToReachFinalPosition(), realDestination);
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuNPCEnemyRanged::enemyMoveFinished));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    sprite->runAction(actionSequence);
}

void HuNPCEnemyRanged::enemyMoveFinished(CCNode *sender) {
    
    // schedule attack
    if (sprite->isVisible()) {
        float interval = attackInterval();
        this->schedule(schedule_selector(HuNPCEnemyRanged::attack), interval, kCCRepeatForever, interval);
    }
}

void HuNPCEnemyRanged::attack() {
    // do ranged attack
    if (sprite->isVisible()) {
        HuProjectile *projectile = new HuProjectile;
        projectile->initForPlayerAttack(MISSILE, sprite->getPosition(), ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), layer);
    }
}

void HuNPCEnemyRanged::killNPC() {
    this->unscheduleAllSelectors();
}

CCPoint HuNPCEnemyRanged::generateEnemyInitialPoint() {
    float x = 0;
    float y = 0;
    
    // decide if starting on left side or right side
    int leftRight = random() % 2;
    x = SCREEN_WIDTH * leftRight;
    
    y = random() % (int)GROUND_END_Y;
    y = MAX(y, 30);
    
    return ccp(x, y);
}

// seconds to reach final position
float HuNPCEnemyRanged::secondsToReachFinalPosition() {
    
    HuPlayer *player = HuPlayer::getInstance();
    switch (player->level) {
        case 0:
        case 1:
        case 2: {
            return 2.0;
        }
        case 3: {
            return 1.9;
        }
        case 4: {
            return 1.8;
            break;
        }
        case 5:{
            return 1.7;
        }
        case 6:{
            return 1.6;
        }
        case 7:{
            return 1.5;
        }
        case 8:{
            return 1.4;
        }
        case 9:{
            return 1.3;
        }
        case 10:{
            return 1.2;
        }
        case 11: {
            return 1.1;
            
        }
        case 12: {
            return 1.0;
        }
        default: {
            float t = (float)player->level / 100.0;
            return 1.0 - (sin (t - M_PI / 2.0 ) + 1.0) / 2.0;
        }

    }
}

float HuNPCEnemyRanged::attackInterval() {
    
    HuPlayer *player = HuPlayer::getInstance();
    switch (player->level) {
        case 0 :
        case 1:
        case 2: {
            return 3.0;
        }
        case 3: {
            return 2.0;
        }
        case 4: {
            return 1.5;
        }
        case 5:{
            return 1.25;
        }
        case 6: {
            return 1.0;
        }
        default: {
            float t = (float)player->level / 100.0;
            return 1.0 - bezierat(0.34, 0.02, 0.34, 0.94, t);
        }
    }
}



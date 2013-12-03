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
    attackSpeed = 1;
    
}

void HuNPCEnemyRanged::setupActions() {
    
    int leftRight = (sprite->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    sprite->setScaleX(leftRight * sprite->getScaleX());
    
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (SCREEN_WIDTH / 4);
    float realFinalY = sprite->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
    
    CCFiniteTimeAction *move = CCMoveTo::create(CANNON_MOVEMENT_TIME, realDestination);
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
        this->schedule(schedule_selector(HuNPCEnemyRanged::attack), 1, kCCRepeatForever, 0);
    }
}

void HuNPCEnemyRanged::attack() {
    // do ranged attack
    HuProjectile *projectile = new HuProjectile;
    projectile->initForPlayerAttack(MISSILE, sprite->getPosition(), ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5), layer);
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
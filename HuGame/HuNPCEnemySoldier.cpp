//
//  HuNPCEnemySoldier.cpp
//  HuGame
//
//  Created by Tyler on 11/30/13.
//
//

#include "HuNPCEnemySoldier.h"
#include "HuPlayer.h"

using namespace cocos2d;

void HuNPCEnemySoldier::setupSprite() {
    sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("kitten_2.png", CCRectMake(0, 0, 40, 30)));
    sprite->setPosition(HuNPCEnemySoldier::generateEnemyInitialPoint());
    layer->addChild(sprite);
    layer->addChild(this);
}

void HuNPCEnemySoldier::setupStats() {
    health = 100;
    givesCurrency = 1;
    dealsDamage = 1;
    attackSpeed = 2;
    
}

void HuNPCEnemySoldier::setupActions() {
    HuPlayer *player = HuPlayer::getInstance();
    
    
    int leftRight = (sprite->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    
    // rotate image to it faces forwards
    sprite->setScaleX(leftRight * sprite->getScaleX());
    
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (player->baseWidth / 2);
    float realFinalY = sprite->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
    
    CCFiniteTimeAction *move = CCMoveTo::create(5.0, realDestination);
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuNPCEnemySoldier::enemyMoveFinished));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    sprite->runAction(actionSequence);
}

void HuNPCEnemySoldier::enemyMoveFinished(CCNode *sender) {

    // schedule attack
    this->schedule(schedule_selector(HuNPCEnemySoldier::attack), 1, kCCRepeatForever, 0);
}

void HuNPCEnemySoldier::attack() {
    // do basic attack
    if (sprite->isVisible()) {
        HuPlayer::getInstance()->health -= dealsDamage;
    }
}

void HuNPCEnemySoldier::killNPC() {
}

CCPoint HuNPCEnemySoldier::generateEnemyInitialPoint() {
    float x = 0;
    float y = 0;
    
    // decide if starting on left side or right side
    int leftRight = random() % 2;
    x = SCREEN_WIDTH * leftRight;
    
    y = random() % (int)GROUND_END_Y;
    y = MAX(y, 30);
    
    return ccp(x, y);
}


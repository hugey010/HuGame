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

void HuNPC::setupSprite() {
    sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("Player.png", CCRectMake(0, 0, 27, 40)));
    sprite->setPosition(this->generateEnemyInitialPoint());
    layer->addChild(sprite);
}

void HuNPC::setupStats() {
    health = 100;
    givesCurrency = 1;
    dealsDamage = 1;
    
}

void HuNPC::setupActions() {
    HuPlayer *player = HuPlayer::getInstance();
    
    
    int leftRight = (sprite->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (player->baseWidth / 2);
    float realFinalY = sprite->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
    
    CCFiniteTimeAction *move = CCMoveTo::create(5.0, realDestination);
    //CCFiniteTimeAction *scale = CCScaleBy::create(5.0, 5);
    //CCFiniteTimeAction *rotate = CCRotateBy::create(5.0, 10000);
    //CCFiniteTimeAction *moveBack = CCMoveTo::create(2.0, ccp(0, SCREEN_HEIGHT - 10));
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuNPC::enemyMoveFinished));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    sprite->runAction(actionSequence);
}

void HuNPC::enemyMoveFinished(CCNode *sender) {
    // begin basic attack
    if (sprite->isVisible()) {
        HuPlayer::getInstance()->health -= dealsDamage;
    }
}

void HuNPC::killNPC() {
    
}


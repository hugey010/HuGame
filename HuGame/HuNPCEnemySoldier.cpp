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
    health = 50;
    givesCurrency = 1;
    dealsDamage = 1;
    
}

void HuNPCEnemySoldier::setupActions() {
    HuPlayer *player = HuPlayer::getInstance();
    
    
    int leftRight = (sprite->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    
    // rotate image to it faces forwards
    sprite->setScaleX(leftRight * sprite->getScaleX());
    
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (player->baseWidth / 2);
    float realFinalY = sprite->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
    
    CCFiniteTimeAction *move = CCMoveTo::create(secondsToReachFinalPosition(), realDestination);
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuNPCEnemySoldier::enemyMoveFinished));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    sprite->runAction(actionSequence);
}

void HuNPCEnemySoldier::enemyMoveFinished(CCNode *sender) {

    // schedule attack
    float interval = attackInterval();
    if (sprite->isVisible()) {
        this->schedule(schedule_selector(HuNPCEnemySoldier::attack), interval, kCCRepeatForever, interval);
    }
}

void HuNPCEnemySoldier::attack() {
    // do basic attack
    if (sprite->isVisible()) {
        HuPlayer::getInstance()->health -= dealsDamage;
        
        // animate attack
        CCSprite *explosion = CCSprite::create("explosion_blue.png");
        CCFiniteTimeAction *scale = CCScaleBy::create(0.5, 0.2);
        CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuNPCEnemySoldier::attackActionFinished));
        CCArray *actionArray = CCArray::create();
        actionArray->addObject(scale);
        actionArray->addObject(finished);
        CCSequence *actionSequence = CCSequence::create(actionArray);
        explosion->setPosition(sprite->getPosition());
        layer->addChild(explosion);
        explosion->runAction(actionSequence);
    }
}

void HuNPCEnemySoldier::attackActionFinished(CCNode *sender) {
    CCSprite *sprite = (CCSprite*)sender;
    layer->removeChild(sprite);
}

void HuNPCEnemySoldier::killNPC() {
    this->unscheduleAllSelectors();
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

// seconds to reach final position
float HuNPCEnemySoldier::secondsToReachFinalPosition() {
    HuPlayer *player = HuPlayer::getInstance();
    switch (player->level) {
        case 0:
        case 1:
        case 2: {
            return 5.0;
        }
        case 3: {
            return 4.0;
        }
        case 4: {
            return 3.5;
        }
        case 5:{
            return 3.0;
        }
        case 6: {
            return 2.5;
        }
        case 7:{
            return 2.0;
        }
        case 8: {
            return 1.5;
        }
        case 9:{
            return 1.25;
        }
        case 10: {
            return 1.0;
        }
        default: {
            float t = (float)player->level / 100.0;
            return 1.0 - (sin (t - M_PI / 2.0 ) + 1.0) / 2.0;
        }
            
    }
}

float HuNPCEnemySoldier::attackInterval() {
    
    HuPlayer *player = HuPlayer::getInstance();
    float interval = 1.0;
    switch (player->level) {
        case 0 :
        case 1:
        case 2: {
            return interval = 3.0;
        }
        case 3: {
            return interval = 2.0;
        }
        case 4: {
            return interval = 1.5;
        }
        case 5:{
            return interval = 1.25;
        }
        case 6: {
            return interval = 1.0;
        }
        default: {
            float t = (float)player->level / 100.0;
            return 1.0 - bezierat(0.34, 0.02, 0.34, 0.94, t);
        }
            
    }
    return interval;
}




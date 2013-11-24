//
//  HuGoodNPC.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 11/18/13.
//
//

#include "HuGoodNPC.h"
#include "HuPlayer.h"
#include "Constants.h"
#include "HuProjectile.h"
#include "HuGameNPCs.h"

using namespace cocos2d;

bool HuGoodNPC::initialize() {
    
    if (!CCNode::init()) {
        return false;
    }
    
    float max = 5.0;
    float min = 1.0;
    
    switch (soldierType) {
        case SOLDIER_TYPE_SOLDIER : {
            sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("Target.png", CCRectMake(0, 0, 27, 40)));
            max = SOLDIER_MAX_FIRING_INTERVAL;
            min = SOLDIER_MIN_FIRING_INTERVAL;
            break;
        }
            
        case SOLDIER_TYPE_CANNON : {
            sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("missile_launcher.png", CCRectMake(0, 0, 144, 74)));
            sprite->setScale(0.5);
            max = CANNON_MAX_FIRING_INTERVAL;
            min = CANNON_MIN_FIRING_INTERVAL;
            break;
        }
    }
    
    sprite->setPosition(this->generateInitialPoint());
    layer->addChild(sprite);
    
    player = HuPlayer::getInstance();
    

    float range = max - min;
    attackTime = ((float)arc4random() / ARC4RANDOM_MAX) * range + min;
    this->scheduleAttackInSeconds(attackTime);
    
    return true;
}

void HuGoodNPC::initWithLayerAndNumberAndType(cocos2d::CCLayer *layer, int number, SoldierType type) {
    this->layer = layer;
    this->playerNumber = number;
    this->soldierType = type;
    this->initialize();
    
}

CCPoint HuGoodNPC::generateInitialPoint() {
    int minX = SCREEN_WIDTH / 2 - 100;
    int minY = SCREEN_HEIGHT / 2 - 200;
    int maxX = SCREEN_WIDTH / 2 + 100;
    int maxY = SCREEN_HEIGHT - 100;
    int xRandom = arc4random() % (maxX - minX) + minX;
    int yRandom = arc4random() % (maxY - minY) + minY;
    
    return ccp(xRandom, yRandom);
}

void HuGoodNPC::attack(CCNode *sender) {
    //int attackTime = arc4random() % 10 + 1;
    this->scheduleAttackInSeconds(attackTime);
    
   // HuGameNPCs::getNPCs();
    HuNPC *targetNPC = (HuNPC*)HuGameNPCs::getNPCs()->randomObject();
    HuProjectile *projectile = new HuProjectile;
    
    ProjectileType projectileType;
    switch (soldierType) {
        case SOLDIER_TYPE_CANNON : {
            
            projectileType = MISSILE;
            break;
        }
            
        case SOLDIER_TYPE_SOLDIER : {
            projectileType = BULLET;
            break;
        }
            
        default:
            projectileType = BULLET;
            break;
    }
    
    projectile->initWithMandatories(projectileType, sprite->getPosition(), targetNPC, layer);
    
}

void HuGoodNPC::scheduleAttackInSeconds(float seconds) {
    // TODO: this is pretty bad. Instead of just scheduleing a selector I'm moving a sprite to its current point for the amount of time
    
    CCFiniteTimeAction *attackFake = CCMoveTo::create(seconds, sprite->getPosition());
    CCFiniteTimeAction *attack = CCCallFuncN::create(this, callfuncN_selector(HuGoodNPC::attack));
    
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(attackFake);
    actionArray->addObject(attack);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    sprite->runAction(actionSequence);
}
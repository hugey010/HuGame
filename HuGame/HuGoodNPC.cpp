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
    
    float max;
    float min;
    
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
    layer->addChild((CCNode*)this);
    
    player = HuPlayer::getInstance();
    

    float range = max - min;
    attackTime = ((float)arc4random() / ARC4RANDOM_MAX) * range + min;
    
    this->schedule(schedule_selector(HuGoodNPC::attack), attackTime, kCCRepeatForever, 1);
    
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
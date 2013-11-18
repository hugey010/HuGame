//
//  HuProjectile.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 11/18/13.
//
//

#include "HuProjectile.h"

using namespace cocos2d;


bool HuProjectile::initialize() {
    switch (this->projectileType) {
        case MISSILE : {
            this->sprite = CCSprite::create("missile.png");
         
            break;
        }
        case BULLET : {
            
            break;
        }
    }
    
    sprite->setPosition(this->startingPosition);
    
    
    return true;
}

bool HuProjectile::initWithMandatories(ProjectileType type, CCPoint startingPosition, HuNPC *npc) {
    if (!CCNode::init()) {
        return false;
    }
    
    this->projectileType = type;
    this->startingPosition = startingPosition;
    this->npc = npc;
    
    // TODO: remove the debug
    this->projectileType = MISSILE;
    
    return initialize();
    
}


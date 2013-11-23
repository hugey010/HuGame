//
//  HuProjectile.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 11/18/13.
//
//

#include "HuProjectile.h"
#include "HuGameNPCs.h"
#include <math.h>

using namespace cocos2d;


bool HuProjectile::initialize() {
    switch (this->projectileType) {
        case MISSILE : {
            this->sprite = CCSprite::create("missile.png");
            sprite->setScale(0.2);
         
            break;
        }
        case BULLET : {
            
            break;
        }
    }
    
    sprite->setPosition(this->startingPosition);
    
    
    float ccangle = CC_RADIANS_TO_DEGREES(startingPosition.getAngle(npc->sprite->getPosition()));
    CCPoint endingPosition = npc->sprite->getPosition();
    
    float deltax = startingPosition.x - endingPosition.x;
    float deltay = startingPosition.y - endingPosition.y;
    float angleInDegrees = atan2(deltay, deltax) * 180.0 / M_PI;
    float angle = 0;
    
    if (npc->sprite->getPositionX() < SCREEN_WIDTH / 2) {
        angle = angleInDegrees + ccangle + 200;
    } else {
        angle = -1 * angleInDegrees - ccangle + 230;

    }
    //CCLog("initialAngle = %f, cocos2dAngle = %f, angleInDegrees = %f", sprite->getRotation(), otherAngle, angleInDegrees);
    sprite->setRotation(angle);
    
    float time = npc->sprite->getPosition().getDistance(startingPosition) * 0.002;
    CCFiniteTimeAction *move = CCMoveTo::create(time, npc->sprite->getPosition());
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuProjectile::projectileMoveFinished));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    sprite->runAction(actionSequence);
    
    
    layer->addChild(sprite);

    return true;
}

bool HuProjectile::initWithMandatories(ProjectileType type, CCPoint startingPosition, HuNPC *npc, CCLayer* layer) {
    if (!CCNode::init()) {
        return false;
    }
    
    this->projectileType = type;
    this->startingPosition = startingPosition;
    this->npc = npc;
    this->layer = layer;
    
    // TODO: remove the debug
    this->projectileType = MISSILE;
    
    return initialize();
    
}

void HuProjectile::projectileMoveFinished(CCNode *sender) {
    
    
    CCSprite *sprite = (CCSprite*)sender;
    
    int damage = 1;
    switch (projectileType) {
        case MISSILE : {
            damage = 50;
            
            break;
        }
        
        case BULLET : {
            
            break;
        }
        default:
            break;
    }
    
    if (npc->takeDamageFromNPC(damage)) {
        CCArray *npcs = HuGameNPCs::getNPCs();
        npcs->fastRemoveObject((CCNode*)npc);
        
    }
    
    
    // clean up the projectile and do explosion
    CCSprite *explosion = CCSprite::create("explosion_simple.png");
    CCFiniteTimeAction *scale = CCScaleBy::create(0.5, 0.2);
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuProjectile::explosionFinished));
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(scale);
    actionArray->addObject(finished);
    CCSequence *actionSequence = CCSequence::create(actionArray);
    explosion->setPosition(sprite->getPosition());
    layer->addChild(explosion);
    explosion->runAction(actionSequence);
    
    layer->removeChild(sprite);
    

}

void HuProjectile::explosionFinished(CCNode *sender) {
    CCSprite *sprite = (CCSprite*)sender;
    layer->removeChild(sprite);
}



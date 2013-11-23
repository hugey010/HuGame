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
    
    //float angle = CC_RADIANS_TO_DEGREES(startingPosition.getAngle(npc->sprite->getPosition()));
    

    /*
    if (npc->sprite->getPositionX() < startingPosition.x) {
        angle += 45.0;
    } else {
        angle -= 45.0;
    }
     */
    CCPoint endingPosition = npc->sprite->getPosition();
    
    float deltax = startingPosition.x - endingPosition.x;
    float deltay = startingPosition.y - endingPosition.y;
    float angleInDegrees = atan2(deltay, deltax) * 180.0 / M_PI;
    
    CCLog("angle = %f", angleInDegrees);
    if (angleInDegrees > 0) {
        angleInDegrees -= 180;
    }
    /*
    if (angleInDegrees < 0) {
        angleInDegrees -= 80;
    } else {
        angleInDegrees += 80;
    }
     */
    
    
 
    
    //angle = angle + 90.0;
    /*
    if (angle < 0) {
        angle += 270;
    } else {
        angle -= 270;
    }
     */
    
    sprite->setRotation(angleInDegrees + -180);
    
    float time = npc->sprite->getPosition().getDistance(startingPosition) * 0.002;
    CCFiniteTimeAction *move = CCMoveTo::create(time, npc->sprite->getPosition());
    //CCFiniteTimeAction *scale = CCScaleBy::create(5.0, 5);
    //CCFiniteTimeAction *rotate = CCRotateBy::create(5.0, 10000);
    //CCFiniteTimeAction *moveBack = CCMoveTo::create(2.0, ccp(0, SCREEN_HEIGHT - 10));
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



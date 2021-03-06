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
#include "Constants.h"

using namespace cocos2d;


bool HuProjectile::initialize() {
    
    if (!CCNode::init()) {
        return false;
    }
    float time = 0;
    
    
    switch (this->projectileType) {
        case MISSILE : {
            CCString *missileString = CCString::create("missile.png");
            if (npc == NULL) {
                // use blue missile becuase its an enemy attacking
                missileString = CCString::create("missile_blue.png");
            }
            this->sprite = CCSprite::create(missileString->getCString());
            sprite->setScale(0.2);
            sprite->setPosition(ccp(startingPosition.x - 40, startingPosition.y));

            time = endingPosition.getDistance(startingPosition) * 0.002;
            break;
        }
        case BULLET : {
            this->sprite = CCSprite::create("bullet.png");
            sprite->setScale(0.4);
            sprite->setPosition(this->startingPosition);

            time = endingPosition.getDistance(startingPosition) * 0.001;
            break;
        }
    }
    
    float angle = CC_RADIANS_TO_DEGREES(atan2(endingPosition.x - startingPosition.x, endingPosition.y - startingPosition.y));
    if(angle < 0){
        angle += 360;
    }

    sprite->setRotation(angle);
    
    CCFiniteTimeAction *move = CCMoveTo::create(time, endingPosition);
    
    
    // the ending selector depends on if this class is given an npc to attack
    SEL_CallFuncN func;
    if (npc != NULL) {
        func = callfuncN_selector(HuProjectile::projectileMoveFinished);
    } else {
        func = callfuncN_selector(HuProjectile::projectileToPlayerMoveFinished);
    }
    
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, func);
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    sprite->runAction(actionSequence);
    layer->addChild(sprite);

    return true;
}

bool HuProjectile::initWithMandatories(ProjectileType type, CCPoint startingPosition, HuNPC *npc, CCLayer* layer) {
    if (!npc->sprite->isVisible()) {
        return false;
    }

    this->endingPosition = npc->sprite->getPosition();
    this->startingPosition = startingPosition;
    this->npc = npc;
    this->layer = layer;
    this->projectileType = type;
    
    switch (type) {
        case MISSILE : {
            damage = GOOD_NPC_DAMAGE_MISSILE;
            
            break;
        }
            
        case BULLET : {
            damage = GOOD_NPC_DAMAGE_BULLET;
            
            break;
        }

    }
    
    return initialize();
}

bool HuProjectile::initForPlayerAttack(ProjectileType type, cocos2d::CCPoint startingPosition, cocos2d::CCPoint endingPosition, cocos2d::CCLayer *layer) {
    
    this->npc = NULL;
    this->endingPosition = endingPosition;
    this->projectileType = type;
    this->startingPosition = startingPosition;
    this->layer = layer;
    this->projectileType = type;
    
    switch (projectileType) {
        case MISSILE : {
            damage = 5;
            
            break;
        }
            
        case BULLET : {
            damage = 2;
            
            break;
        }
        default:
            damage = 1;
            break;
    }
    
    return initialize();
}

void HuProjectile::projectileMoveFinished(CCNode *sender) {
    
    CCSprite *sprite = (CCSprite*)sender;

    if (npc->takeDamageFromNPC(damage)) {
        CCArray *npcs = HuGameNPCs::getNPCs();
        npcs->fastRemoveObject((CCNode*)npc);
    }
    
    // clean up the projectile and do explosion
    CCSprite *explosion;
    if (projectileType == MISSILE) {
        explosion = CCSprite::create("explosion_simple_yellow.png");
        explosion->setScale(1.5);
    } else {
        explosion = CCSprite::create("explosion_simple.png");
    }
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

void HuProjectile::projectileToPlayerMoveFinished(cocos2d::CCNode *sender) {
    CCSprite *sprite = (CCSprite*)sender;
    
    HuPlayer::getInstance()->health -= damage;
    
    // clean up the projectile and do explosion
    CCSprite *explosion;
    if (projectileType == MISSILE) {
        explosion = CCSprite::create("explosion_simple_yellow.png");
        explosion->setScale(1.5);
    } else {
        explosion = CCSprite::create("explosion_simple.png");
    }
    
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



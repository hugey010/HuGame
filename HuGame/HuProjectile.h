//
//  HuProjectile.h
//  HuGame
//
//  Created by Tyler Hugenberg on 11/18/13.
//
//

#ifndef __HuGame__HuProjectile__
#define __HuGame__HuProjectile__

#include "cocos2d.h"
#include "HuNPC.h"

typedef enum {
    MISSILE,
    BULLET
} ProjectileType;

class HuProjectile : cocos2d::CCNode {
public:
    bool initWithMandatories(ProjectileType type, cocos2d::CCPoint startingPosition, HuNPC *npc, cocos2d::CCLayer *layer);
    bool initForPlayerAttack(ProjectileType type, cocos2d::CCPoint startingPosition, cocos2d::CCPoint endingPosition, cocos2d::CCLayer *layer);
    
protected:
    bool initialize();
    
private:
    cocos2d::CCSprite *sprite;
    ProjectileType projectileType;
    cocos2d::CCPoint startingPosition;
    cocos2d::CCPoint endingPosition;
    cocos2d::CCLayer *layer;
    HuNPC *npc;
    int damage;
    
    void projectileMoveFinished(CCNode *sender);
    void projectileToPlayerMoveFinished(CCNode *sender);
    void explosionFinished(CCNode *sender);
    
    
};

#endif /* defined(__HuGame__HuProjectile__) */

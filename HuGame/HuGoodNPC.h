//
//  HuGoodNPC.h
//  HuGame
//
//  Created by Tyler Hugenberg on 11/18/13.
//
//

#ifndef __HuGame__HuGoodNPC__
#define __HuGame__HuGoodNPC__

#include "cocos2d.h"
#include "HuPlayer.h"

#define PLACEMENT_SPOTS 6

typedef enum {
    SOLDIER_TYPE_SOLDIER,
    SOLDIER_TYPE_CANNON
} SoldierType;

class HuGoodNPC : cocos2d::CCNode {
public:
    cocos2d::CCSprite *sprite;
    int playerNumber;

    void initWithLayerAndNumberAndType(cocos2d::CCLayer *layer, int number, SoldierType type);
    
protected:
    bool initialize();
    
private:
    HuPlayer *player;
    
    cocos2d::CCLayer *layer;
    
    cocos2d::CCPoint point0;
    cocos2d::CCPoint point1;
    cocos2d::CCPoint point2;
    cocos2d::CCPoint point3;
    cocos2d::CCPoint point4;
    cocos2d::CCPoint point5;
    
    cocos2d::CCPoint generateInitialPoint();

    void attack(cocos2d::CCNode *sender);
    
    int scheduleID;
    float attackTime;
    SoldierType soldierType;
    
};

#endif /* defined(__HuGame__HuGoodNPC__) */

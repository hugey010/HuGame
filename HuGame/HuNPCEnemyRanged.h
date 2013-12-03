//
//  HuNPCEnemyRanged.h
//  HuGame
//
//  Created by Tyler on 12/1/13.
//
//

#ifndef __HuGame__HuNPCEnemyRanged__
#define __HuGame__HuNPCEnemyRanged__

#include "HuNPC.h"

class HuNPCEnemyRanged : HuNPC {
public:
    static cocos2d::CCPoint generateEnemyInitialPoint();
    void attack();
    
private:
    void setupSprite();
    void setupStats();
    void setupActions();
    void enemyMoveFinished(cocos2d::CCNode *sender);
    void killNPC();
    
    float secondsToReachFinalPosition();
    float attackInterval();

};

#endif /* defined(__HuGame__HuNPCEnemyRanged__) */

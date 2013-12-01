//
//  HuNPCEnemySoldier.h
//  HuGame
//
//  Created by Tyler on 11/30/13.
//
//

#ifndef __HuGame__HuNPCEnemySoldier__
#define __HuGame__HuNPCEnemySoldier__

#include "HuNPC.h"

class HuNPCEnemySoldier : HuNPC {
public:
    static cocos2d::CCPoint generateEnemyInitialPoint();
    void attack();

private:
};

#endif /* defined(__HuGame__HuNPCEnemySoldier__) */

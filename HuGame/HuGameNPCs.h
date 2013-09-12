//
//  HuGameNPCs.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#ifndef __HuGame__HuGameNPCs__
#define __HuGame__HuGameNPCs__

#include "cocos2d.h"
#include "HuPlayer.h"
#include "Constants.h"

class HuGameNPCs : cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuGameNPCs);
    
    // for handling attacks
    void handleAttack(cocos2d::CCPoint vertices[], int numberOfVertices, ElementalDamageTypes damageType);
        


private:
    void enemyMoveFinished(cocos2d::CCNode *sender);
    void makeEnemy();

};

#endif /* defined(__HuGame__HuGameNPCs__) */

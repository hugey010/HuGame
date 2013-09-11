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

class HuGameNPCs : cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuGameNPCs);
    
    // for handling attacks
    void handleAttack(cocos2d::CCPoint vertices[], int numberOfVertices);
    
    // create an npc class which gets extended by all your special objects. npc will have all the base features a class needs
    


private:
    void enemyMoveFinished(cocos2d::CCNode *sender);
    void makeEnemy();

};

#endif /* defined(__HuGame__HuGameNPCs__) */

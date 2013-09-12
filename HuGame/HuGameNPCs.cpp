//
//  HuGameNPCs.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#include "HuGameNPCs.h"
#include "Constants.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "HuNPC.h"

using namespace cocos2d;

CCArray *npcs = new CCArray;


bool HuGameNPCs::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //npcs = CCArray::createWithCapacity(1000);
    this->schedule(schedule_selector(HuGameNPCs::makeEnemy), 0.1, kCCRepeatForever, 0);
    
    return true;
}

void HuGameNPCs::makeEnemy()
{
    HuNPC *npc = new HuNPC;
    
    npc->initWithLayer(this);
    npcs->addObject((CCNode*)npc);
    

}

void HuGameNPCs::handleAttack(cocos2d::CCPoint vertices[], int numberOfVertices, ElementalDamageTypes damageType)
{
    CCLog("hugamenpcs handling attack");
    
    for (int i = 0; i < npcs->count(); i++) {
        HuNPC *npc = (HuNPC*)npcs->objectAtIndex(i);
        if (npc != NULL) {
            npc->takeDamageFromPlayer(damageType);
            npcs->removeObjectAtIndex(i);
        }
    }
    
    

    // loop through all active npcs and detect an attack
    // this is going to cause the npcs to be a class of its own hosting a ccsprite
    
    
    
    
}




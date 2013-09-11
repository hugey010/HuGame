//
//  HuGameNPCs.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#include "HuGameNPCs.h"
#include "Constants.h"
#include "HuPlayer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "HuNPC.h"

using namespace cocos2d;


bool HuGameNPCs::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->schedule(schedule_selector(HuGameNPCs::makeEnemy), 0.1, kCCRepeatForever, 0);
    
    return true;
}

void HuGameNPCs::makeEnemy()
{
    HuNPC *npc = new HuNPC;
    npc->initWithLayer(this);

}

void HuGameNPCs::handleAttack(cocos2d::CCPoint vertices[],int numberOfVertices)
{
    CCLog("hugamenpcs handling attack");

    // loop through all active npcs and detect an attack
    // this is going to cause the npcs to be a class of its own hosting a ccsprite
    
    
    
    
}




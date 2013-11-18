//
//  HuFriendlyNPCs.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 11/17/13.
//
//

#include "HuFriendlyNPCs.h"
#include "HuGoodNPC.h"
#include "HuPlayer.h"

using namespace cocos2d;

bool HuFriendlyNPCs::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    
    addBackgroundElements();
    
    addSoldiers();
    addCannons();
    
        
    return true;
}

void HuFriendlyNPCs::addBackgroundElements() {
    
}

void HuFriendlyNPCs::addSoldiers() {
    HuPlayer *player = HuPlayer::getInstance();
    
    for (int i = 0; i < player->numberOfSoldiers; i++) {
        HuGoodNPC *friendly = new HuGoodNPC;
        friendly->initWithLayerAndNumber(this, i);
    }
    
}

void HuFriendlyNPCs::addCannons() {
    
}
        
        

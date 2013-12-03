//
//  HuNPC.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 9/9/13.
//
//

#include "HuNPC.h"
#include "HuPlayer.h"

using namespace cocos2d;


bool HuNPC::initialize() {
    
    if (!CCNode::init()) {
        return false;
    }
    
    setupStats();
    setupSprite();
    setupActions();

    return true;
}

void HuNPC::initWithLayer(cocos2d::CCLayer *layer) {
    this->layer = layer;
    this->initialize();

}

bool HuNPC::takeDamageFromPlayer(ElementalDamageTypes damageType) {
    if (!sprite->isVisible()) {
        return false;
    }
    
    this->health -= HuPlayer::getInstance()->damageModifier;
    if (this->health <= 0) {
        sprite->setVisible(false);
        HuPlayer::getInstance()->currency += givesCurrency;
        
        unscheduleAllSelectors();
        
        // kill it and clean up npc
        killNPC();
        
        return true;
        
        
    }
    this->currentElementalDamage.insert(damageType);
    
    return false;
}

bool HuNPC::takeDamageFromNPC(int damage) {
    // don't do anything if the npc is already dead / invisible
    if (!sprite->isVisible()) {
        return false;
    }

    this->health -= damage;
    if (health <= 0) {
        sprite->setVisible(false);
        HuPlayer::getInstance()->currency += givesCurrency;
        
        killNPC();
        
        return true;
    }
    
    return false;
}

float HuNPC::bezierat( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a +
            3*t*(powf(1-t,2))*b +
            3*powf(t,2)*(1-t)*c +
            powf(t,3)*d );
}

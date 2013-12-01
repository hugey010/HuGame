//
//  HuNPC.h
//  HuGame
//
//  Created by Tyler Hugenberg on 9/9/13.
//
// NEVER INSTANTIATE THIS CLASS, ALWAYS INSTANTIATE ONE OF THE SUBCLASSES!!!


#ifndef __HuGame__HuNPC__
#define __HuGame__HuNPC__

#include "cocos2d.h"
#include "Constants.h"


class HuNPC : cocos2d::CCNode {
public:
    
    cocos2d::CCSprite *sprite;
    int health;
    int givesCurrency;
    int dealsDamage;
  
    void initWithLayer(cocos2d::CCLayer *layer);
    
    // return true if it kills the npc
    bool takeDamageFromPlayer(ElementalDamageTypes damageType);
    bool takeDamageFromNPC(int damage);
    
protected:
    // don't allow normal initialization - do not override
    bool initialize();
    
private:
    std::set<ElementalDamageTypes> currentElementalDamage;
    cocos2d::CCLayer *layer;
    
    // randomly makes a point on the ground on either the left or right side of screen
    static cocos2d::CCPoint generateEnemyInitialPoint();
    
    // REQUIRED: methods must be implemented by subclass
    void setupSprite();
    void setupStats();
    void setupActions();
    void enemyMoveFinished(cocos2d::CCNode *sender);
    void killNPC();

};

#endif /* defined(__HuGame__HuNPC__) */

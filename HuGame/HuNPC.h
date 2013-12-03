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


class HuNPC : public cocos2d::CCNode {
public:
    
    cocos2d::CCSprite *sprite;
    cocos2d::CCLayer *layer;
    int health;
    int givesCurrency;
    int dealsDamage;
    int attackSpeed;
  
    void initWithLayer(cocos2d::CCLayer *layer);
    
    // return true if it kills the npc
    bool takeDamageFromPlayer(ElementalDamageTypes damageType);
    bool takeDamageFromNPC(int damage);
    
protected:
    // don't allow normal initialization - do not override
    bool initialize();
    
private:
    std::set<ElementalDamageTypes> currentElementalDamage;
    
    // REQUIRED: methods must be implemented by subclass
    virtual void setupSprite(){};
    virtual void setupStats(){};
    virtual void setupActions(){};
    virtual void enemyMoveFinished(cocos2d::CCNode *sender){};
    virtual void killNPC(){};
    //virtual float secondsToReachFinalPosition();

};

#endif /* defined(__HuGame__HuNPC__) */

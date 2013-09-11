//
//  HuNPC.h
//  HuGame
//
//  Created by Tyler Hugenberg on 9/9/13.
//
//

#ifndef __HuGame__HuNPC__
#define __HuGame__HuNPC__

#include "cocos2d.h"
#include "Constants.h"

class HuNPC : cocos2d::CCNode {
public:
    
    //virtual bool init();
    //CREATE_FUNC(HuNPC);
    
    cocos2d::CCSprite *sprite;
    int health;
    int givesCurrency;
    int dealsDamage;
   
    // override init to change some of the base values the npc has
    void initialize();
    // this method should be overridden by subclass. do something useful with killin the ncp!
    void killNPC();
    
    void initWithLayer(cocos2d::CCLayer *layer);
    void takeDamageFromPlayer(int damage, ElementalDamageTypes damageType);
    
    // randomly makes a point on the ground on either the left or right side of screen
    static cocos2d::CCPoint generateEnemyInitialPoint();
    
    
private:
    void getKilled();
    std::set<ElementalDamageTypes> currentElementalDamage;
    cocos2d::CCLayer *layer;
    
    
    void enemyMoveFinished(cocos2d::CCNode *sender);


};

#endif /* defined(__HuGame__HuNPC__) */

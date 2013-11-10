//
//  HuEndRoundMenuScene.h
//  HuGame
//
//  Created by Tyler Hugenberg on 11/5/13.
//
//

#ifndef __HuGame__HuEndRoundMenuScene__
#define __HuGame__HuEndRoundMenuScene__

#include "cocos2d.h"

class HuEndRoundMenuScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HuEndRoundMenuScene);
    
    static cocos2d::CCScene* scene();
    void refreshLabels();
    
    // menu button callbacks
    void nextRoundPressed(CCObject* psender);
    void sellAllPressed(CCObject* psender);
    
    // upgrades for defense
    void addSoldierPressed(CCObject* sender);
    void minusSoldierPressed(CCObject *sender);
    void addCannonPressed(CCObject* sender);
    void minusCannonPressed(CCObject* sender);
   
    // upgrades for player
    void addHealthPressed(CCObject* sender);
};


#endif /* defined(__HuGame__HuEndRoundMenuScene__) */



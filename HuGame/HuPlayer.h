//
//  HuPlayer.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#ifndef __HuGame__HuPlayer__
#define __HuGame__HuPlayer__

#include "cocos2d.h"

class HuPlayer
{
public:
    static HuPlayer* getInstance();
    static HuPlayer* loadPlayerWithName(cocos2d::CCString *name);
    
    int health;
    int level;
    int currency;
    cocos2d::CCString *name;
    
    // fortress (base) info
    float baseWidth;
    float baseHeight;
    
    // attack info
    float attackWidth;
    
    void create();
    void save();
    
    
private:
    HuPlayer(){};
    HuPlayer(HuPlayer const&);       // Don't Implement
    void operator=(HuPlayer const&); // Don't implement
    
    static HuPlayer *mPInstance;
};

#endif /* defined(__HuGame__HuPlayer__) */
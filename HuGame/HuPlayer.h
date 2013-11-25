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
#include <string>

typedef enum  {
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD
} PlayerDifficulty;

typedef enum {
    DEFENSE_UPGRADE_0 = 0,
    DEFENSE_UPGRADE_1 = 1,
    DEFENSE_UPGRADE_2 = 2,
    DEFENSE_UPGRADE_3 = 3
} PlayerDefenseUpgrade;

class HuPlayer
{
public:
    static HuPlayer* getInstance();
    static bool loadLastPlayer();
    static int currentPlayerID();
    static bool loadPlayerWithID(int playerID);
   
    int playerID;
    int health;
    int maxHealth;
    int level;
    int currency;
    std::string name;
    int damageModifier;
    //cocos2d::CCString *name;
    PlayerDifficulty difficulty;
    PlayerDefenseUpgrade defenseUpgradeLevel;
    
    // fortress (base) info
    float baseWidth;
    float baseHeight;
    int numberOfSoldiers;
    int numberOfCannons;
    
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
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


class HuPlayer
{
public:
    static HuPlayer* getInstance();
    static void loadLastPlayer();
    static int currentPlayerID();
    static void loadPlayerWithID(int playerID);
    //static void setupDatabase();
   
    int playerID;
    int health;
    int level;
    int currency;
    std::string name;
    int damageModifier;
    //cocos2d::CCString *name;
    PlayerDifficulty difficulty;
    
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
//
//  HuPlayer.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#include "HuPlayer.h"
#include "cocos2d.h"

using namespace cocos2d;

HuPlayer* HuPlayer::mPInstance = NULL;

HuPlayer *HuPlayer::getInstance() {
    if (!mPInstance) {
        mPInstance = new HuPlayer;
    }
    return mPInstance;
}

void HuPlayer::create()
{
    this->health = 100;
    this->currency = 50; 
    // possibly start at level 0 as a demo or tutorial
    this->level = 1;
    this->name = CCStringMake("");


}
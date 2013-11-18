//
//  HuProjectile.h
//  HuGame
//
//  Created by Tyler Hugenberg on 11/18/13.
//
//

#ifndef __HuGame__HuProjectile__
#define __HuGame__HuProjectile__

#include "cocos2d.h"

typedef enum {
    MISSILE,
    BULLET
};

class HuProjectile : cocos2d::CCNode {
public:
    
private:
    cocos2d::CCSprite *sprite;
    
    
};

#endif /* defined(__HuGame__HuProjectile__) */

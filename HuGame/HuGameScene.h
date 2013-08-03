//
//  HuGameScene.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#ifndef __HuGame__HuGameScene__
#define __HuGame__HuGameScene__

#include "cocos2d.h"

class HuGameScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HuGameScene);
};

#endif /* defined(__HuGame__HuGameScene__) */

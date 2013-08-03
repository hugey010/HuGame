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
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HuGameScene);
    
    static cocos2d::CCScene* scene();
    

    
    // callback methods
    void endRoundCallback(CCObject* pSender);

};


#endif /* defined(__HuGame__HuGameScene__) */

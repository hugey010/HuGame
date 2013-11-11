//
//  HuLoserScene.h
//  HuGame
//
//  Created by Tyler Hugenberg on 11/10/13.
//
//

#ifndef __HuGame__HuLoserScene__
#define __HuGame__HuLoserScene__

#include "cocos2d.h"

class HuLoserScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuLoserScene);
    
    static cocos2d::CCScene* scene();
    
    void tryAgainCallback(CCObject* pSender);
    void mainMenuCallback(CCObject* pSender);
};

#endif /* defined(__HuGame__HuLoserScene__) */

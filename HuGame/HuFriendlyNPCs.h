//
//  HuFriendlyNPCs.h
//  HuGame
//
//  Created by Tyler Hugenberg on 11/17/13.
//
//

#ifndef __HuGame__HuFriendlyNPCs__
#define __HuGame__HuFriendlyNPCs__

#include "cocos2d.h"

class HuFriendlyNPCs : cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuFriendlyNPCs);
    
private:
    void addBackgroundElements();
    void addSoldiers();
    void addCannons();


};

#endif /* defined(__HuGame__HuFriendlyNPCs__) */

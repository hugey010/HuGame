//
//  HuGameAttacks.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/22/13.
//
//

#ifndef __HuGame__HuGameAttacks__
#define __HuGame__HuGameAttacks__

#include "cocos2d.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "HuGameNPCs.h"
#include "Constants.h"

#define kHitBoxWidth 32

class HuGameAttacks : cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuGameAttacks);
    
    // reference to npcs
    HuGameNPCs *npcs;
    
    
private:
    void didSwipe(cocos2d::CCObject *sender);
    cocos2d::CCRect rectBetweenPoints(cocos2d::CCPoint point1, cocos2d::CCPoint point2, CCSwipeGestureRecognizerDirection direction);
    void animateAttack(cocos2d::CCPoint *swipeVerts, int swipeVerticesCount, ElementalDamageTypes PhysicalDamage, CCSwipeGestureRecognizerDirection direction);
    void explosionFinished(cocos2d::CCNode *sender);

};

#endif /* defined(__HuGame__HuGameAttacks__) */

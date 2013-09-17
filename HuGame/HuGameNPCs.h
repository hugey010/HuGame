//
//  HuGameNPCs.h
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#ifndef __HuGame__HuGameNPCs__
#define __HuGame__HuGameNPCs__

#include "cocos2d.h"
#include "HuPlayer.h"
#include "Constants.h"

class HuGameNPCs : cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HuGameNPCs);
    
    // for handling attacks
    void handleAttack(cocos2d::CCPoint vertices[], int numberOfVertices, ElementalDamageTypes damageType);
        

    // stuff for collision detection
    // should all be static
    bool collisionBetween(cocos2d::CCPoint polygonVertices[], cocos2d::CCPoint spriteVerts[]);
    cocos2d::CCPoint normalizedVector(cocos2d::CCPoint vector);
    float dotProduct(cocos2d::CCPoint first, cocos2d::CCPoint second);
    void projectPolygonMinMax(cocos2d::CCPoint normalizedVector, cocos2d::CCPoint vertices[], float *max, float *min);
    float intervalDistance(float minA, float maxA, float minB, float maxB);
    bool axisSeparatePolygons(cocos2d::CCPoint edge, cocos2d::CCPoint polygonVertices[], cocos2d::CCPoint spriteVerts[]);
    bool areIntersecting(float v1x1, float v1y1, float v1x2, float v1y2,
                         float v2x1, float v2y1, float v2x2, float v2y2);

private:
    void enemyMoveFinished(cocos2d::CCNode *sender);
    void makeEnemy();
    
    



};

#endif /* defined(__HuGame__HuGameNPCs__) */

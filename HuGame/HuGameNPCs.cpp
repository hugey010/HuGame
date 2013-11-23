//
//  HuGameNPCs.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#include "HuGameNPCs.h"
#include "Constants.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"
#include "HuNPC.h"

using namespace cocos2d;

CCArray *npcs;

bool HuGameNPCs::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    npcs = new CCArray;
    
    //npcs = CCArray::createWithCapacity(1000);
    this->schedule(schedule_selector(HuGameNPCs::makeEnemy), 0.1, kCCRepeatForever, 0);
        
    return true;
}

void HuGameNPCs::makeEnemy()
{
    HuNPC *npc = new HuNPC;
    
    npc->initWithLayer(this);
    npcs->addObject((CCNode*)npc);

    

}

void HuGameNPCs::handleAttack(CCPoint vertices[], int numberOfVertices, ElementalDamageTypes damageType)
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(npcs, object) {
        
        HuNPC *tempNPC = (HuNPC*)object;
        
        if (tempNPC == NULL) {
            CCLog("null tempnpc");
        }
        if (tempNPC->sprite == NULL) {
            CCLog("null tmepsprite");
        }
        
        if (!tempNPC->sprite->isVisible()) {
            npcs->fastRemoveObject((CCNode*)tempNPC);
            continue;
        }
        

        // first test, just checks for obvious miss
        float minX = vertices[3].x;
        float maxX = vertices[3].x;
        float minY = vertices[3].y;
        float maxY = vertices[3].y;
        
        for (int i = 0; i < 3; i++) {
            
            minX = fminf(vertices[i].x, minX);
            minY = fminf(vertices[i].y, minY);
            maxX = fmaxf(vertices[i].x, maxX);
            maxY = fmaxf(vertices[i].y, maxY);
        }
        
        CCPoint p = tempNPC->sprite->getPosition();

        
        if (p.x < minX || p.x > maxX || p.y < minY || p.y > maxY) {
            continue;
        } else {
            // TODO: need to take damage properly.
            
            CCSprite *sprite = CCSprite::create("explosion_simple.png");
            CCFiniteTimeAction *scale = CCScaleBy::create(0.5, 0.2);
            
            CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuGameNPCs::explosionFinished));
            CCArray *actionArray = CCArray::create();
            actionArray->addObject(scale);
            actionArray->addObject(finished);
            CCSequence *actionSequence = CCSequence::create(actionArray);
            sprite->setPosition(tempNPC->sprite->getPosition());
            this->addChild(sprite);
            sprite->runAction(actionSequence);
            
            // have to remove npc after using its position
            


            if (tempNPC->takeDamageFromPlayer(damageType)) {
                npcs->fastRemoveObject((CCNode*)tempNPC);

            }
            
            
            
            /*
            bool c = false;
            int i = 0, j = 0;
            for (i = 0, j = 3; i < 4; j = i++) {
                if (((vertices[i].y > p.y) != (vertices[j].y > p.y)) &&
                    (p.x < (vertices[j].x - vertices[i].x) * (p.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x)) {
                    c = !c;
                }
            }
            if (c) {
                tempNPC->sprite->removeFromParent();
                npcs->fastRemoveObject((CCNode*)tempNPC);
            }
             */


        }
        

    }


    
}

bool HuGameNPCs::pointCollision(CCPoint polygonVertices[], CCPoint point) {
    return true;
}

// detects collision between 4 sided polygon and sprite bounding box
bool HuGameNPCs::collisionBetween(CCPoint polygonVertices[], CCPoint spriteVerts[]) {
   

    // a side is a pair of connected vertices
    int intersections = 0;
    
    CCPoint polyEdges[4][2];
    CCPoint spriteEdges[4][2];
    for (int i = 0; i < 4; i++) {
        int secondVertex = i+1;
        if (secondVertex == 4) {
            secondVertex = 0;
        }
        polyEdges[i][0] = ccp(polygonVertices[i].x, polygonVertices[i].y);
        polyEdges[i][1] = ccp(polygonVertices[secondVertex].x, polygonVertices[secondVertex].y);
        
        // drawing dot for polygon edge 1
        CCSprite *dot1 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot1.png", CCRectMake(0, 0, 20, 20)));
        dot1->setPosition(polyEdges[i][0]);
        //this->addChild(dot1);
        
        CCSprite *dot2 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
        dot2->setPosition(polyEdges[i][1]);
        this->addChild(dot2);
        
        spriteEdges[i][0] = ccp(spriteVerts[i].x, spriteVerts[i].y);
        spriteEdges[i][1] = ccp(spriteVerts[secondVertex].x, spriteVerts[secondVertex].y);

    }
    
    for (int side = 0; side < 4; side++) {
        // Test if current side intersects with ray.

        if (areIntersecting(polyEdges[side][0].x, polyEdges[side][0].y, polyEdges[side][1].x, polyEdges[side][1].y, spriteEdges[side][0].x, spriteEdges[side][0].y, spriteEdges[side][1].x, spriteEdges[side][1].y)) {
            intersections++;
        }
    }
    if ((intersections & 1) == 1) {
        // Inside of polygon
        return true;
    } else {
        // Outside of polygon
        return false;
    }
    //return false;
}

/*
#define NO 0
#define YES 1
#define COLLINEAR 2
 */

bool HuGameNPCs::areIntersecting(float v1x1, float v1y1, float v1x2, float v1y2,
                    float v2x1, float v2y1, float v2x2, float v2y2)
{
    float d1, d2;
    float a1, a2, b1, b2, c1, c2;
    
    // Convert vector 1 to a line (line 1) of infinite length.
    // We want the line in linear equation standard form: A*x + B*y + C = 0
    // See: http://en.wikipedia.org/wiki/Linear_equation
    a1 = v1y2 - v1y1;
    b1 = v1x1 - v1x2;
    c1 = (v1x2 * v1y1) - (v1x1 * v1y2);
    
    // Every point (x,y), that solves the equation above, is on the line,
    // every point that does not solve it, is either above or below the line.
    // We insert (x1,y1) and (x2,y2) of vector 2 into the equation above.
    d1 = (a1 * v2x1) + (b1 * v2y1) + c1;
    d2 = (a1 * v2x2) + (b1 * v2y2) + c1;
    
    // If d1 and d2 both have the same sign, they are both on the same side of
    // our line 1 and in that case no intersection is possible. Careful, 0 is
    // a special case, that's why we don't test ">=" and "<=", but "<" and ">".
    if (d1 > 0 && d2 > 0) return true;
    if (d1 < 0 && d2 < 0) return false;
    
    // We repeat everything above for vector 2.
    // We start by calculating line 2 in linear equation standard form.
    a2 = v2y2 - v2y1;
    b2 = v2x1 - v2x2;
    c2 = (v2x2 * v1y1) - (v2x1 * v2y2);
    
    // Calulate d1 and d2 again, this time using points of vector 1
    d1 = (a2 * v1x1) + (b2 * v1y1) + c2;
    d2 = (a2 * v1x2) + (b2 * v1y2) + c2;
    
    // Again, if both have the same sign (and neither one is 0),
    // no intersection is possible.
    if (d1 > 0 && d2 > 0) return false;
    if (d1 < 0 && d2 < 0) return false;
    
    // If we get here, only three possibilities are left. Either the two
    // vectors intersect in exactly one point or they are collinear
    // (they both lie both on the same infinite line), in which case they
    // may intersect in an infinite number of points or not at all.
    if ((a1 * b2) - (a2 * b1) == 0.0f) return true; // colinear
    
    // If they are not collinear, they must intersect in exactly one point.
    return true;
}

bool HuGameNPCs::axisSeparatePolygons(CCPoint edge, CCPoint polygonVertices[], CCPoint spriteVerts[]) {
    float minA = 0.0f, minB = 0.0f, maxA = 0.0f, maxB = 0.0f;
    
    projectPolygonMinMax(edge, polygonVertices, &maxA, &minA);
    projectPolygonMinMax(edge, spriteVerts, &maxB, &minB);
    
    if (minA > maxB || minB > maxA) {
        return true;
    } else {
        return false;
    }
}

float HuGameNPCs::intervalDistance(float minA, float maxA, float minB, float maxB) {
    if (minA < minB) {
        return minB - maxA;
    } else {
        return minA - maxB;
    }
}

// again assuming eash shape only has 4 sides
// alters the values of max and min, basically the side effect and only usage of this 'function'
void HuGameNPCs::projectPolygonMinMax(CCPoint normalizedVector, CCPoint vertices[], float *max, float *min) {
    float dotProduct = HuGameNPCs::dotProduct(normalizedVector, vertices[0]);
    min = &dotProduct;
    max = &dotProduct;
    for (int i = 0; i < 4; i++) {
        
        float nextDotProduct = HuGameNPCs::dotProduct(normalizedVector, vertices[i]);
        float newMin = fminf(nextDotProduct, *min);
        //CCLog("min = %f, max = %f", *min, *max);
        min = &newMin;
        float newMax = fmaxf(nextDotProduct, *max);
        max = &newMax;
        
    }
}

CCPoint HuGameNPCs::normalizedVector(CCPoint vector) {
    
    //CCLog("vectorToNormal x = %f, y = %f", vector.x, vector.y);
    float size = sqrtf(vector.x * vector.x + vector.y * vector.y);
    CCPoint point = ccp(vector.y / size, vector.x / size);
    
    //CCLog("normalizedVector x = %f, y = %f", point.x, point.y);
    
    return point;
     
}

// assumes is 1x2 and 2x1 vectors respectively
float HuGameNPCs::dotProduct(cocos2d::CCPoint first, cocos2d::CCPoint second) {
    return first.x * second.x + first.y * second.y;
}

void HuGameNPCs::removeAllEnemies() {
    CCObject *object = NULL;
    CCARRAY_FOREACH(npcs, object) {
        HuNPC *tempNPC = (HuNPC*)object;
        tempNPC->sprite->removeFromParent();
        npcs->fastRemoveObject((CCNode*)tempNPC);
    }
    return;
}

void HuGameNPCs::explosionFinished(cocos2d::CCNode *node) {
    CCSprite *sprite = (CCSprite *)node;
    sprite->removeFromParent();
}

CCArray *HuGameNPCs::getNPCs() {
    return npcs;
}





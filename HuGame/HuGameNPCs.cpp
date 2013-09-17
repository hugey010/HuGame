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

CCArray *npcs = new CCArray;


bool HuGameNPCs::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
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
    //CCLog("hugamenpcs handling attack");
    
    for (int i = 0; i < npcs->count(); i++) {
        HuNPC *npc = (HuNPC*)npcs->objectAtIndex(i);
        if (npc != NULL) {
            // check for collision
            //npc->sprite->getS
           // npc->sprite->getContentSize().width
            // get sprite points
            CCRect spriteRect = npc->sprite->boundingBox();
            CCPoint spritePoint1 = ccp(spriteRect.origin.x, spriteRect.origin.y);
            CCPoint spritePoint2 = ccp(spriteRect.origin.x + spriteRect.size.width, spriteRect.origin.y + spriteRect.size.height);
            CCPoint spritePoint3 = ccp(spriteRect.origin.x + spriteRect.size.width, spriteRect.origin.y);
            CCPoint spritePoint4 = ccp(spriteRect.origin.x, spriteRect.origin.y + spriteRect.size.height);
            
            CCPoint spriteVerts[] = {spritePoint1, spritePoint2, spritePoint3, spritePoint4};

           // collisionBetween(vertices, spriteVerts);
            if (collisionBetween(vertices, spriteVerts)) {
                this->removeChild(npc->sprite);
                npcs->removeObjectAtIndex(i);
                CCLog("hit an object");
            }
            
            
            
            
            /*
            CCLog("x = %f, y = %f, width = %f, height = %f", npc->sprite->getPosition().x, npc->sprite->getPosition().y, npc->sprite->getContentSize().width, npc->sprite->getContentSize().height);
            
            CCRect npcRect = CCRectMake(npc->sprite->getPosition().x, npc->sprite->getPosition().y, npc->sprite->getContentSize().width, npc->sprite->getContentSize().height);
            for (int j = 0; j < 4; j++) {
                CCLog("vertices[j].x = %f, vertices[j].y = %f", vertices[j].x, vertices[j].y);
                if (npcRect.containsPoint(ccp(vertices[j].x, vertices[j].y))) {
                    if (npc->takeDamageFromPlayer(damageType)) {
                        this->removeChild(npc->sprite);
                        npcs->removeObjectAtIndex(i);
                        CCLog("hit an object");
                    }
 
                    break;
                }
            }
             */
            
            //CCLog("sprite position.x = %f, y = %f", npc->sprite->getPosition().x, npc->sprite->getPosition().y);
            
        }
    }
    
    

    // loop through all active npcs and detect an attack
    // this is going to cause the npcs to be a class of its own hosting a ccsprite
    
    
    
    
}

// detects collision between 4 sided polygon and sprite bounding box
bool HuGameNPCs::collisionBetween(CCPoint polygonVertices[], CCPoint spriteVerts[]) {
   
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 1; j++) {
            CCPoint vectors[] = {polygonVertices[0], polygonVertices[1], polygonVertices[2], polygonVertices[3]};
            if (j == 0) {
                for (int k = 0; k < 4; k++) {
                    vectors[i] = spriteVerts[i];
                }
            }
            
            
            for (int edgeCounter = 0; edgeCounter < 4; edgeCounter++) {
                int pointCounter2 = edgeCounter - 1;
                if (pointCounter2 == -1) {
                    pointCounter2 = 4;
                }
                
                // debug for drawing dot where edge should be
                // need the -y component for edge
                // and x component
                vectors[edgeCounter] = normalizedVector(vectors[edgeCounter]);
                vectors[pointCounter2] = normalizedVector(vectors[pointCounter2]);
                CCPoint edge = ccp(-1 * (vectors[edgeCounter].y - vectors[pointCounter2].y), vectors[edgeCounter].x - vectors[pointCounter2].x);
                CCSprite *dot1 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot1.png", CCRectMake(0, 0, 20, 20)));
                dot1->setPosition(edge);
                //CCLog("edge x = %f, edge y = %f", edge.x, edge.y);
                this->addChild(dot1);
                
                //CCLog("edge.x = %f, edge.y = %f", edge.x, edge.y);
                if (axisSeparatePolygons(edge, polygonVertices, spriteVerts)) {
                    return false;
                }
                
            }
            
            
            /*
            CCPoint normalizedVector = HuGameNPCs::normalizedVector(vectors[i]);
            float minA = 0.0f, minB = 0.0f, maxA = 0.0f, maxB = 0.0f;

            HuGameNPCs::projectPolygonMinMax(normalizedVector, vectors, &maxA, &minA);
            HuGameNPCs::projectPolygonMinMax(normalizedVector, vectors, &maxB, &minB);
          
            //CCLog("minA = %f, minB = %f, maxA = %f, maxB = %f", minA, minB, maxA, maxB);
 

            if (HuGameNPCs::intervalDistance(minA, maxA, minB, maxB) <= 0) {
                return true;
            }
            
            return false;
             */
        }
        
    }
  
    /*
    // get polygon points
    CCPoint polygonPoint1 = ccp(polygonVertices[0].x, polygonVertices[0].y);
    CCPoint polygonPoint2 = ccp(polygonVertices[1].x, polygonVertices[1].y);
    CCPoint polygonPoint3 = ccp(polygonVertices[2].x, polygonVertices[2].y);
    CCPoint polygonPoint4 = ccp(polygonVertices[3].x, polygonVertices[3].y);
   

   
    // normalize each vector
    CCPoint normalPolyVector1 = HuGameNPCs::normalizedVector(polygonPoint1);
    CCPoint normalPolyVector2 = HuGameNPCs::normalizedVector(polygonPoint2);
    CCPoint normalPolyVector3 = HuGameNPCs::normalizedVector(polygonPoint3);
    CCPoint normalPolyVector4 = HuGameNPCs::normalizedVector(polygonPoint4);

    // project polygon onto axis. need min / max values
    float dotProductPoly1 = HuGameNPCs::dotProduct(normalPolyVector1, polygonPoint1);
    float minDot = dotProductPoly1;
    float maxDot = dotProductPoly1;
     */
    
    
    
 
    return false;
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





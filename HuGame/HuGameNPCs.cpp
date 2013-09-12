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

            collisionBetween(vertices, spriteVerts);
            /*
            if (collisionBetween(vertices, spriteVerts)) {
                this->removeChild(npc->sprite);
                npcs->removeObjectAtIndex(i);
                CCLog("hit an object");
            }
            */
            
            
            
            
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
        CCPoint normalizedVector = HuGameNPCs::normalizedVector(polygonVertices[i]);
        
    }
   
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
    
 
    return true;
}

// again assuming eash shape only has 4 sides
void HuGameNPCs::projectPolygon(CCPoint normalizedVector, CCPoint polygonVertices[], CCPoint spriteVertices[], int &max, int &min) {
    
}

CCPoint HuGameNPCs::normalizedVector(CCPoint vector) {
    float size = sqrtf(vector.x * vector.x + vector.y * vector.y);
    return ccp(vector.x / size, vector.y / size);
}

// assumes is 1x2 and 2x1 vectors respectively
float HuGameNPCs::dotProduct(cocos2d::CCPoint first, cocos2d::CCPoint second) {
    return first.x * second.x + first.y * second.y;
}





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
            if (collisionBetween(vertices, npc->sprite)) {
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

static bool collisionBetween(cocos2d::CCPoint vertices[], cocos2d::CCSprite *sprite) {
   
    // get polygon points
    CCPoint polygonPoint1 = ccp(vertices[0].x, vertices[0].y);
    CCPoint polygonPoint2 = ccp(vertices[1].x, vertices[1].y);
    CCPoint polygonPoint3 = ccp(vertices[2].x, vertices[2].y);
    CCPoint polygonPoint4 = ccp(vertices[3].x, vertices[3].y);
   
    // get sprite points
    CCRect spriteRect = sprite->boundingBox();
    CCPoint spritePoint1 = ccp(spriteRect.origin.x, spriteRect.origin.y);
    CCPoint spritePoint2 = ccp(spriteRect.origin.x + spriteRect.size.width, spriteRect.origin.y + spriteRect.size.height);
    CCPoint spritePoint3 = ccp(spriteRect.origin.x + spriteRect.size.width, spriteRect.origin.y);
    CCPoint spritePoint4 = ccp(spriteRect.origin.x, spriteRect.origin.y + spriteRect.size.height);
    
    // project every edge normal
    
        //CCPoint spritePoint1 = ccp(sprite->)
 
    
    //ccVertex2F vert = vertex2(0, 0);
    
    
    return false;
}






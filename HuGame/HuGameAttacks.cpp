//
//  HuGameAttacks.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/22/13.
//
//

#include "HuGameAttacks.h"
#include "HuPlayer.h"

using namespace cocos2d;

bool HuGameAttacks::init()
{
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // some gesture recognizer stuff
    CCSwipeGestureRecognizer *swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(HuGameAttacks::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft | kSwipeGestureRecognizerDirectionRight);
    //swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
    
    return true;
}


void HuGameAttacks::didSwipe(CCObject *sender)
{
    CCSwipe *swipe = (CCSwipe*)sender;
    
    // cancel swipe if it crosses center of screen (exactly)
    /*
    if (swipe->location.x < SCREEN_WIDTH / 2.0) {
        // swipe starts on left side of screen
        if (swipe->finalLocation.x - SWIPE_BASE_BUFFER > SCREEN_WIDTH / 2.0) {
            return;
        }
        
        
    } else {
        // swipe starts on right side of screen
        if (swipe->finalLocation.x + SWIPE_BASE_BUFFER < SCREEN_WIDTH / 2.0) {
            return;
        }
        
    }
     */
    

    
    // some logic for manipulating points according to the angle between swipe start and end
    float deltaX = swipe->finalLocation.x - swipe->location.x;
    float deltaY = swipe->finalLocation.y - swipe->location.y;
    //CCLog("deltay = %f, deltax = %f", deltaY, deltaX);
    float angleInDegrees = atan2f(deltaY, deltaX) * 180.0 / M_PI;
    
    //CCLog("angleInDegrees = %f, cosf = %f, sinf = %f, tanf = %f", angleInDegrees, cosf(angleInDegrees), sinf(angleInDegrees), tanf(angleInDegrees));
    
    float widthOffset = HuPlayer::getInstance()->attackWidth / 2.0;
    CCPoint point1 =  ccp(swipe->finalLocation.x + widthOffset * cosf(angleInDegrees), swipe->finalLocation.y + widthOffset * sinf(angleInDegrees));
    CCPoint point2 =  ccp(swipe->finalLocation.x - widthOffset * cosf(angleInDegrees), swipe->finalLocation.y - widthOffset * sinf(angleInDegrees));
    CCPoint point3 =  ccp(swipe->location.x + widthOffset * cosf(angleInDegrees), swipe->location.y + widthOffset * sinf(angleInDegrees));
    CCPoint point4 =  ccp(swipe->location.x - widthOffset * cosf(angleInDegrees), swipe->location.y - widthOffset * sinf(angleInDegrees));
    
    // draw  the attack hitting ground
    
    // drawing dots for help
   /*
    CCSprite *dot1 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot1->setPosition(point1);
    this->addChild(dot1);
    
    CCSprite *dot2 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot2->setPosition(point2);
    this->addChild(dot2);
    
    CCSprite *dot3 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot3->setPosition(point3);
    this->addChild(dot3);
    
    CCSprite *dot4 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot4->setPosition(point4);
    this->addChild(dot4);
     */
   
    // weird issue with ccdrawpoly, but fuck it. its probably not how im going to be drawing my attacks anyways
    int swipeVerticesCount = 4;
    CCPoint swipeVerts[] = {point1, point2, point3, point4};
    //CCDrawNode *drawNode = CCDrawNode::create();
    //drawNode->drawPolygon(swipeVerts, swipeVerticesCount, ccc4f(1,0,0,1), 3, ccc4f(1,1,1,1));
    //this->addChild(drawNode);
    
    
    // send this rect to npc controller to determine if there is a collision
    this->animateAttack(swipeVerts, swipeVerticesCount, PhysicalDamage, swipe->direction);
    
    
    // TODO: hard coding a damage type
    this->npcs->handleAttack(swipeVerts, swipeVerticesCount, PhysicalDamage);
}

void HuGameAttacks::animateAttack(CCPoint *swipeVerts, int swipeVerticesCount, ElementalDamageTypes PhysicalDamage, CCSwipeGestureRecognizerDirection direction) {
    float maxDistance = 0;
    float minX = SCREEN_WIDTH;
    
    CCPoint point1;
    CCPoint point2;
    

    for (int i = 0; i < swipeVerticesCount; i++) {
        for (int j = 3; j > i; j--) {
            float distance = sqrtf(powf(swipeVerts[i].x - swipeVerts[j].x, 2) + powf(swipeVerts[i].y - swipeVerts[j].y, 2));
            
            if (maxDistance < distance) {
                maxDistance = distance;
                
                point1 = swipeVerts[i];
                point2 = swipeVerts[j];
                
                minX = fminf(point1.x, minX);
                minX = fminf(point2.x, minX);
            }
        }
        
    }
   
    CCLog("minx = %f", minX);
    CCLog("maxDistance = %f", maxDistance);
    

    float slope = (point2.y - point1.y) / (point2.x - point1.x);
    CCLog("slope = %f", slope);
    
    
    int numberOfExplosions = 50;
    int randomness = 10;
    int xStep = maxDistance / numberOfExplosions;
    CCLog("xstep = %d", xStep);
    
    
    for (int i = 0; i < numberOfExplosions; i++) {
    
        float x = i * xStep + minX;
        float y = slope * (x - point1.x) + point1.y;
        y = y - arc4random() % randomness;
        y = y + arc4random() % randomness;
        
        x = x - arc4random() % randomness;
        x = x + arc4random() % randomness;
        
        
        CCFiniteTimeAction *scale = CCScaleBy::create(0.4, 10);
        CCFiniteTimeAction *rotate = CCRotateBy::create(0.4, 360);
        CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuGameAttacks::explosionFinished));
        
        CCArray *actionArray = CCArray::create();
        //actionArray->addObject(scale);
        actionArray->addObject(rotate);
        actionArray->addObject(finished);
       
        CCSequence *actionSequence = CCSequence::create(actionArray);

        
        CCSprite *sprite;
        if (direction == kSwipeGestureRecognizerDirectionDown || direction == kSwipeGestureRecognizerDirectionUp) {
            sprite = CCSprite::create("dot1.png", CCRectMake(0, 0, 2, 2));
        } else {
           sprite = CCSprite::create("dot2.png", CCRectMake(0, 0, 2, 2));
 
        }
        
        sprite->setPosition(ccp(x, y));
        sprite->runAction(actionSequence);
        sprite->runAction(scale);
        sprite->runAction(rotate);
        this->addChild(sprite);
        
    }

    


    
    
}

void HuGameAttacks::explosionFinished(CCNode *sender) {
    CCSprite *sprite = (CCSprite*)sender;
    sprite->removeFromParent();
}

void HuGameAttacks::draw() {
    
}

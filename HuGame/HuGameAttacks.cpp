//
//  HuGameAttacks.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/22/13.
//
//

#include "HuGameAttacks.h"
#include "Constants.h"
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
    // TODO: hard coding a damage type
    this->npcs->handleAttack(swipeVerts, swipeVerticesCount, PhysicalDamage);
}

/*
 Returns rect zero if the swipe is invalid. Otherwise returns the rect.
 will either be a vertical or horizontal rectangle with a constant width / height
 need to keep track if swipe is on left or right of screen (aka do not allow entire screen swipes)
 */
CCRect HuGameAttacks::rectBetweenPoints(CCPoint point1, CCPoint point2, CCSwipeGestureRecognizerDirection direction)
{
    CCRect rect = CCRectZero;
    if ((point1.x < SCREEN_WIDTH / 2 && point2.x < SCREEN_WIDTH / 2) || (point1.x > SCREEN_WIDTH / 2 && point2.x > SCREEN_WIDTH / 2))
    {
        // the first point is going to be based on the swipe direction
        // the standard will be to use the first point as the starting x / y coordinate
        switch (direction) {
            case kSwipeGestureRecognizerDirectionLeft:
                rect = CCRectMake(point1.x - abs(point1.x - point2.x), point1.y - kHitBoxWidth / 2, abs(point1.x - point2.x), kHitBoxWidth);
                
                break;
            case kSwipeGestureRecognizerDirectionRight:
                rect = CCRectMake(point1.x, point1.y - kHitBoxWidth / 2, abs(point1.x - point2.x), kHitBoxWidth);
                
                break;
            case kSwipeGestureRecognizerDirectionDown:
                rect = CCRectMake(point1.x - kHitBoxWidth / 2, point1.y - abs(point1.y - point2.y), kHitBoxWidth, abs(point1.y - point2.y));
                
                break;
            case kSwipeGestureRecognizerDirectionUp:
                rect = CCRectMake(point1.x - kHitBoxWidth / 2, point1.y, kHitBoxWidth, abs(point1.y - point2.y));
                
                break;
                
        }

    }
    return rect;
    
}

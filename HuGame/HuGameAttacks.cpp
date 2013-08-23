//
//  HuGameAttacks.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/22/13.
//
//

#include "HuGameAttacks.h"
#include "Constants.h"

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
    swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
    
    return true;
}


void HuGameAttacks::didSwipe(CCObject *sender)
{
    CCSwipe *swipe = (CCSwipe*)sender;
    
    CCSprite *dot1 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot1->setPosition(swipe->location);
    this->addChild(dot1);
    
    CCSprite *dot2 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot2->setPosition(swipe->finalLocation);
    this->addChild(dot2);
    

    CCRect rect = this->rectBetweenPoints(swipe->location, swipe->finalLocation, swipe->direction);
    
    // send this rect to npc controller to determine if there is a collision
}

/*
 Returns rect zero if the swipe is invalid. Otherwise returns the rect.
 will either be a vertical or horizontal rectangle with a constant width / height
 need to keep track if swipe is on left or right of screen (aka do not allow entire screen swipes)
 */
CCRect rectBetweenPoints(CCPoint point1, CCPoint point2, CCSwipeGestureRecognizerDirection direction)
{
    if ((point1.x < SCREEN_WIDTH / 2 && point2.x < SCREEN_WIDTH / 2) || (point1.x > SCREEN_WIDTH / 2 && point2.x > SCREEN_WIDTH / 2))
    {
        if (direction == kSwipeGestureRecognizerDirectionDown || direction == kSwipeGestureRecognizerDirectionUp)
        {
            // x of first point - half of hit box width
            // y is lower of both points
            // width = box width
            // height = distancy between y's
            return CCRectMake(point1.x - kHitBoxWidth / 2, MIN(point1.y, point2.y), kHitBoxWidth,  abs(point1.y - point2.y));
        }
        else if (direction == kSwipeGestureRecognizerDirectionLeft || direction == kSwipeGestureRecognizerDirectionRight)
        {
            // x lower of both points 
            // y is y of first point - half hit box width 
            // width = distance between x's
            // height = box width
            return CCRectMake(MIN(point1.x, point2.x), point1.y - kHitBoxWidth / 2, abs(point1.x - point2.x), kHitBoxWidth);
        }
    }
    else
    {
        return CCRectZero;
    }
}

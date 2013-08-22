//
//  HuGameNPCs.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/6/13.
//
//

#include "HuGameNPCs.h"
#include "Constants.h"
#include "HuPlayer.h"
#include "CCGestureRecognizer/CCSwipeGestureRecognizer.h"

using namespace cocos2d;

bool HuGameNPCs::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->schedule(schedule_selector(HuGameNPCs::makeEnemy), 0.1, kCCRepeatForever, 0);
    //this->schedule(schedule_selector(HuGameNPCs::makeEnemy), 0.1, kCCRepeatForever, 0);
    
    // some gesture recognizer stuff
    CCSwipeGestureRecognizer *swipe = CCSwipeGestureRecognizer::create();
    swipe->setTarget(this, callfuncO_selector(HuGameNPCs::didSwipe));
    swipe->setDirection(kSwipeGestureRecognizerDirectionDown | kSwipeGestureRecognizerDirectionUp | kSwipeGestureRecognizerDirectionLeft | kSwipeGestureRecognizerDirectionRight);
    swipe->setCancelsTouchesInView(true);
    this->addChild(swipe);
 
    return true;
}

void HuGameNPCs::makeEnemy()
{
        
    CCSprite *enemy = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("Player.png", CCRectMake(0, 0, 20, 20)));
    enemy->setPosition(this->generateEnemyInitialPoint());
    this->addChild(enemy);
    
    
    HuPlayer *player = HuPlayer::getInstance();
    
    
    int leftRight = (enemy->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (player->baseWidth / 2);
    float realFinalY = enemy->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
    
    CCFiniteTimeAction *move = CCMoveTo::create(5.0, realDestination);
    CCFiniteTimeAction *scale = CCScaleBy::create(5.0, 5);
    CCFiniteTimeAction *rotate = CCRotateBy::create(5.0, 10000);
    //CCFiniteTimeAction *moveBack = CCMoveTo::create(2.0, ccp(0, SCREEN_HEIGHT - 10));
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuGameNPCs::enemyMoveFinished));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    enemy->runAction(actionSequence);
    enemy->runAction(scale);
    enemy->runAction(rotate);
    
    if (!enemies) {
        this->enemies = CCArray::create();
    }
    
    //this->enemies->addObject(enemy);
}

void HuGameNPCs::didSwipe(CCObject *sender)
{
    CCSwipe *swipe = (CCSwipe*)sender;
    CCLog("start position = (%f, %f)", swipe->location.x, swipe->location.y);
    CCLog("end position = (%f, %f)", swipe->finalLocation.x, swipe->finalLocation.y);
    
    CCSprite *dot1 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot1->setPosition(swipe->location);
    this->addChild(dot1);
    CCSprite *dot2 = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("dot2.png", CCRectMake(0, 0, 20, 20)));
    dot2->setPosition(swipe->finalLocation);
    this->addChild(dot2);
}

void HuGameNPCs::enemyMoveFinished(CCNode *sender)
{
    CCSprite *enemy = (CCSprite*)sender;
    //CCLog("enemy %s move finished", enemy->description());
    this->removeChild(enemy);
    //enemies->removeObject(enemy);
}

CCPoint HuGameNPCs::generateEnemyInitialPoint()
{
    float x = 0;
    float y = 0;
    
    // decide if starting on left side or right side
    int leftRight = random() % 2;
    x = SCREEN_WIDTH * leftRight;
    
    y = random() % (int)GROUND_END_Y;
    
    return ccp(x, y);
}
//
//  HuGoodNPC.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 11/18/13.
//
//

#include "HuGoodNPC.h"
#include "HuPlayer.h"
#include "Constants.h"
#include "HuProjectile.h"

using namespace cocos2d;

bool HuGoodNPC::initialize() {
    
    if (!CCNode::init()) {
        return false;
    }
    
    sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("Target.png", CCRectMake(0, 0, 20, 20)));
    sprite->setPosition(this->generateInitialPoint());
    layer->addChild(sprite);
    
    player = HuPlayer::getInstance();
    
    

    
    //sprite->runAction(actionSequence);
    //sprite->runAction(scale);
    //sprite->runAction(rotate);
    
    this->scheduleAttackInSeconds(1);
    
    return true;
}

void HuGoodNPC::initWithLayerAndNumber(cocos2d::CCLayer *layer, int number) {
    this->layer = layer;
    this->playerNumber = number;
    this->initialize();
    
}

CCPoint HuGoodNPC::generateInitialPoint() {
    int minX = SCREEN_WIDTH / 2 - 100;
    int minY = SCREEN_HEIGHT / 2 - 200;
    int maxX = SCREEN_WIDTH / 2 + 100;
    int maxY = SCREEN_HEIGHT - 100;
    int xRandom = arc4random() % (maxX - minX) + minX;
    int yRandom = arc4random() % (maxY - minY) + minY;
    
    return ccp(xRandom, yRandom);
}

void HuGoodNPC::attack(CCNode *sender) {
    this->scheduleAttackInSeconds(1);
    CCLog("good npc ATTACK");
    
    HuProjectile *projectile = HuProjectile::initWithMandatories(MISSILE, sprite->getPosition(), )
    
    
}

void HuGoodNPC::scheduleAttackInSeconds(int seconds) {
    // TODO: this is pretty bad. Instead of just scheduleing a selector I'm moving a sprite to its current point for the amount of time
    
    CCFiniteTimeAction *attackFake = CCMoveTo::create(seconds, sprite->getPosition());
    CCFiniteTimeAction *attack = CCCallFuncN::create(this, callfuncN_selector(HuGoodNPC::attack));
    
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(attackFake);
    actionArray->addObject(attack);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    sprite->runAction(actionSequence);
}
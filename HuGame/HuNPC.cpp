//
//  HuNPC.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 9/9/13.
//
//

#include "HuNPC.h"
#include "HuPlayer.h"

using namespace cocos2d;


bool HuNPC::initialize() {
    
    if (!CCNode::init()) {
        return false;
    }
    
    health = 100;
    givesCurrency = 1;
    dealsDamage = 1;
    

    sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("Player.png", CCRectMake(0, 0, 27, 40)));
    sprite->setPosition(this->generateEnemyInitialPoint());
    layer->addChild(sprite);
    
    HuPlayer *player = HuPlayer::getInstance();
    
    
    int leftRight = (sprite->getPositionX() < (SCREEN_WIDTH / 2)) ? 1 : -1;
    float realFinalX = (SCREEN_WIDTH / 2) - leftRight * (player->baseWidth / 2);
    float realFinalY = sprite->getPositionY();
    CCPoint realDestination = ccp(realFinalX, realFinalY);
    
    CCFiniteTimeAction *move = CCMoveTo::create(5.0, realDestination);
    //CCFiniteTimeAction *scale = CCScaleBy::create(5.0, 5);
    //CCFiniteTimeAction *rotate = CCRotateBy::create(5.0, 10000);
    //CCFiniteTimeAction *moveBack = CCMoveTo::create(2.0, ccp(0, SCREEN_HEIGHT - 10));
    CCFiniteTimeAction *finished = CCCallFuncN::create(this, callfuncN_selector(HuNPC::enemyMoveFinished));
    
    CCArray *actionArray = CCArray::create();
    actionArray->addObject(move);
    actionArray->addObject(finished);
    
    
    CCSequence *actionSequence = CCSequence::create(actionArray);
    
    sprite->runAction(actionSequence);
    //sprite->runAction(scale);
    //sprite->runAction(rotate);
    
    return true;
}

void HuNPC::initWithLayer(cocos2d::CCLayer *layer) {
    this->layer = layer;
    this->initialize();

}

void HuNPC::enemyMoveFinished(CCNode *sender)
{
    // begin basic attack
    if (sprite->isVisible()) {
        HuPlayer::getInstance()->health -= dealsDamage;
    }
    //CCLog("attacked player for %d damage", dealsDamage);
   // layer->removeChild(this->sprite);
}

bool HuNPC::takeDamageFromPlayer(ElementalDamageTypes damageType) {
    if (!sprite->isVisible()) {
        return false;
    }
    
    this->health -= HuPlayer::getInstance()->damageModifier;
    if (this->health <= 0) {
        sprite->setVisible(false);
        //layer->removeChild(sprite);
        HuPlayer::getInstance()->currency += givesCurrency;
        
        
        // kill it and clean up npc
        killNPC();
        
        return true;
        
        
    }
    this->currentElementalDamage.insert(damageType);
    
    return false;
    

}

bool HuNPC::takeDamageFromNPC(int damage) {
    // don't do anything if the npc is already dead / invisible
    if (!sprite->isVisible()) {
        return false;
    }
    this->health -= damage;
    if (health <= 0) {
        sprite->setVisible(false);
        //layer->removeChild(sprite);
        HuPlayer::getInstance()->currency += givesCurrency;
        
        killNPC();
        
        return true;
    }
    
    return false;
}

void HuNPC::killNPC() {
    // supposed to be empty, meant to be overridden
    
}

CCPoint HuNPC::generateEnemyInitialPoint()
{
    float x = 0;
    float y = 0;
    
    // decide if starting on left side or right side
    int leftRight = random() % 2;
    x = SCREEN_WIDTH * leftRight;
    
    y = random() % (int)GROUND_END_Y;
    y = MAX(y, 30);
    
    return ccp(x, y);
}

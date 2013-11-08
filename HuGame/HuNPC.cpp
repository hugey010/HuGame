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



void HuNPC::initialize() {
    health = 100;
    givesCurrency = 1;
    dealsDamage = 1;
    
    
    sprite = CCSprite::createWithSpriteFrame(CCSpriteFrame::create("Player.png", CCRectMake(0, 0, 20, 20)));
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
}

void HuNPC::initWithLayer(cocos2d::CCLayer *layer) {
    this->layer = layer;
    this->initialize();

}

void HuNPC::enemyMoveFinished(CCNode *sender)
{
    // begin basic attack
    HuPlayer::getInstance()->health -= dealsDamage;
    //CCLog("attacked player for %d damage", dealsDamage);
   // layer->removeChild(this->sprite);
}

bool HuNPC::takeDamageFromPlayer(ElementalDamageTypes damageType) {
    this->health -= HuPlayer::getInstance()->damageModifier;
    if (this->health <= 0) {
        layer->removeChild(sprite);
        HuPlayer::getInstance()->currency += givesCurrency;
        
        
        // kill it and clean up npc
        killNPC();
        
        return true;
        
        
    }
    this->currentElementalDamage.insert(damageType);
    
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
    
    return ccp(x, y);
}

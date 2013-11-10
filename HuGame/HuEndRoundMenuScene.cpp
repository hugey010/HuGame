//
//  HuEndRoundMenuScene.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 11/5/13.
//
//

#include "HuEndRoundMenuScene.h"
#include "Constants.h"
#include "HuGameScene.h"
#include "HuPlayer.h"

using namespace cocos2d;

CCMenu *pMenu;
CCLabelTTF *soldierLabel;
CCLabelTTF *cannonLabel;
CCLabelTTF *healthLabel;
CCLabelTTF *currencyLabel;
CCLabelTTF *roundLabel;

HuPlayer *player;

CCScene* HuEndRoundMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HuEndRoundMenuScene *layer = HuEndRoundMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HuEndRoundMenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    player = HuPlayer::getInstance();

    
    CCLabelTTF *plusLabel = CCLabelTTF::create("+", MENU_FONT, MENU_FONT_SIZE);
    CCLabelTTF *minusLabel = CCLabelTTF::create("-", MENU_FONT, MENU_FONT_SIZE);
    
        // health label
    HuPlayer *player = HuPlayer::getInstance();
    CCString *health = CCString::createWithFormat("Health: %d", player->health);
    healthLabel = CCLabelTTF::create(health->getCString(), MENU_FONT, MENU_FONT_SIZE);
    healthLabel->setPosition(ccp(80, SCREEN_HEIGHT - 50));
    this->addChild(healthLabel);
    
    CCString *level = CCString::createWithFormat("Level: %d", player->level);
    roundLabel = CCLabelTTF::create(level->getCString(), MENU_FONT, MENU_FONT_SIZE);
    roundLabel->setPosition(ccp(SCREEN_WIDTH - 80, SCREEN_HEIGHT - 50));
    this->addChild(roundLabel);
    
    CCString *currency = CCString::createWithFormat("Coins: %d", player->currency);
    currencyLabel = CCLabelTTF::create(currency->getCString(), MENU_FONT, MENU_FONT_SIZE);
    currencyLabel->setPosition(ccp(SCREEN_WIDTH - 80, 50));
    this->addChild(currencyLabel);
    
    // SOLDIER ITEM
    CCString *soldiers = CCString::createWithFormat("Soldiers: %d", player->numberOfSoldiers);
    soldierLabel = CCLabelTTF::create(soldiers->getCString(), MENU_FONT, MENU_FONT_SIZE);
    soldierLabel->setPosition(ccp(180, 320));
    this->addChild(soldierLabel);
    
    CCMenuItemLabel *soldierPlusItem = CCMenuItemLabel::create(plusLabel, this, menu_selector(HuEndRoundMenuScene::addSoldierPressed));
    soldierPlusItem->setPosition(ccp(soldierLabel->getPositionX() - 30, soldierLabel->getPositionY()));
    this->addChild(soldierPlusItem);

    CCMenuItemLabel *soldierMinusItem = CCMenuItemLabel::create(minusLabel, this, menu_selector(HuEndRoundMenuScene::minusSoldierPressed));
    soldierMinusItem->setPosition(ccp(soldierLabel->getPositionX() + 30, soldierLabel->getPositionY()));
    this->addChild(soldierMinusItem);
   
    // CANNON ITEM
    CCString *cannons = CCString::createWithFormat("Cannons: %d", player->numberOfCannons);
    cannonLabel = CCLabelTTF::create(cannons->getCString(), MENU_FONT, MENU_FONT_SIZE);
    cannonLabel->setPosition(ccp(180, 280));
    this->addChild(cannonLabel);
   
    CCMenuItemLabel *cannonPlusItem = CCMenuItemLabel::create(plusLabel, this, menu_selector(HuEndRoundMenuScene::addCannonPressed));
    cannonPlusItem->setPosition(ccp(cannonLabel->getPositionX() - 30, soldierLabel->getPositionY()));
    this->addChild(soldierPlusItem);
    
    CCMenuItemLabel *cannonMinusItem = CCMenuItemLabel::create(minusLabel, this, menu_selector(HuEndRoundMenuScene::minusCannonPressed));
    soldierMinusItem->setPosition(ccp(cannonLabel->getPositionX() + 30, soldierLabel->getPositionY()));
    this->addChild(cannonMinusItem);
    
    // NEXT ROUND ITEM
    CCLabelTTF *nextRoundLabel = CCLabelTTF::create("Next Round", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *nextRoundItem = CCMenuItemLabel::create(nextRoundLabel, this, menu_selector(HuEndRoundMenuScene::nextRoundPressed));
    nextRoundItem->setPosition(ccp(SCREEN_WIDTH / 2, 50));
    
    // SELL ALL ITEM
    CCLabelTTF *sellAllLabel = CCLabelTTF::create("Sell All", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *sellAllItem = CCMenuItemLabel::create(sellAllLabel, this, menu_selector(HuEndRoundMenuScene::sellAllPressed));
    sellAllItem->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));
    
    // CREATE THAT MENU
    pMenu = CCMenu::create(nextRoundItem, sellAllItem,  NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}
                                                 
void HuEndRoundMenuScene::refreshLabels()
{
    
    CCString *soldiers = CCString::createWithFormat("Soldiers: %d", player->numberOfSoldiers);
    soldierLabel->setString(soldiers->getCString());
    
    CCString *currency = CCString::createWithFormat("Coins: %d", player->currency);
    currencyLabel->setString(currency->getCString());
    
    CCString *level = CCString::createWithFormat("Level: %d", player->level);
    roundLabel->setString(level->getCString());
    
    
}

// menu callbacks
void HuEndRoundMenuScene::nextRoundPressed(cocos2d::CCObject *psender)
{
    CC_SHARED_DIRECTOR->replaceScene(HuGameScene::scene());

    
}

void HuEndRoundMenuScene::sellAllPressed(cocos2d::CCObject *psender)
{
    int currencyToAdd = 0;
    currencyToAdd += player->numberOfCannons * COST_CANNON;
    currencyToAdd += player->numberOfSoldiers * COST_SOLDIER;
    
    player->numberOfSoldiers = 0;
    player->numberOfCannons = 0;
    
    refreshLabels();
}

    // upgrades for defense
void HuEndRoundMenuScene::addSoldierPressed(CCObject* sender)
{
    if (player->currency >= COST_SOLDIER)
    {
        player->currency -= COST_SOLDIER;
        player->numberOfSoldiers++;
    }
    
    refreshLabels();
}

void HuEndRoundMenuScene::minusSoldierPressed(CCObject* sender)
{
    if (player->numberOfSoldiers > 0)
    {
        player->numberOfSoldiers--;
        player->currency += COST_SOLDIER;
        
    }
    
    refreshLabels();
}

void HuEndRoundMenuScene::addCannonPressed(CCObject* sender)
{
    if (player->currency >= COST_CANNON)
    {
        player->currency -= COST_CANNON;
        player->numberOfCannons++;
    }
    
    refreshLabels();
}

void HuEndRoundMenuScene::minusCannonPressed(cocos2d::CCObject *sender)
{
    if (player->numberOfCannons > 0)
    {
        player->numberOfCannons--;
        player->currency += COST_CANNON;
    }
    
    refreshLabels();
}

// upgrades for player
void HuEndRoundMenuScene::addHealthPressed(CCObject* sender) {
    if (player->currency >= COST_HEALTH)
    {
        int health = player->health;
        health += (int)(float)health * 0.1f;
        player->health = health;
    }
    
    refreshLabels();
}

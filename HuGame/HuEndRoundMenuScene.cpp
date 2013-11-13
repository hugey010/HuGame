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
CCMenuItemLabel *defenseUpgradeItemLabel;

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
    
    CCLabelTTF *offenseLabel = CCLabelTTF::create("Offensive Upgrades", MENU_FONT, MENU_FONT_HEADER_SIZE);
    offenseLabel->setPosition(ccp(280, 500));
    this->addChild(offenseLabel);
    
    CCLabelTTF *defenseLabel = CCLabelTTF::create("Defensive Upgrades", MENU_FONT, MENU_FONT_HEADER_SIZE);
    defenseLabel->setPosition(ccp(880, 500));
    this->addChild(defenseLabel);
    
    // SOLDIER ITEM
    CCString *soldiers = CCString::createWithFormat("Soldiers: %d", player->numberOfSoldiers);
    soldierLabel = CCLabelTTF::create(soldiers->getCString(), MENU_FONT, MENU_FONT_SIZE);
    soldierLabel->setPosition(ccp(280, 340));
    this->addChild(soldierLabel);
    
    CCLabelTTF *plusLabel = CCLabelTTF::create("+", MENU_FONT, MENU_FONT_SIZE + 50);
    CCLabelTTF *minusLabel = CCLabelTTF::create("-", MENU_FONT, MENU_FONT_SIZE + 50);
    
    CCMenuItemLabel *soldierPlusItem = CCMenuItemLabel::create(plusLabel, this, menu_selector(HuEndRoundMenuScene::addSoldierPressed));
    soldierPlusItem->setPosition(ccp(soldierLabel->getPositionX() + 100, soldierLabel->getPositionY() + 10));

    CCMenuItemLabel *soldierMinusItem = CCMenuItemLabel::create(minusLabel, this, menu_selector(HuEndRoundMenuScene::minusSoldierPressed));
    soldierMinusItem->setPosition(ccp(soldierLabel->getPositionX() - 100, soldierLabel->getPositionY() + 10));
   
    // CANNON ITEM
    CCString *cannons = CCString::createWithFormat("Cannons: %d", player->numberOfCannons);
    cannonLabel = CCLabelTTF::create(cannons->getCString(), MENU_FONT, MENU_FONT_SIZE);
    cannonLabel->setPosition(ccp(280, 260));
    this->addChild(cannonLabel);
    
    CCLabelTTF *plusLabel2 = CCLabelTTF::create("+", MENU_FONT, MENU_FONT_SIZE + 50);
    CCLabelTTF *minusLabel2 = CCLabelTTF::create("-", MENU_FONT, MENU_FONT_SIZE + 50);
    
    CCMenuItemLabel *cannonPlusItem = CCMenuItemLabel::create(plusLabel2, this, menu_selector(HuEndRoundMenuScene::addCannonPressed));
    cannonPlusItem->setPosition(ccp(cannonLabel->getPositionX() + 100, cannonLabel->getPositionY() + 10));
    
    CCMenuItemLabel *cannonMinusItem = CCMenuItemLabel::create(minusLabel2, this, menu_selector(HuEndRoundMenuScene::minusCannonPressed));
    cannonMinusItem->setPosition(ccp(cannonLabel->getPositionX() - 100, cannonLabel->getPositionY() + 10));
    
    // NEXT ROUND ITEM
    CCLabelTTF *nextRoundLabel = CCLabelTTF::create("Next Round", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *nextRoundItem = CCMenuItemLabel::create(nextRoundLabel, this, menu_selector(HuEndRoundMenuScene::nextRoundPressed));
    nextRoundItem->setPosition(ccp(SCREEN_WIDTH / 2, 50));
    
    // SELL ALL ITEM
    CCLabelTTF *sellAllLabel = CCLabelTTF::create("Sell All", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *sellAllItem = CCMenuItemLabel::create(sellAllLabel, this, menu_selector(HuEndRoundMenuScene::sellAllPressed));
    sellAllItem->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));
    
    // DEFENSE UPGRADE ITEM
    CCString *fortressLevelString = CCString::createWithFormat("Fortress Level %d", (int)player->defenseUpgradeLevel + 1);
    CCLabelTTF *defenseUpgradeLabel = CCLabelTTF::create(fortressLevelString->getCString(), MENU_FONT, MENU_FONT_SIZE);
    defenseUpgradeItemLabel = CCMenuItemLabel::create(defenseUpgradeLabel, this, menu_selector(HuEndRoundMenuScene::upgradeDefensePressed));
    defenseUpgradeItemLabel->setPosition(ccp(defenseLabel->getPositionX(), soldierLabel->getPositionY()));
    
    // CREATE THAT MENU
    pMenu = CCMenu::create(nextRoundItem, sellAllItem, soldierMinusItem, soldierPlusItem, cannonMinusItem, cannonPlusItem, defenseUpgradeItemLabel,  NULL);
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
    
    CCString *cannons = CCString::createWithFormat("Cannons: %d", player->numberOfCannons);
    cannonLabel->setString(cannons->getCString());
    
    CCString *fortressLevelString = CCString::createWithFormat("Fortress Level %d", (int)player->defenseUpgradeLevel + 1);
    defenseUpgradeItemLabel->setString(fortressLevelString->getCString());
}

// menu callbacks
void HuEndRoundMenuScene::nextRoundPressed(cocos2d::CCObject *psender)
{
    HuPlayer::getInstance()->save();
    
    CC_SHARED_DIRECTOR->replaceScene(HuGameScene::scene());
}

void HuEndRoundMenuScene::sellAllPressed(cocos2d::CCObject *psender)
{
    int currencyToAdd = 0;
    currencyToAdd += player->numberOfCannons * COST_CANNON;
    currencyToAdd += player->numberOfSoldiers * COST_SOLDIER;
    player->currency += currencyToAdd;
    
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

void HuEndRoundMenuScene::upgradeDefensePressed(CCObject *sender) {
    // different costs for different purchases of defese
    switch (player->defenseUpgradeLevel) {
        case DEFENSE_UPGRADE_0 : {
            if (player->currency >= COST_FORTRESS_1) {
                player->currency -= COST_FORTRESS_1;
                player->defenseUpgradeLevel = DEFENSE_UPGRADE_1;
            }
            
            break;
        }
            
        case DEFENSE_UPGRADE_1 : {
            if (player->currency >= COST_FORTRESS_2) {
                player->currency -= COST_FORTRESS_2;
                player->defenseUpgradeLevel = DEFENSE_UPGRADE_2;
            }
            
            break;
        }
            
        case DEFENSE_UPGRADE_2 : {
            if (player->currency >= COST_FORTRESS_3) {
                player->currency -= COST_FORTRESS_3;
                player->defenseUpgradeLevel = DEFENSE_UPGRADE_2;
            }
            
            break;
        }
            
        case DEFENSE_UPGRADE_3 : {
            // do nothing, this is max level of defense
            break;
        }
    }
    
    refreshLabels();
}


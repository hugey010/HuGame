//
//  HuLoserScene.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 11/10/13.
//
//

#include "HuLoserScene.h"
#include "Constants.h"
#include "HuEndRoundMenuScene.h"
#include "HelloWorldScene.h"
#include "HuPlayer.h"
#include "HuGameScene.h"

using namespace cocos2d;

CCScene* HuLoserScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HuLoserScene *layer = HuLoserScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HuLoserScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLabelTTF *loseLabel = CCLabelTTF::create("You Lost", MENU_FONT, MENU_FONT_HEADER_SIZE + 20);
    loseLabel->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80));
    this->addChild(loseLabel);
    
    CCLabelTTF *tryAgainLabel = CCLabelTTF::create("Try Again", MENU_FONT, MENU_FONT_HEADER_SIZE);
    CCMenuItemLabel *tryAgainItem = CCMenuItemLabel::create(tryAgainLabel, this, menu_selector(HuLoserScene::tryAgainCallback));
    tryAgainItem->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 400));

    
    CCLabelTTF *mainMenuLabel = CCLabelTTF::create("Quit", MENU_FONT, MENU_FONT_HEADER_SIZE);
    CCMenuItemLabel *mainMenuItem = CCMenuItemLabel::create(mainMenuLabel, this, menu_selector(HuLoserScene::mainMenuCallback));
    mainMenuItem->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 500));
    
    CCMenu *menu = CCMenu::create(tryAgainItem, mainMenuItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    return true;
}

void HuLoserScene::tryAgainCallback(cocos2d::CCObject *pSender) {
    
    // if dudes on first level, dont allow purchases
    if (HuPlayer::getInstance()->level <= 1) {
        CC_SHARED_DIRECTOR->replaceScene(HuGameScene::scene());

    } else {
        CC_SHARED_DIRECTOR->replaceScene(HuEndRoundMenuScene::scene());
    }
    
}

void HuLoserScene::mainMenuCallback(cocos2d::CCObject *pSender) {
    CC_SHARED_DIRECTOR->replaceScene(HelloWorld::scene());

}


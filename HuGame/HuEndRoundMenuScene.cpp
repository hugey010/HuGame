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

using namespace cocos2d;

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
    
    
    CCLabelTTF *nextRoundLabel = CCLabelTTF::create("Next Round", MENU_FONT, MENU_FONT_SIZE);
    //CCMenuItemLabel *nextRoundItem = CCMenuItemLabel::create(nextRoundLabel, this, menu_selector(HuEndRoundMenuScene::nextRoundPressed));
    //nextRoundItem->setPosition(ccp(SCREEN_WIDTH - 80, 50));
    nextRoundLabel->setPosition(ccp(SCREEN_WIDTH - 80, 50));
    /*
    CCLabelTTF *mContinueGameLabel = CCLabelTTF::create("Continue Game", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *mContinueGameItem = CCMenuItemLabel::create(mContinueGameLabel, this, menu_selector(HelloWorld::continueGameCallback));
    mNewGameItem->setPosition(ccp(0, -2 * MENU_FONT_SIZE));
    
    CCLabelTTF *mEndGameLabel = CCLabelTTF::create("End Game", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *mEndGameItem = CCMenuItemLabel::create(mEndGameLabel, this, menu_selector(HelloWorld::endGameCallback));
    mEndGameItem->setPosition(ccp(0, -4 * MENU_FONT_SIZE));
    */
    
    // create menu, it's an autorelease object
    //CCMenu* pMenu = CCMenu::create(nextRoundItem, NULL);
    
    //pMenu->setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100));
    //this->addChild(pMenu, 1);
    
    this->addChild(nextRoundLabel);
    
    return true;
}

// menu callbacks
void HuEndRoundMenuScene::nextRoundPressed(cocos2d::CCObject *psender)
{
    CC_SHARED_DIRECTOR->replaceScene(HuGameScene::scene());

    
}

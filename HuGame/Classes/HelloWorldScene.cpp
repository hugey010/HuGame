#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"
#include "HuGameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // Create Opening Menu 
    CCSize size = CC_SHARED_DIRECTOR->getWinSize();
    
    CCLabelTTF *mNewGameLabel = CCLabelTTF::create("New Game", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *mNewGameItem = CCMenuItemLabel::create(mNewGameLabel, this, menu_selector(HelloWorld::newGameCallback));
    mNewGameItem->setPosition(CCPointZero);
    
    
    CCLabelTTF *mContinueGameLabel = CCLabelTTF::create("Continue Game", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *mContinueGameItem = CCMenuItemLabel::create(mContinueGameLabel, this, menu_selector(HelloWorld::continueGameCallback));
    mNewGameItem->setPosition(ccp(0, -2 * MENU_FONT_SIZE));

    CCLabelTTF *mEndGameLabel = CCLabelTTF::create("End Game", MENU_FONT, MENU_FONT_SIZE);
    CCMenuItemLabel *mEndGameItem = CCMenuItemLabel::create(mEndGameLabel, this, menu_selector(HelloWorld::endGameCallback));
    mEndGameItem->setPosition(ccp(0, -4 * MENU_FONT_SIZE));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(mNewGameItem, mContinueGameItem, mEndGameItem, NULL);
    pMenu->setPosition(ccp(size.width / 2, size.height / 2 + 100));
    this->addChild(pMenu, 1);
    
    return true;
}

void HelloWorld::newGameCallback(CCObject* pSender)
{
    CCLog("Make that new game");
    CC_SHARED_DIRECTOR->replaceScene(HuGameScene::scene());
}

void HelloWorld::continueGameCallback(CCObject* pSender)
{
    CCLog("Continue a game");
    CC_SHARED_DIRECTOR->replaceScene(HuGameScene::scene());
}

void HelloWorld::endGameCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

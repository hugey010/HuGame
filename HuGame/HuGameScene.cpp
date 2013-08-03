//
//  HuGameScene.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#include "HuGameScene.h"
#include "Constants.h"
#include "HuGameHud.h"

using namespace cocos2d;

CCScene* HuGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HuGameScene *layer = HuGameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HuGameScene::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // schedule end of round
    this->schedule(schedule_selector(HuGameScene::endRoundCallback), ROUND_INTERVAL, false, 0);
    
    

    
    // lay out all of the HUD elements
    
    //HuGameHUD *hud =
    
    HuGameHud *hud = HuGameHud::create();
    this->addChild((CCLayer*)hud,5);
    
    // create hud class which updates itself based on the model (possible on a timer or maybe a listener")
    /*
     HUD has: 
     health
     timeleft
     ammo
     special ability timers
     round number
     currency
     */
    
    // layout user base and all the shit thats involved with that
    /*  This includes:
     Turrets, Special abilities, defenses, npcs, 
     
     This should probably update the game scene on its lonesome. I would think 
     
     */
    
    // Create enemy ncp generator. based on round number, ?difficulty? (possibly other ways to make the enemy easier / more difficult).
    
    // I would think touches should be handled by each thing respectively. touches on HUD,
    
    // what on the hugamescene actually requires touching from here and isnt a component
    
    
    
    return true;
}



void HuGameScene::endRoundCallback(CCObject *pSender)
{
    CCLog("end of round");
}

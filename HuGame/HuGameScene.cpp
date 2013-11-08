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
#include "HuGameFortress.h"
#include "HuGameBackground.h"
#include "HuGameNPCs.h"
#include "HuGameAttacks.h"
#include "HuEndRoundMenuScene.h"

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
    /*
        TODO: the second argument for addChild is the z order. higher numbers get drawn later
        this might need to be changed because I don't know what is most important, nor how many
        layers i'll have
     */
    
    // the hud should handle the swapping of current weapons
    // the hud will also handle pausing the game
    // it will probably be responsible for menus and other things like that
    
    
    
    HuGameHud *hud = HuGameHud::create();
    this->addChild((CCLayer*)hud,4);
    
    // create a fortress layer which handles drawing all the modifications / upgrades the user has
    
    HuGameFortress *fortress = HuGameFortress::create();
    this->addChild((CCLayer*)fortress, 5);
    
    HuGameBackground *background = HuGameBackground::create();
    this->addChild((CCLayer*)background, 1);

    
    
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
    
    // HuGameNPCs will handle deploying of the enemies
    // touch and gesture handling for killing enemies
    //
    HuGameNPCs *npcs = HuGameNPCs::create();
    this->addChild((CCLayer*)npcs, 6);
    
    HuGameAttacks *attacks = HuGameAttacks::create();
    attacks->npcs = npcs;
    this->addChild((CCLayer*)attacks, 7);
    
    
    return true;
}



void HuGameScene::endRoundCallback(CCObject *pSender)
{
    CCLog("end of round");
    CC_SHARED_DIRECTOR->replaceScene(HuEndRoundMenuScene::scene());
    
}

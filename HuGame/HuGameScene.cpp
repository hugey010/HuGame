//
//  HuGameScene.cpp
//  HuGame
//
//  Created by Tyler Hugenberg on 8/3/13.
//
//

#include "HuGameScene.h"

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
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    return true;
}
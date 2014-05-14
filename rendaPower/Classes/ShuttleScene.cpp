//
//  ShuttleScene.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#include "ShuttleScene.h"

using namespace cocos2d;

CCScene* ShuttleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ShuttleScene *layer = ShuttleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShuttleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("base/planet.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height*0.75f) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

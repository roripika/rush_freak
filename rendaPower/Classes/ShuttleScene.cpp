//
//  ShuttleScene.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#include "ShuttleScene.h"

using namespace cocos2d;

/**
 * コンストラクタ
 */
ShuttleScene::ShuttleScene()
:m_Lady(NULL)
,m_menu(NULL)
,m_Score(NULL)
,m_PlanetSprite(NULL)
,m_RocketSprite(NULL)
{
    
}
/**
 * デストラクタ
 */
ShuttleScene::~ShuttleScene()
{
    
}

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
    
    this->m_PlanetSprite = CCSprite::create("base/planet.png");
    this->m_RocketSprite = CCSprite::create("base/rocket.png");
    
    this->m_menu = CCMenu::create();
    CCSprite* normalSprite = CCSprite::create("base/tap_button.png");
    CCSprite* selectSprite = CCSprite::create("base/tap_button.png");
    selectSprite->setColor(ccc3(0x7F, 0x7F, 0x7F));
    CCMenuItemSprite * menuPush = CCMenuItemSprite::create(normalSprite, selectSprite);
    menuPush->setTag(10000);
    this->m_menu->addChild(menuPush);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    // add "HelloWorld" splash screen"
    
    // position the sprite on the center of the screen
    this->m_PlanetSprite->setPosition( ccp(this->m_PlanetSprite->getContentSize().width
                                           , size.height*0.75f) );
    
    // add the sprite as a child to this layer
    this->addChild(this->m_PlanetSprite, 0);
    this->addChild(this->m_RocketSprite, 10);
    this->addChild(this->m_menu, 0);
    
    
    //ボタンの位置
    menuPush->setPosition(ccp(size.width -
                              menuPush->getContentSize().width * 0.5f,
                              menuPush->getContentSize().height * 0.5f));
    this->m_menu->setPosition(0, 0);
    
    return true;
}

/**
 * 設定をシーンによって変える
 */
void ShuttleScene::settingShotSceneObject(SHOT_SECNE val)
{
    switch (val) {
        case SSHOT_INIT:            
            break;
            
        default:
            break;
    }
}
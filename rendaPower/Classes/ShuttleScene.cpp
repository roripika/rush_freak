//
//  ShuttleScene.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#include "ShuttleScene.h"

#define DEF_PRINTSTR_HISCORE    ("HiScore: %8d")
#define DEF_PRINTSTR_SCORE      ("Score  : %8d")
#define DEF_PRINTSTR_SPEED      ("Speed: %4d")
#define DEF_PRINTSTR_POWER      ("Power: %4d")

using namespace cocos2d;

/**
 * コンストラクタ
 */
ShuttleScene::ShuttleScene()
:m_ReadyLabel(NULL)
,m_ScoreLabel(NULL)
,m_PowerLabel(NULL)
,m_HiScoreLabel(NULL)
,m_SpeedLabel(NULL)
,m_menu(NULL)
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
    
    //UIの初期位置設定
    char buff[100] = "";
    //ハイスコア
    sprintf(buff,DEF_PRINTSTR_HISCORE,0);
    this->m_HiScoreLabel = CCLabelTTF::create(buff, "Helvetica", 48);
    this->m_HiScoreLabel->setAnchorPoint(ccp(0.0,1.0f));
    this->m_HiScoreLabel->setPosition(ccp(0,size.height));
    //スコア
    sprintf(buff,DEF_PRINTSTR_SCORE,0);
    this->m_ScoreLabel = CCLabelTTF::create(buff, "Helvetica", 48);
    this->m_ScoreLabel->setAnchorPoint(ccp(0.0,1.0f));
    this->m_ScoreLabel->setPosition(
                                    ccp(0,
                                        size.height -
                                        this->m_HiScoreLabel->getContentSize().height));

    //レディーラベル
    this->m_ReadyLabel = CCLabelTTF::create("", "Helvetica", 48);
    this->m_ReadyLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));

    //スピードラベル
    sprintf(buff,DEF_PRINTSTR_SPEED,0);
    this->m_SpeedLabel = CCLabelTTF::create(buff, "Helvetica", 48);
    this->m_SpeedLabel->setAnchorPoint(ccp(0,0));
    this->m_SpeedLabel->setPosition(ccp(0,0));
    
    //パワーラベル
    sprintf(buff,DEF_PRINTSTR_POWER,0);
    this->m_PowerLabel = CCLabelTTF::create(buff, "Helvetica", 48);
    this->m_PowerLabel->setAnchorPoint(ccp(0,0));
    this->m_PowerLabel->setPosition(ccp(0,
                                        this->m_SpeedLabel->getContentSize().height));
    
    this->addChild(this->m_HiScoreLabel,1000);
    this->addChild(this->m_ScoreLabel,1000);
    this->addChild(this->m_ReadyLabel,1000);
    this->addChild(this->m_SpeedLabel,1000);
    this->addChild(this->m_PowerLabel,1000);
    
    
    //ボタンの位置
    menuPush->setPosition(ccp(size.width -
                              menuPush->getContentSize().width * 0.5f,
                              menuPush->getContentSize().height * 0.5f));
    this->m_menu->setPosition(0, 0);
    this->m_ReadyLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
    
    
    return true;
}

/**
 * 設定をシーンによって変える
 */
void ShuttleScene::settingShotSceneObject(SHOT_SECNE val)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    switch (val) {
        case SSHOT_INIT: //初期準備
            this->m_PlanetSprite->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
            this->m_ReadyLabel->setVisible(false);
            break;
        case SSHOT_READY:
            this->m_ReadyLabel->setVisible(true);
            this->m_ReadyLabel->setString("Are you ready?");
        case SSHOT_START_COUNT:
        case SSHOT_PUSH_PLAY:
        case SSHOT_SHUTTLE_ANIME:
        case SSHOT_SCORE:
        case SSHOT_RETRY:
            
        default:
            break;
    }
}
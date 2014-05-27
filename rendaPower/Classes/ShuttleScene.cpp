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
#define DEF_PRINTSTR_SPEED      ("Speed: %4ld")
#define DEF_PRINTSTR_POWER      ("Power: %4ld")


#define DEF_BG_HEIGHT   (4000)

#define DEF_TAG_RUSH_BTN (10000)

#define DEF_Z_UI (1000)

#define DEF_RUSH_TIME (10000)
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
,m_CloudSprite1(NULL)
,m_CloudSprite2(NULL)
,m_BackGroundLayer(NULL)
,m_shotSceneState(SSHOT_NONE)
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
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //背景
    m_BackGroundLayer = CCLayerGradient::create(ccc4(0x0, 0x0, 0x0, 0xFF), ccc4(0x7f, 0x7f, 0x7f, 0x7f));
    this->m_BackGroundLayer->setContentSize(CCSizeMake(size.width, DEF_BG_HEIGHT));
    this->addChild(this->m_BackGroundLayer,0);
    
    this->m_PlanetSprite = CCSprite::create("base/planet.png");
    this->m_RocketSprite = ShuttleModel::create();
    this->m_CloudSprite1 = CCSprite::create("base/kumo.png");
    this->m_CloudSprite2 = CCSprite::create("base/kumo.png");
    
    this->m_BackGroundLayer->addChild(this->m_PlanetSprite, 0);
    this->m_BackGroundLayer->addChild(this->m_CloudSprite1, 5);
    this->m_BackGroundLayer->addChild(this->m_CloudSprite2, 6);
    this->m_BackGroundLayer->addChild(this->m_RocketSprite, 10);
    
    
    // position the sprite on the center of the screen
    this->m_PlanetSprite->setPosition(
                                      ccp(
                                          size.width * 0.5f,
                                        DEF_BG_HEIGHT- size.height * 0.5f) );

    this->m_menu = CCMenu::create();
    
    //RUSHボタンの生成
    CCSprite* normalSprite = CCSprite::create("base/tap_button.png");
    CCSprite* selectSprite = CCSprite::create("base/tap_button.png");
    selectSprite->setColor(ccc3(0x7F, 0x7F, 0x7F));
    CCMenuItemSprite * menuPush = CCMenuItemSprite::create(normalSprite, selectSprite);
    menuPush->setTarget(this, menu_selector(ShuttleScene::tapRushButton));
    menuPush->setTag(DEF_TAG_RUSH_BTN);
    this->m_menu->addChild(menuPush);
    // add the sprite as a child to this layer
    this->addChild(this->m_menu, 5000);
    
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
    sprintf(buff,DEF_PRINTSTR_SPEED,0L);
    this->m_SpeedLabel = CCLabelTTF::create(buff, "Helvetica", 48);
    this->m_SpeedLabel->setAnchorPoint(ccp(0,0));
    this->m_SpeedLabel->setPosition(ccp(0,0));
    
    //パワーラベル
    sprintf(buff,DEF_PRINTSTR_POWER,0L);
    this->m_PowerLabel = CCLabelTTF::create(buff, "Helvetica", 48);
    this->m_PowerLabel->setAnchorPoint(ccp(0,0));
    this->m_PowerLabel->setPosition(ccp(0,
                                        this->m_SpeedLabel->getContentSize().height));
    
    this->addChild(this->m_HiScoreLabel,DEF_Z_UI);
    this->addChild(this->m_ScoreLabel,DEF_Z_UI);
    this->addChild(this->m_ReadyLabel,DEF_Z_UI);
    this->addChild(this->m_SpeedLabel,DEF_Z_UI);
    this->addChild(this->m_PowerLabel,DEF_Z_UI);
    
    
    //ボタンの位置
    menuPush->setPosition(ccp(size.width -
                              menuPush->getContentSize().width * 0.5f,
                              menuPush->getContentSize().height * 0.5f));
    this->m_menu->setPosition(0, 0);
    this->m_ReadyLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
    
    //開始
    shotChenge();

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
            this->planetLookAnime();
            break;
        case SSHOT_READY:
            this->readyCheck();
            break;
        case SSHOT_PUSH_PLAY:
            this->pushRushPlay();
            break;
        case SSHOT_SHUTTLE_ANIME:
            this->launchShuttleAnime();
            break;
        case SSHOT_SCORE:
        case SSHOT_RETRY:
            
        default:
            break;
    }
}
/**
 * 次の設定シーンを取得する
 */
ShuttleScene::SHOT_SECNE ShuttleScene::nextShotSceneSelecter(SHOT_SECNE val)
{
    SHOT_SECNE ret = SSHOT_NONE;
    
    switch (val) {
        case SSHOT_INIT:
            ret = SSHOT_READY;
            break;
        case SSHOT_READY:
            ret = SSHOT_PUSH_PLAY;
            break;
        case SSHOT_PUSH_PLAY:
            ret = SSHOT_SHUTTLE_ANIME;
            break;
        case SSHOT_SHUTTLE_ANIME:
            ret = SSHOT_SCORE;
            break;
        case SSHOT_SCORE:
        case SSHOT_RETRY:
            
        default:
            ret = SSHOT_INIT;
            break;
    }
    
    return ret;
}

/**
 * シーンを切り替える
 */
void ShuttleScene::shotChenge()
{
    //数値更新
    this->refleshStetusLabel();

    //次のシーンを選択
    this->m_shotSceneState = nextShotSceneSelecter(m_shotSceneState);
    
    //カットシーンに合わせて修正
    this->settingShotSceneObject(m_shotSceneState);
}

/**
 * ラッシュボタンのタップ
 */
void ShuttleScene::tapRushButton()
{
    if(this->m_shotSceneState == SSHOT_READY)
    {
        this->shotChenge();
    }
    
    //エネルギーチャージ
    this->m_RocketSprite->chargeEnergy();
    
    //項目の更新
    this->refleshStetusLabel();
}

/**
 * 数値関連の数値更新
 */
void ShuttleScene::refleshStetusLabel()
{
    char buff[100];
    
    //ハイスコア
    sprintf(buff,DEF_PRINTSTR_HISCORE,0);
    this->m_HiScoreLabel->setString(buff);
    
    //スコア
    sprintf(buff,DEF_PRINTSTR_SCORE,0);
    this->m_ScoreLabel->setString(buff);
    
    //スピードラベル
    sprintf(buff,DEF_PRINTSTR_SPEED,this->m_RocketSprite->getSpeed());
    this->m_SpeedLabel->setString(buff);
    
    //パワーラベル
    sprintf(buff,DEF_PRINTSTR_POWER,this->m_RocketSprite->getEnergy());
    this->m_PowerLabel->setString(buff);
    
}
/**
 * UIオブジェクトの表示非表示
 */
void ShuttleScene::UIsVisible(bool val)
{
    this->m_menu->setVisible(val);
    this->m_HiScoreLabel->setVisible(val);
    this->m_ScoreLabel->setVisible(val);
    this->m_SpeedLabel->setVisible(val);
    this->m_PowerLabel->setVisible(val);
}

#pragma mark カットシーン処理類
/**
 * 惑星を見上げたところからのアニメーション
 */
void ShuttleScene::planetLookAnime()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->m_ReadyLabel->setVisible(false);
    //ロケット初期位置
    this->m_RocketSprite->setPosition(size.width * 0.5f,size.height * 0.5f);
    this->m_RocketSprite->resetParam();
    
    //雲の配置
    this->m_CloudSprite1->setPosition(ccp(this->m_PlanetSprite->getPosition().x - 30.0f,
                                          this->m_PlanetSprite->getPosition().y + 5));
    this->m_CloudSprite2->setPosition(ccp(this->m_PlanetSprite->getPosition().x + 30.0f,
                                          this->m_PlanetSprite->getPosition().y - 5));
    this->m_CloudSprite1->setOpacity(0xFF);
    this->m_CloudSprite2->setOpacity(0xFF);
    this->m_CloudSprite1->setScale(1.5f);
    this->m_CloudSprite2->setScale(1.5f);
    
    //背景見上げる
    this->m_BackGroundLayer->setPosition(
                                         ccp(this->m_BackGroundLayer->getPosition().x,
                                             -DEF_BG_HEIGHT + size.height));
    CCArray * seqlist = CCArray::create();
    seqlist->addObject(CCDelayTime::create(2.5f));
    seqlist->addObject(CCMoveTo::create(1.5f, ccp(this->m_BackGroundLayer->getPosition().x,0)));
    seqlist->addObject(CCCallFunc::create(this, callfunc_selector(ShuttleScene::shotChenge)));
    this->m_BackGroundLayer->runAction(CCSequence::create(seqlist));
    
    //雲が開けるアニメーション
    this->m_CloudSprite1->runAction(CCSequence::create(CCDelayTime::create(1.0f),
                                                       CCSpawn::createWithTwoActions(
                                                                                     CCMoveBy::create(1, ccp(-100, 0)),
                                                                                     CCFadeTo::create(1,0)
                                                                                     )
                                                       ,NULL)
                                    );
    this->m_CloudSprite2->runAction(CCSequence::create(CCDelayTime::create(1.0f),
                                                       CCSpawn::createWithTwoActions(
                                                                                     CCMoveBy::create(1, ccp(100, 0)),
                                                                                     CCFadeTo::create(1,0)
                                                                                     )
                                                       ,NULL)
                                    );
    
    //ステータスやボタンを押せなくする
    this->UIsVisible(false);
}
/**
 * 準備完了？の処理
 */
void ShuttleScene::readyCheck()
{
    this->m_ReadyLabel->setVisible(true);
    this->m_ReadyLabel->setString("Are you ready?");
    
    this->UIsVisible(true);
}
/**
 * RUSHタイム
 */
void ShuttleScene::pushRushPlay()
{
    this->m_ReadyLabel->setVisible(false);
    
    CCArray *seq = CCArray::create();
    seq->addObject(CCDelayTime::create(DEF_RUSH_TIME));
    seq->addObject(CCCallFunc::create(this,callfunc_selector(ShuttleScene::shotChenge)));
    
    this->runAction(CCSequence::create(seq));
}
/**
 * シャトル発射
 */
void ShuttleScene::launchShuttleAnime()
{
    this->m_menu->setVisible(false);
}


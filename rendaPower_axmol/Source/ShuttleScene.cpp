#include "ShuttleScene.h"
#include "axmol.h"
#include "audio/AudioEngine.h"

using namespace ax;

#define DEF_PRINTSTR_HISCORE    ("HiScore %8ld")
#define DEF_PRINTSTR_SCORE      ("Score   %8ld")
#define DEF_PRINTSTR_SPEED      ("Speed %4ld")
#define DEF_PRINTSTR_POWER      ("Power %4ld")

#define DEF_BG_HEIGHT   (4000)
#define DEF_TAG_RUSH_BTN (10000)
#define DEF_Z_UI (1000)
#define DEF_RUSH_TIME (10)

/**
 * コンストラクタ
 */
ShuttleScene::ShuttleScene()
:m_ReadyLabel(nullptr)
,m_ScoreLabel(nullptr)
,m_PowerLabel(nullptr)
,m_HiScoreLabel(nullptr)
,m_SpeedLabel(nullptr)
,m_menu(nullptr)
,m_PlanetSprite(nullptr)
,m_RocketSprite(nullptr)
,m_CloudSprite1(nullptr)
,m_CloudSprite2(nullptr)
,m_BackGroundLayer(nullptr)
,m_CountSprite(nullptr)
,m_shotSceneState(SSHOT_NONE)
,m_moveShuttle(false)
,m_Score(0)
,m_HiScore(0)
,m_ScoreBackGround(nullptr)
{
    
}
/**
 * デストラクタ
 */
ShuttleScene::~ShuttleScene()
{
}

Scene* ShuttleScene::scene()
{
    auto *scene = Scene::create();
    auto *layer = ShuttleScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool ShuttleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto size = Director::getInstance()->getWinSize();
        
    //背景
    auto * backGround1 = Sprite::create("base/rocketBackGraund_1.png");
    auto * backGround2 = Sprite::create("base/rocketBackGraund_2.png");
    auto * backGround3 = Sprite::create("base/rocketBackGraund_3.png");
    auto * backGround4 = Sprite::create("base/rocketBackGraund_4.png");
    
    m_BackGroundLayer = LayerGradient::create(Color4B(0x0, 0x0, 0x0, 0xFF), Color4B(0x3a, 0x3a, 0x3a, 0xff));
    this->m_BackGroundLayer->setContentSize(Size(size.width, DEF_BG_HEIGHT + size.height));
    this->m_BackGroundLayer->addChild(backGround1,1);
    this->m_BackGroundLayer->addChild(backGround2,1);
    this->m_BackGroundLayer->addChild(backGround3,1);
    this->m_BackGroundLayer->addChild(backGround4,1);
    
    backGround1->setAnchorPoint(Vec2(0.5f,0.5f));
    backGround2->setAnchorPoint(Vec2(0.5f,0.5f));
    backGround3->setAnchorPoint(Vec2(0.5f,0.5f));
    backGround4->setAnchorPoint(Vec2(0.5f,0.5f));
    
    Vec2 pos(this->m_BackGroundLayer->getContentSize().width * 0.5f,
             this->m_BackGroundLayer->getContentSize().height * 0.5f);
    pos.y += 1875;
    backGround1->setPosition(pos);
    pos.y -= 1250;
    backGround2->setPosition(pos);
    pos.y -= 1250;
    backGround3->setPosition(pos);
    pos.y -= 1250;
    backGround4->setPosition(pos);
    this->addChild(this->m_BackGroundLayer,0);
    
    this->m_PlanetSprite = Sprite::create("base/planet.png");
    this->m_RocketSprite = ShuttleModel::create();
    this->m_CloudSprite1 = Sprite::create("base/kumo.png");
    this->m_CloudSprite2 = Sprite::create("base/kumo.png");
    
    this->m_BackGroundLayer->addChild(this->m_PlanetSprite, 10);
    this->m_BackGroundLayer->addChild(this->m_CloudSprite1, 15);
    this->m_BackGroundLayer->addChild(this->m_CloudSprite2, 16);
    this->m_BackGroundLayer->addChild(this->m_RocketSprite, 20);
    
    this->m_PlanetSprite->setPosition(
        Vec2(size.width * 0.5f, DEF_BG_HEIGHT + size.height * 0.5f));

    this->m_menu = Menu::create();
    this->m_menu->setPosition(Vec2::ZERO);
    
    //RUSHボタンの生成
    auto* normalSprite = Sprite::create("base/tap_button.png");
    auto* selectSprite = Sprite::create("base/tap_button.png");
    selectSprite->setColor(Color3B(0x7F, 0x7F, 0x7F));
    
    auto* menuPush = MenuItemSprite::create(normalSprite, selectSprite, AX_CALLBACK_0(ShuttleScene::tapRushButton, this));
    menuPush->setTag(DEF_TAG_RUSH_BTN);
    this->m_menu->addChild(menuPush);
    this->addChild(this->m_menu, 5000);
    
    //UIの構成
    char buff[100] = "";
    this->m_HiScore = UserDefault::getInstance()->getIntegerForKey("HiScore", 0);
    
    sprintf(buff, DEF_PRINTSTR_HISCORE, this->m_HiScore);
    this->m_HiScoreLabel = Label::createWithBMFont("base/bmfRocket.fnt", buff);
    this->m_HiScoreLabel->setAnchorPoint(Vec2(0.0, 1.0f));
    this->m_HiScoreLabel->setPosition(Vec2(0, size.height));
    
    sprintf(buff, DEF_PRINTSTR_SCORE, this->m_Score);
    this->m_ScoreLabel = Label::createWithBMFont("base/bmfRocket.fnt", buff);
    this->m_ScoreLabel->setAnchorPoint(Vec2(0.0, 1.0f));
    this->m_ScoreLabel->setPosition(Vec2(0, size.height - this->m_HiScoreLabel->getContentSize().height));

    this->m_ReadyLabel = Label::createWithBMFont("base/bmfRocket.fnt", "");
    this->m_ReadyLabel->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));

    sprintf(buff, DEF_PRINTSTR_SPEED, 0L);
    this->m_SpeedLabel = Label::createWithBMFont("base/bmfRocket.fnt", buff);
    this->m_SpeedLabel->setAnchorPoint(Vec2(0, 0));
    this->m_SpeedLabel->setPosition(Vec2(0, 0));
    
    sprintf(buff, DEF_PRINTSTR_POWER, 0L);
    this->m_PowerLabel = Label::createWithBMFont("base/bmfRocket.fnt", buff);
    this->m_PowerLabel->setAnchorPoint(Vec2(0, 0));
    this->m_PowerLabel->setPosition(Vec2(0, this->m_SpeedLabel->getContentSize().height));
    
    this->addChild(this->m_HiScoreLabel, DEF_Z_UI);
    this->addChild(this->m_ScoreLabel, DEF_Z_UI);
    this->addChild(this->m_ReadyLabel, DEF_Z_UI);
    this->addChild(this->m_SpeedLabel, DEF_Z_UI);
    this->addChild(this->m_PowerLabel, DEF_Z_UI);
    
    menuPush->setPosition(Vec2(size.width - menuPush->getContentSize().width * 0.5f,
                               menuPush->getContentSize().height * 0.5f));
    
    //カウントダウンスプライト
    this->m_CountSprite = CountNumberSprite::create();
    this->m_CountSprite->setAdd(1);
    this->m_CountSprite->setInterval(2.0f);
    this->m_CountSprite->setMax(5);
    this->m_CountSprite->setMin(0);
    this->m_CountSprite->setCountType(CountNumberSprite::CT_DOWN);
    this->m_CountSprite->setEndCallback(AX_CALLBACK_0(ShuttleScene::shotChenge, this));
    this->m_CountSprite->setPosition(Vec2(size.width * 0.5f, size.height * 0.25f));
    this->addChild(this->m_CountSprite, DEF_Z_UI);

    //スコア表示画面
    this->m_ScoreBackGround = ScoreLayer::create();
    this->m_ScoreBackGround->setPosition(Vec2::ZERO);
    this->m_ScoreBackGround->setVisible(false);
    this->m_ScoreBackGround->setRetryCallback(AX_CALLBACK_0(ShuttleScene::shotChenge, this));
    this->addChild(this->m_ScoreBackGround, DEF_Z_UI + 1);
    
    shotChenge();
    return true;
}

void ShuttleScene::settingShotSceneObject(SHOT_SECNE val)
{
    switch (val) {
        case SSHOT_INIT: this->planetLookAnime(); break;
        case SSHOT_READY: this->readyCheck(); break;
        case SSHOT_PUSH_PLAY: this->pushRushPlay(); break;
        case SSHOT_SHUTTLE_TAKEOFF: this->launchShuttleAnime(); break;
        case SSHOT_SHUTTLE_MOVE: this->launchShuttleMove(); break;
        case SSHOT_SCORE: this->scoreView(); break;
        case SSHOT_RETRY: this->retryView(); break;
        default: break;
    }
}

ShuttleScene::SHOT_SECNE ShuttleScene::nextShotSceneSelecter(SHOT_SECNE val)
{
    switch (val) {
        case SSHOT_INIT: return SSHOT_READY;
        case SSHOT_READY: return SSHOT_PUSH_PLAY;
        case SSHOT_PUSH_PLAY: return SSHOT_SHUTTLE_TAKEOFF;
        case SSHOT_SHUTTLE_TAKEOFF: return SSHOT_SHUTTLE_MOVE;
        case SSHOT_SHUTTLE_MOVE: return SSHOT_SCORE;
        case SSHOT_SCORE: return SSHOT_RETRY;
        case SSHOT_RETRY:
        default: return SSHOT_INIT;
    }
}

void ShuttleScene::shotChenge()
{
    this->refreshStetusLabel();
    this->m_shotSceneState = nextShotSceneSelecter(m_shotSceneState);
    this->settingShotSceneObject(m_shotSceneState);
}

void ShuttleScene::tapRushButton()
{
    if(this->m_shotSceneState == SSHOT_READY) {
        this->shotChenge();
    }
    this->m_RocketSprite->chargeEnergy();
    this->refreshStetusLabel();
}

void ShuttleScene::refreshStetusLabel()
{
    char buff[100];
    sprintf(buff, DEF_PRINTSTR_HISCORE, this->m_HiScore);
    this->m_HiScoreLabel->setString(buff);
    sprintf(buff, DEF_PRINTSTR_SCORE, this->m_Score);
    this->m_ScoreLabel->setString(buff);
    sprintf(buff, DEF_PRINTSTR_SPEED, this->m_RocketSprite->getSpeed());
    this->m_SpeedLabel->setString(buff);
    sprintf(buff, DEF_PRINTSTR_POWER, this->m_RocketSprite->getEnergy());
    this->m_PowerLabel->setString(buff);
}

void ShuttleScene::UIsVisible(bool val)
{
    this->m_menu->setVisible(val);
    this->m_HiScoreLabel->setVisible(val);
    this->m_ScoreLabel->setVisible(val);
    this->m_SpeedLabel->setVisible(val);
    this->m_PowerLabel->setVisible(val);
}

void ShuttleScene::update(float delta)
{
    Layer::update(delta);
    auto size = Director::getInstance()->getWinSize();
    if(m_moveShuttle) {
        Vec2 roketPos = this->m_RocketSprite->getPosition();
        Vec2 bkgPos = roketPos - Vec2(size.width * 0.5f, size.height * 0.5f);
        this->m_BackGroundLayer->setPosition(-bkgPos);
        m_Score = bkgPos.y;
        this->m_PlanetSprite->setScale(1.0f + (-this->m_BackGroundLayer->getPosition().y / DEF_BG_HEIGHT) * 3);
        if(this->m_RocketSprite->getSpeed() <= 0 || this->m_BackGroundLayer->getPosition().y + DEF_BG_HEIGHT <= 0) {
            this->shotChenge();
        }
        this->refreshStetusLabel();
    }
}

void ShuttleScene::planetLookAnime()
{
    auto size = Director::getInstance()->getWinSize();
    this->m_ReadyLabel->setVisible(false);
    this->m_CountSprite->setVisible(false);
    this->m_CountSprite->resetCount();
    this->m_ScoreBackGround->setVisible(false);
    this->m_RocketSprite->setPosition(size.width * 0.5f, size.height * 0.5f);
    this->m_RocketSprite->resetParam();
    this->m_PlanetSprite->setScale(1.0f);
    this->m_CloudSprite1->setPosition(Vec2(this->m_PlanetSprite->getPosition().x - 30.0f, this->m_PlanetSprite->getPosition().y + 5));
    this->m_CloudSprite2->setPosition(Vec2(this->m_PlanetSprite->getPosition().x + 30.0f, this->m_PlanetSprite->getPosition().y - 5));
    this->m_CloudSprite1->setOpacity(0xFF);
    this->m_CloudSprite2->setOpacity(0xFF);
    this->m_CloudSprite1->setScale(1.5f);
    this->m_CloudSprite2->setScale(1.5f);
    this->m_BackGroundLayer->setPosition(Vec2(this->m_BackGroundLayer->getPosition().x, - DEF_BG_HEIGHT));
    
    auto seq = Sequence::create(
        DelayTime::create(2.5f),
        MoveTo::create(1.5f, Vec2(this->m_BackGroundLayer->getPosition().x, 0)),
        CallFunc::create(AX_CALLBACK_0(ShuttleScene::shotChenge, this)),
        nullptr
    );
    this->m_BackGroundLayer->runAction(seq);
    
    this->m_CloudSprite1->runAction(Sequence::create(
        DelayTime::create(1.0f),
        Spawn::create(MoveBy::create(1, Vec2(-100, 0)), FadeTo::create(1, 0), nullptr),
        nullptr
    ));
    this->m_CloudSprite2->runAction(Sequence::create(
        DelayTime::create(1.0f),
        Spawn::create(MoveBy::create(1, Vec2(100, 0)), FadeTo::create(1, 0), nullptr),
        nullptr
    ));
    this->UIsVisible(false);
}

void ShuttleScene::readyCheck()
{
    this->m_ReadyLabel->setVisible(true);
    this->m_ReadyLabel->setString("Are you ready?");
    this->UIsVisible(true);
}

void ShuttleScene::pushRushPlay()
{
    this->m_ReadyLabel->setVisible(false);
    this->m_CountSprite->setVisible(true);
    this->m_CountSprite->startCount();
}

void ShuttleScene::launchShuttleAnime()
{
    this->m_menu->setVisible(false);
    this->m_CountSprite->setVisible(false);
    this->m_RocketSprite->rocketStart(AX_CALLBACK_0(ShuttleScene::shotChenge, this));
}

void ShuttleScene::launchShuttleMove()
{
    this->runAction(Sequence::create(
        DelayTime::create(0.5f),
        CallFunc::create([this](){ this->scheduleUpdate(); }),
        nullptr
    ));
    this->m_moveShuttle = true;
}

void ShuttleScene::scoreView()
{
    this->unscheduleUpdate();
    this->m_moveShuttle = false;
    if(this->m_HiScore < this->m_Score) {
        this->m_HiScore = this->m_Score;
        UserDefault::getInstance()->setIntegerForKey("HiScore", (int)this->m_HiScore);
    }
    this->m_ScoreBackGround->setVisible(true);
    this->m_ScoreBackGround->setScore((int)this->m_Score, (int)this->m_HiScore);
    this->m_ScoreBackGround->setVisibleRetryButton(false);
    
    this->runAction(Sequence::create(
        DelayTime::create(1.0f),
        CallFunc::create(AX_CALLBACK_0(ShuttleScene::shotChenge, this)),
        nullptr
    ));
}

void ShuttleScene::retryView()
{
    this->m_ScoreBackGround->setVisibleRetryButton(true);
}



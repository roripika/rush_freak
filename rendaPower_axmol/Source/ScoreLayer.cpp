#include "ScoreLayer.h"
#include "axmol.h"
#include "audio/AudioEngine.h"
#include "TitleScene.h"

using namespace ax;

ScoreLayer::ScoreLayer()
:m_ScoreLabel(nullptr)
,m_HiScoreLabel(nullptr)
,m_StrScoreSLabel(nullptr)
,m_StrHiScoreSLabel(nullptr)
,m_RetryLabelButton(nullptr)
,m_TopLabelButton(nullptr)
,m_callback(nullptr)
{
}

ScoreLayer::~ScoreLayer()
{
}

bool ScoreLayer::init()
{
    auto size = Director::getInstance()->getWinSize();
    
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 0x3A), size.width, size.height))
    {
        return false;
    }
    
    this->m_StrHiScoreSLabel = Label::createWithSystemFont("HiScore:", "Helvetica", 50, Size(250, 60), TextHAlignment::CENTER);
    this->m_HiScoreLabel = Label::createWithSystemFont("", "Helvetica", 50, Size(250, 60), TextHAlignment::RIGHT);
    this->m_StrScoreSLabel = Label::createWithSystemFont("Score:", "Helvetica", 50, Size(250, 60), TextHAlignment::CENTER);
    this->m_ScoreLabel = Label::createWithSystemFont("", "Helvetica", 50, Size(250, 60), TextHAlignment::RIGHT);
    
    this->addChild(this->m_StrHiScoreSLabel, 1);
    this->addChild(this->m_HiScoreLabel, 1);
    this->addChild(this->m_StrScoreSLabel, 1);
    this->addChild(this->m_ScoreLabel, 1);
    
    this->m_StrHiScoreSLabel->setPosition(Vec2(size.width * 0.25f, size.height * 0.75f));
    this->m_HiScoreLabel->setPosition(Vec2(size.width * 0.75f, size.height * 0.75f));
    this->m_StrScoreSLabel->setPosition(Vec2(size.width * 0.25f, size.height * 0.5f));
    this->m_ScoreLabel->setPosition(Vec2(size.width * 0.75f, size.height * 0.5f));

    //リトライ
    auto *retrylabel = Label::createWithSystemFont("[Retry?]", "Helvetica", 50, Size(280, 60), TextHAlignment::CENTER);
    this->m_RetryLabelButton = MenuItemLabel::create(retrylabel, AX_CALLBACK_0(ScoreLayer::onRetry, this));
    this->m_RetryLabelButton->setPosition(Vec2(size.width * 0.25f, size.height * 0.25f));

    //トップ画面
    auto *toplabel = Label::createWithSystemFont("[Top Menu?]", "Helvetica", 50, Size(280, 60), TextHAlignment::CENTER);
    this->m_TopLabelButton = MenuItemLabel::create(toplabel, AX_CALLBACK_0(ScoreLayer::onMoveSceneTop, this));
    this->m_TopLabelButton->setPosition(Vec2(size.width * 0.75f, size.height * 0.25f));

    auto * menu = Menu::create(this->m_RetryLabelButton, this->m_TopLabelButton, nullptr);
    this->addChild(menu, 100);
    menu->setPosition(Vec2::ZERO);
    
    return true;
}

void ScoreLayer::setScore(unsigned long score, unsigned long hiscore)
{
    char buf[128] = "";
    sprintf(buf, "%ld", score);
    this->m_ScoreLabel->setString(buf);
    sprintf(buf, "%ld", hiscore);
    this->m_HiScoreLabel->setString(buf);
}

void ScoreLayer::setVisibleRetryButton(bool val)
{
    this->m_RetryLabelButton->setVisible(val);
    this->m_TopLabelButton->setVisible(val);
}

void ScoreLayer::setRetryCallback(std::function<void()> callback)
{
    this->m_callback = callback;
}

void ScoreLayer::onMoveSceneTop()
{
    Director::getInstance()->replaceScene(TitleScene::scene());
}

void ScoreLayer::onRetry()
{
    if(this->m_callback)
    {
        this->m_callback();
    }
}

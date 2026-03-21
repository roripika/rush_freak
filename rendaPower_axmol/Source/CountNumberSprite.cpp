#include "CountNumberSprite.h"
#include "axmol.h"

using namespace ax;

bool CountNumberSprite::init()
{
    if(!Node::init())
    {
        return false;
    }
    
    this->m_countLabel = Label::createWithBMFont("base/bmfRocket.fnt", "0", TextHAlignment::CENTER);
    this->m_countLabel->setAnchorPoint(Vec2::ZERO);
    this->addChild(this->m_countLabel);
    
    this->setContentSize(Size(70, 70));
    return true;
}

CountNumberSprite::CountNumberSprite()
:m_Count(0)
,m_type(CT_UP)
,m_countLabel(nullptr)
,m_Add(1)
,m_Interval(1.0f)
,m_EndCallback(nullptr)
,m_MinCount(0)
,m_MaxCount(10)
{
}

CountNumberSprite::~CountNumberSprite()
{
}

void CountNumberSprite::startCount()
{
    onCountUp();
}

void CountNumberSprite::stopCount()
{
    this->stopAllActions();
}

void CountNumberSprite::resetCount()
{
    switch (m_type)
    {
        case CT_DOWN:
            this->m_Count = this->m_MaxCount;
            break;
        case CT_UP:
        default:
            this->m_Count = this->m_MinCount;
            break;
    }
}

/**
 * カウントアップイベント
 */
void CountNumberSprite::onCountUp()
{
    //ラベルの文字設定
    char moji[5] = "";
    sprintf(moji, "%ld", this->m_Count);
    this->m_countLabel->setString(moji);
    
    //判定
    if(this->m_type == CT_DOWN)
    {
        if(this->m_Count <= this->m_MinCount)
        {
            onCountEnd();
            return;
        }
    }
    else
    {
        if(this->m_Count >= this->m_MaxCount)
        {
            onCountEnd();
            return;
        }
    }
    
    //アニメーション設定
    auto seq = Sequence::create(
        DelayTime::create((float)this->m_Interval),
        CallFunc::create(AX_CALLBACK_0(CountNumberSprite::onCountUp, this)),
        nullptr
    );
    runAction(seq);
    
    //増加
    if(this->m_type == CT_DOWN)
    {
        this->m_Count -= this->m_Add;
    }
    else
    {
        this->m_Count += this->m_Add;
    }
}

/**
 * カウント終了
 */
void CountNumberSprite::onCountEnd()
{
    if(this->m_EndCallback)
    {
        this->m_EndCallback();
    }
}

/**
 * コールバックの設定
 */
void CountNumberSprite::setEndCallback(std::function<void()> endCallback)
{
    this->m_EndCallback = endCallback;
}

#pragma mark ゲッターセッター

void CountNumberSprite::setCountType(CountType val)
{
    this->m_type = val;
}

CountNumberSprite::CountType CountNumberSprite::getCountType()
{
    return this->m_type;
}

void CountNumberSprite::setMin(long val)
{
    this->m_MinCount = val;
}
long CountNumberSprite::getMin()
{
    return this->m_MinCount;
}
void CountNumberSprite::setMax(long val)
{
    this->m_MaxCount = val;
}
long CountNumberSprite::getMax()
{
    return this->m_MaxCount;
}
void CountNumberSprite::setAdd(long val)
{
    this->m_Add = val;
}
long CountNumberSprite::getAdd()
{
    return this->m_Add;
}
void CountNumberSprite::setInterval(long val)
{
    this->m_Interval = val;
}
long CountNumberSprite::getInterval()
{
    return this->m_Interval;
}

//
//  ShuttleModel.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/05/27.
//
//

#include "ShuttleModel.h"

USING_NS_CC;

const unsigned long ShuttleModel::CHARGE_ADD = 10;
const unsigned long ShuttleModel::CHARGE_MAX = 1000;
const unsigned long ShuttleModel::ACCELERATION = 5;
const unsigned long ShuttleModel::SPEED_MAX = 50;

ShuttleModel::ShuttleModel()
:m_Energy(0)
,m_Speed(0)
,m_RocketSprite(NULL)
{
}

ShuttleModel::~ShuttleModel()
{
    
}

bool ShuttleModel::init()
{
    if(!CCNode::init())
    {
        return false;
    }
        
    if(this->m_RocketSprite)this->m_RocketSprite->removeFromParent();
    this->m_RocketSprite = CCSprite::create("base/rocket.png");
    this->addChild(this->m_RocketSprite);
    
    this->setContentSize(this->m_RocketSprite->getContentSize());
    this->setAnchorPoint(ccp(0.5f,0.5f));
    
    this->m_RocketSprite->setPosition(ccp(this->getContentSize().width * 0.5f,
                                          this->getContentSize().height * 0.5f));
    
    return true;
}
/**
 * エネルギーチャージ
 */
void ShuttleModel::chargeEnergy()
{
    if(this->m_Energy < CHARGE_MAX)
    {
        this->m_Energy += CHARGE_ADD;
        if(this->m_Energy > CHARGE_MAX)
        {
            this->m_Energy = CHARGE_MAX;
        }
    }
}

/**
 * 値リセット
 */
void ShuttleModel::resetParam()
{
    this->m_Energy = 0;
    this->m_Speed = 0;
}

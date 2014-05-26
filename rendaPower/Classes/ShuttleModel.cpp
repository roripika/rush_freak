//
//  ShuttleModel.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/05/27.
//
//

#include "ShuttleModel.h"

USING_NS_CC;

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
    this->m_Energy += this->CHARGE_ADD;
}

/**
 * 値リセット
 */
void ShuttleModel::resetParam()
{
    this->m_Energy = 0;
    this->m_Speed = 0;
}

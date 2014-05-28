//
//  CountNumber.cpp
//  rendaPower
//
//  Created by ooharayukio on 2014/05/28.
//
//

#include "CountNumberSprite.h"

USING_NS_CC;

bool CountNumberSprite::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
    return true;
}
CountNumberSprite::CountNumberSprite()
{
    
}
CountNumberSprite::~CountNumberSprite()
{
    
}

void CountNumberSprite::startCount()
{
    
}
void CountNumberSprite::stopCount()
{
    
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
            this->m_Count = 0;
            break;
    }
}
void CountNumberSprite::setType(COUNT_TYPE val)
{
    m_type = val;
}
COUNT_TYPE CountNumberSprite::getType()
{
    return m_type;
}

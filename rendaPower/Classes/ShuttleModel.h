//
//  ShuttleModel.h
//  rendaPower
//
//  Created by 大原幸夫 on 2014/05/27.
//
//

#ifndef __rendaPower__ShuttleModel__
#define __rendaPower__ShuttleModel__

#include "cocos2d.h"

class ShuttleModel:public cocos2d::CCNode
{
protected:
    const unsigned long CHARGE_ADD = 10;
    const unsigned long CHARGE_MAX = 300;
    const unsigned long ACCELERATION = 5;
    const unsigned long SPEED_MAX = 50;
    cocos2d::CCSprite* m_RocketSprite;
public:
    ShuttleModel();
    ~ShuttleModel();
    CREATE_FUNC(ShuttleModel);
    virtual bool init();
    
    CC_SYNTHESIZE(long,m_Energy,Energy);
    CC_SYNTHESIZE(long,m_Speed,Speed);
    
    /**
     * エネルギーチャージ
     */
    virtual void chargeEnergy();
    
    /**
     * 値リセット
     */
    virtual void resetParam();
};

#endif /* defined(__rendaPower__ShuttleModel__) */

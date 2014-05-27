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
    static unsigned long CHARGE_ADD;
    static unsigned long CHARGE_MAX;
    static unsigned long ACCELERATION;
    static unsigned long SPEED_MAX;
    cocos2d::CCSprite* m_RocketSprite;
public:
    ShuttleModel();
    virtual ~ShuttleModel();
    virtual bool init();
    
    CREATE_FUNC(ShuttleModel);
    
    /**
     * エネルギーチャージ
     */
    virtual void chargeEnergy();
    
    /**
     * 値リセット
     */
    virtual void resetParam();

    
    CC_SYNTHESIZE(long,m_Energy,Energy);
    CC_SYNTHESIZE(long,m_Speed,Speed);
    
};

#endif /* defined(__rendaPower__ShuttleModel__) */

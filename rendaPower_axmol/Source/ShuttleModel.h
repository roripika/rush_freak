//
//  ShuttleModel.h
//  rendaPower
//
//  Created by roripika on 2014/05/27.
//
//

#ifndef __rendaPower__ShuttleModel__
#define __rendaPower__ShuttleModel__

#include "axmol.h"

class ShuttleModel : public ax::Node
{
protected:
    std::function<void()> m_takeoffCallback;
    
    static const unsigned long CHARGE_ADD;
    static const unsigned long CHARGE_MAX;
    static const unsigned long ACCELERATION;
    static const unsigned long SPEED_MAX;
    static const float ENERGY_CONVERT;
    ax::Sprite* m_RocketSprite;
    
    ax::ParticleSmoke * m_smork;

    /**
     * 画面更新
     */
    virtual void update(float delta) override;

    /**
     * 離陸
     */
    virtual void takeoff();
    
    /**
     * エネルギー消費
     */
    virtual void energyConsumption();
    //
    bool m_runAcceleration;
public:
    ShuttleModel();
    virtual ~ShuttleModel() override;
    virtual bool init() override;
    
    CREATE_FUNC(ShuttleModel);
    
    /**
     * エネルギーチャージ
     */
    virtual void chargeEnergy();
    
    /**
     * 値リセット
     */
    virtual void resetParam();
    
    /**
     * 飛び出そう
     */
    virtual void rocketStart(std::function<void()> takeoffCallback);

    /**
     * 加速
     */
    virtual void acceleration();

    /**
     * 減速
     */
    virtual void slowdown();

    AX_SYNTHESIZE(long, m_Energy, Energy);
    AX_SYNTHESIZE(long, m_Speed, Speed);
};

#endif /* defined(__rendaPower__ShuttleModel__) */

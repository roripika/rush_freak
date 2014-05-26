//
//  ShuttleScene.h
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#ifndef __rendaPower__PlayScene__
#define __rendaPower__PlayScene__

#include "cocos2d.h"
#include "ShuttleModel.h"

/**
 * スペースシャトルのゲームプレイ
 */
class ShuttleScene : public cocos2d::CCLayer
{
protected:
    cocos2d::CCSprite * m_PlanetSprite;
    ShuttleModel * m_RocketSprite;
    cocos2d::CCSprite * m_CloudSprite1;
    cocos2d::CCSprite * m_CloudSprite2;
    cocos2d::CCLayerGradient * m_BackGroundLayer;
    
    cocos2d::CCMenu * m_menu;
    
    cocos2d::CCLabelTTF * m_HiScoreLabel;
    cocos2d::CCLabelTTF * m_ScoreLabel;
    cocos2d::CCLabelTTF * m_ReadyLabel;
    cocos2d::CCLabelTTF * m_SpeedLabel;
    cocos2d::CCLabelTTF * m_PowerLabel;
    
    long m_PowerPoint;
    long m_Score;
    long m_HiScore;
    
    enum SHOT_SECNE
    {
        SSHOT_INIT = 0,
        SSHOT_READY,
        SSHOT_START_COUNT,
        SSHOT_PUSH_PLAY,
        SSHOT_SHUTTLE_ANIME,
        SSHOT_SCORE,
        SSHOT_RETRY
    };
    
    SHOT_SECNE m_shotSceneState;
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    /**
     * コンストラクタ
     */
    ShuttleScene();
    /**
     * デストラクタ
     */
    ~ShuttleScene();
        
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ShuttleScene);
    
    /**
     * 設定をシーンによって変える
     */
    virtual void settingShotSceneObject(SHOT_SECNE val);
    
    /**
     * シーンを切り替える
     */
    virtual void shotChenge();
    
    /**
     * パワー値をためる
     */
    virtual void powerCountup();
    
    /**
     * 惑星を見上げたところからのアニメーション
     */
    virtual void planetLookAnime();
    
};

#endif /* defined(__rendaPower__PlayScene__) */

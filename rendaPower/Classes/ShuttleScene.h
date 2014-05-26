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

/**
 * スペースシャトルのゲームプレイ
 */
class ShuttleScene : public cocos2d::CCLayer
{
protected:
    cocos2d::CCSprite * m_PlanetSprite;
    cocos2d::CCSprite * m_RocketSprite;
    
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
};

#endif /* defined(__rendaPower__PlayScene__) */

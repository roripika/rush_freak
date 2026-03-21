//
//  ScoreLayer.h
//  rendaPower
//
//  Created by ooharayukio on 2014/06/02.
//
//

#ifndef __rendaPower__ScoreLayer__
#define __rendaPower__ScoreLayer__

#include "axmol.h"

class ScoreLayer : public ax::LayerColor
{
protected:
    //スコア
    ax::Label * m_ScoreLabel;
    //ハイスコア
    ax::Label * m_HiScoreLabel;
    
    //現在のスコアラベル
    ax::Label * m_StrScoreSLabel;
    //現在のハイスコアラベル
    ax::Label * m_StrHiScoreSLabel;

    //リトライ
    ax::MenuItemLabel * m_RetryLabelButton;
    //トップ画面
    ax::MenuItemLabel * m_TopLabelButton;
    
    virtual void onMoveSceneTop();
    virtual void onRetry();
    
    std::function<void()> m_callback;
    
public:
    CREATE_FUNC(ScoreLayer);
    virtual bool init() override;
    
    ScoreLayer();
    virtual ~ScoreLayer() override;
    
    void setScore(unsigned long score, unsigned long hiscore);
    void setVisibleRetryButton(bool val);
    
    void setRetryCallback(std::function<void()> callback);
};

#endif /* defined(__rendaPower__ScoreLayer__) */

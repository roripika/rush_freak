//
//  CountNumberSprite.h
//  rendaPower
//
//  Created by ooharayukio on 2014/05/28.
//
//

#ifndef __rendaPower__CountNumber__
#define __rendaPower__CountNumber__

#include "axmol.h"

/**
 * カウントダウンスプライトクラス
 */
class CountNumberSprite : public ax::Node
{
public:
    enum CountType
    {
        CT_DOWN = 0,
        CT_UP
    };

protected:
    std::function<void()> m_EndCallback;
    
    long m_MinCount;    //最大値
    long m_MaxCount;    //最小値
    long m_Count;       //カウント数
    long m_Add;         //カウント増加量
    long m_Interval;    //カウント間隔
    CountType m_type;
    
    /**
     * カウントアップイベント
     */
    void onCountUp();
    void onCountEnd();
    
    ax::Label *m_countLabel;
    
public:
    CREATE_FUNC(CountNumberSprite);
    virtual bool init() override;

    CountNumberSprite();
    virtual ~CountNumberSprite() override;

    /**
     * コールバックの設定
     */
    void setEndCallback(std::function<void()> endCallback);

    void startCount();
    void stopCount();
    void resetCount();
    
    void setCountType(CountType val);
    CountType getCountType();
    
    void setMin(long val);
    long getMin();
    void setMax(long val);
    long getMax();
    void setAdd(long val);
    long getAdd();
    void setInterval(long val);
    long getInterval();
};

#endif /* defined(__rendaPower__CountNumber__) */

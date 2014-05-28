//
//  CountNumberSprite.h
//  rendaPower
//
//  Created by ooharayukio on 2014/05/28.
//
//

#ifndef __rendaPower__CountNumber__
#define __rendaPower__CountNumber__

#include "cocos2d.h"

typedef enum _COUNT_TYPE
{
    CT_DOWN = 0,
    CT_UP
}COUNT_TYPE;

/**
 * カウントダウンスプライトクラス
 */
class CountNumberSprite : cocos2d::CCNode
{
protected:
    CCObject* m_EndCallbackTarget;
    SEL_CallFunc m_EndCallback;
    
    long m_MinCount;    //最大値
    long m_MaxCount;    //最小値
    long m_Count;       //カウント数
    long m_Add;         //カウント増加量
    long m_Interval;    //カウント間隔
    COUNT_TYPE m_type;
    
    /**
     * カウントアップイベント
     */
    void onCountUp();
    
    void onCountEnd();
    
public:
    
    CREATE_FUNC(CountNumberSprite);
    virtual bool init();

    CountNumberSprite();
    ~CountNumberSprite();

    void startCount();
    void stopCount();
    void resetCount();
    void setType(COUNT_TYPE val);
    COUNT_TYPE getType();
    
    void setMin(long val);
    long getMin();
    void setMax(long val);
    long getMax();
    void setAdd();
    void getAdd();
    void setInterval(long val);
    long getInterval();
    
};

#endif /* defined(__rendaPower__CountNumber__) */

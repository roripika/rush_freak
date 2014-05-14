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

class ShuttleScene : public cocos2d::CCLayer
{
protected:
    cocos2d::CCSprite * m_PlanetSprite;
    cocos2d::CCSprite * m_RocketSprite;
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
        
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ShuttleScene);
};

#endif /* defined(__rendaPower__PlayScene__) */

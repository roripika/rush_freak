//
//  SplashScene.h
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#ifndef __TreeTest__SplashScene__
#define __TreeTest__SplashScene__

#include "axmol.h"

class SplashScene : public ax::Layer
{
protected:
    void nextScene();
public:
    virtual bool init() override;
    
    static ax::Scene* scene();
    
    void menuCloseCallback(ax::Object* pSender);
    
    CREATE_FUNC(SplashScene);
};

#endif /* defined(__TreeTest__SplashScene__) */

//
//  SelectMenuScene.h
//  rendaPower
//
//  Created by roripika on 2014/02/23.
//
//

#ifndef __rendaPower__SelectMenuScene__
#define __rendaPower__SelectMenuScene__

#include "axmol.h"

class SelectMenuScene : public ax::Layer
{
public:
    virtual bool init() override;
    
    static ax::Scene* scene();
    
    /**
     * シャトル画面にいく
     */
    void moveShuttleScene(ax::Object* obj);
    
    void menuCloseCallback(ax::Object* pSender);
    
    CREATE_FUNC(SelectMenuScene);
};

#endif /* defined(__rendaPower__SelectMenuScene__) */

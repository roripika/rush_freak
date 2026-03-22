//
//  TitleScene.h
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#ifndef __TreeTest__TitleScene__
#define __TreeTest__TitleScene__

#include "axmol.h"

class TitleScene : public ax::Layer
{
public:
    virtual bool init() override;
    
    static ax::Scene* scene();
    
    void NextScene(ax::Object* obj);
    
    void menuCloseCallback(ax::Object* pSender);
    
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__TreeTest__TitleScene__) */

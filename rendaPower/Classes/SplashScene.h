#ifndef __TreeTest__SplashScene__
#define __TreeTest__SplashScene__

#include "axmol.h"

class SplashScene : public ax::Layer
{
protected:
    void nextScene();

public:
    bool init() override;
    static ax::Scene* scene();
    void menuCloseCallback(ax::Object* sender);

    CREATE_FUNC(SplashScene);
};

#endif /* defined(__TreeTest__SplashScene__) */

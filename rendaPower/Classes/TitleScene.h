#ifndef __TreeTest__TitleScene__
#define __TreeTest__TitleScene__

#include "axmol.h"

class TitleScene : public ax::Layer
{
public:
    bool init() override;
    static ax::Scene* scene();

    void nextScene(ax::Object* sender);
    void menuCloseCallback(ax::Object* sender);

    CREATE_FUNC(TitleScene);
};

#endif /* defined(__TreeTest__TitleScene__) */

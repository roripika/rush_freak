#ifndef __rendaPower__SelectMenuScene__
#define __rendaPower__SelectMenuScene__

#include "axmol.h"

class SelectMenuScene : public ax::Layer
{
public:
    bool init() override;
    static ax::Scene* scene();

    void openShuttleScene(ax::Object* sender);
    void menuCloseCallback(ax::Object* sender);

    CREATE_FUNC(SelectMenuScene);
};

#endif /* defined(__rendaPower__SelectMenuScene__) */

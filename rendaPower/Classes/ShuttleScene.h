#ifndef __rendaPower__ShuttleScene__
#define __rendaPower__ShuttleScene__

#include "axmol.h"

class ShuttleScene : public ax::Layer
{
protected:
    ax::Sprite* m_planetSprite = nullptr;
    ax::Sprite* m_rocketSprite = nullptr;

public:
    static ax::Scene* scene();
    bool init() override;

    CREATE_FUNC(ShuttleScene);
};

#endif /* defined(__rendaPower__ShuttleScene__) */

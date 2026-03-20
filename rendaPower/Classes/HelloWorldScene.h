#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "axmol.h"

class HelloWorld : public ax::Layer
{
public:
    bool init() override;
    static ax::Scene* scene();
    void menuCloseCallback(ax::Object* sender);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
